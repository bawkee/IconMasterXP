// IconEditor.cpp : implementation of the CIconEditor class
//

#include "stdafx.h"
#include "IconMasterXP.h"
#include "MWnd.h"

#include "Doc.h"
#include "IconEditor.h"
#include "IconView.h"

#include "Resample.h"
#include "Rotate.h"
#include "Quantize.h"
#include "Colorize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIconEditor

IMPLEMENT_DYNCREATE(CIconEditor, CTreeView)

BEGIN_MESSAGE_MAP(CIconEditor, CTreeView)
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
//	ON_WM_CREATE()
//ON_WM_CREATE()
ON_WM_SIZE()
ON_WM_ERASEBKGND()
//ON_WM_NCPAINT()
//ON_WM_NCPAINT()
END_MESSAGE_MAP()


// CIconEditor construction/destruction

CIconEditor::CIconEditor()
{
	m_nZoom=1;
	m_bPicker=FALSE;
	m_bClose=FALSE;
	m_bInteractive=FALSE;

	m_hPatBrush = ::CreatePatternBrush (::LoadBitmap (::AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PATTBACK)));
}


CIconEditor::~CIconEditor()
{
	// TODO: Add your destructorz code
}

BOOL CIconEditor::PreCreateWindow(CREATESTRUCT& cs)
{	
	return CTreeView::PreCreateWindow(cs);
}

void CIconEditor::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	m_ZoomAlias = GetInt("ZoomAlias", 0);
}


// CIconEditor diagnostics

#ifdef _DEBUG
void CIconEditor::AssertValid() const
{
	CTreeView::AssertValid();
}

void CIconEditor::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CDoc* CIconEditor::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDoc)));
	return (CDoc*)m_pDocument;
}
#endif //_DEBUG

CMWnd * CIconEditor::GetMainWnd ()
{
	CMWnd * wnd = (CMWnd*)::AfxGetMainWnd ();
	return wnd;
}

// CIconEditor message handlers


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Paint Handling
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CIconEditor::OnPaint()
{
	CPaintDC pdc(this); // device context for painting
	CDC bufDC;
	CBitmap bufBmp;
	CMWnd * wnd = (CMWnd*)::AfxGetMainWnd ();
	CRect rtd;

	if (!wnd->m_wndSplitter)  
		return;
	
	CIconView * iv = (CIconView*)wnd->m_wndSplitter.GetPane (1, 0);
	CListCtrl * lv = &iv->GetListCtrl();

	int iSel = lv->GetSelectionMark();

	CRect wrt; 
	
	this->GetClientRect (&wrt);
	
	bufDC.CreateCompatibleDC(&pdc);
	bufBmp.CreateCompatibleBitmap(&pdc, wrt.right, wrt.bottom);
	bufDC.SelectObject(&bufBmp);

	if (wnd->m_nBackground == BACK_COLOR)
		bufDC.FillSolidRect (&wrt, wnd->m_dwBackColor);
	else
		bufDC.FillRect (&wrt, CBrush::FromHandle (m_hPatBrush));

	bufDC.SetBkColor (wnd->m_dwBackColor);

	if ((iSel <= -1) || lv->GetItemCount ()<=0) 
	{
		CFont fnt;
		fnt.CreateFontA(-MulDiv(9, bufDC.GetDeviceCaps(88), 71), 0, 0, 0, 400, TRUE, FALSE, FALSE, 238, 0, 0, 2, 0, "Tahoma");
		bufDC.SelectObject(&fnt);
		bufDC.SetTextColor (RGB(120,120,120));
		bufDC.DrawText("Icon preview area. Select an image to preview.", &wrt, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		fnt.DeleteObject();

		goto fin;
	}

	CIcoImage * img = &wnd->m_Imported[(int)lv->GetItemData (iSel)];
	
	int w = img->GetWidth () * m_nZoom;
	int h = img->GetHeight () * m_nZoom;
	double rw=0,rh=0,r;
	
	rtd.left=wrt.right/2-w/2;
	rtd.top=wrt.bottom/2-h/2;

	rtd.right=w+rtd.left;
	rtd.bottom=h+rtd.top;

	if (w>wrt.right)
		rw=100.00-((double)wrt.right/(double)w)*100.00;
	if (h>wrt.bottom)
		rh=100.00-((double)wrt.bottom/(double)h)*100.00;

	r = rw>rh?rw:rh;

	rtd.right = w-(int)((double)r/100.00*(double)w);
	rtd.bottom = h-(int)((double)r/100.00*(double)h);
	
	rtd.left=wrt.right/2-rtd.right/2;
	rtd.top=wrt.bottom/2-rtd.bottom/2;

	rtd.right+=rtd.left;rtd.bottom+=rtd.top;

	//TRACE2("%2.2f,%2.2f\n", rw,rh);

	img->m_rtPosition = rtd;
	img->Draw (bufDC.m_hDC, rtd, NULL, m_ZoomAlias);
	
fin:
	pdc.BitBlt(0, 0, wrt.right, wrt.bottom, &bufDC, 0, 0, SRCCOPY);

	bufDC.DeleteDC();
	bufBmp.DeleteObject();
}

CIcoImage * CIconEditor::GetSelectedImage ()
{
	CMWnd * wnd = (CMWnd*)::AfxGetMainWnd ();
	CListCtrl * lv = &((CIconView*)wnd->m_wndSplitter.GetPane (1, 0))->GetListCtrl ();
	int nSel = lv->GetSelectionMark ();

	if (lv->GetItemCount () != wnd->m_Imported.GetCount ()) return NULL;
	if (nSel >= 0)
		return &(wnd->m_Imported[(int)lv->GetItemData (nSel)]);
	else
		return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Resample
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CIconEditor::Resample()
{
	CResample wndRes;
	CMWnd * wnd = (CMWnd*)::AfxGetMainWnd ();
	CListCtrl * lv = &((CIconView*)wnd->m_wndSplitter.GetPane (1, 0))->GetListCtrl ();
	int nSel = lv->GetSelectionMark ();
	int nCnt = lv->GetSelectedCount ();
	bool bNoEffect = false;
	bool bUsePercent = false;

	CIcoImage * img = GetSelectedImage();

	if (img == NULL) // Sometimes no single image is selected
	{
		wndRes.m_nWidth = 32;
		wndRes.m_nHeight = 32;
	}
	else
	{
		wndRes.m_nWidth = img->GetWidth ();
		wndRes.m_nHeight = img->GetHeight ();
	}

	if (wndRes.DoModal ()!=IDOK) return;

	if (nCnt > 1)
	{
		if (MessageBox ("There are multiple images in the queue for resampling, program will alter their size relative to the chosen percentage.\n\nPress cancel to use the same size for all images anyway.",
			"Resample", MB_OKCANCEL|MB_ICONWARNING) != IDCANCEL)
			bUsePercent = true;
	}

	POSITION pos = lv->GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		while (pos)
		{

			nSel = lv->GetNextSelectedItem(pos);

			img = &wnd->m_Imported[(int)lv->GetItemData (nSel)];

			if ((wndRes.m_dwInterpolation != CxImage::IM_NEAREST_NEIGHBOUR) && (img->GetBpp() == 1))
				bNoEffect = true;

			CIcoImage undo=*img;
			GetMainWnd()->m_Actions.Add (undo);

			int nw = wndRes.m_nWidth;
			int nh = wndRes.m_nHeight;

			if (bUsePercent)
			{
				nw = (int)((wndRes.m_nWidthp * (float)img->GetWidth()) / 100.0f);
				nh = (int)((wndRes.m_nHeightp * (float)img->GetHeight()) / 100.0f);
			}
			
			if ((int)img->GetWidth() > nw && (int)img->GetHeight() > nh && 
				wndRes.m_dwInterpolation == CxImage::IM_BILINEAR)
				img->QIShrink(nw, nh);
			else if (wndRes.m_dwInterpolation == CxImage::IM_NEAREST_NEIGHBOUR)
				img->Resample(nw, nh);
			else
				img->Resample2(nw, nh, wndRes.m_dwInterpolation);

		} // while(pos)

		if (bNoEffect) 
			MessageBox ("Some of the resampled images had a 1-bit palette and therefore no antialiasing was used on those.",
				"Warning", MB_OK|MB_ICONWARNING);
	}

	RedrawWindow();

	wnd->RefreshView ();
}


void CIconEditor::Zoom (int x)
{
	//CxImage * img = GetSelectedImage();
	m_nZoom = x;
	RedrawWindow();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Rotate
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CIconEditor::Rotate ()
{
	CRotate wndRes;
	CMWnd * wnd = (CMWnd*)::AfxGetMainWnd ();
	CListCtrl * lv = &((CIconView*)wnd->m_wndSplitter.GetPane (1, 0))->GetListCtrl ();
	int nSel = lv->GetSelectionMark ();
	int nCnt = lv->GetSelectedCount ();

	CIcoImage * img = GetSelectedImage();

	if (wndRes.DoModal ()!=IDOK) return;

	POSITION pos = lv->GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		while (pos)
		{

			nSel = lv->GetNextSelectedItem(pos);

			img = &wnd->m_Imported[(int)lv->GetItemData (nSel)];

			if ((wndRes.m_dwInterpolation != CxImage::IM_NEAREST_NEIGHBOUR) && (nCnt<=1)) {
				if (!img->AlphaIsValid () && img->GetBpp()!=24) {
					if (MessageBox ("You have selected an antialiasing method, although selected image format does not support alpha channels. It is recommended that you change the format to 32-bit first. Press OK to continue resampling.", "Warning", MB_OKCANCEL|MB_ICONWARNING)==IDCANCEL)
						return;
				}
			}

			GetMainWnd()->m_Actions.Add (*img);
			img->Rotate2 ((float)wndRes.m_nAngle, NULL,
				wndRes.m_dwInterpolation, CxImage::OM_BACKGROUND, 0, TRUE, wndRes.m_bKeepSize);

		} // while(pos)
	}

	RedrawWindow();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Custom Actions
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CIconEditor::CustomAction (DWORD dwAction, DWORD dwParam1)
{
	CMWnd * wnd = (CMWnd*)::AfxGetMainWnd ();
	CListCtrl * lv = &((CIconView*)wnd->m_wndSplitter.GetPane (1, 0))->GetListCtrl ();
	BOOL b32BitTransWarning=FALSE;
	BOOL bDontRefresh=FALSE;
	RGBQUAD qTrans;
	RGBQUAD qRc1, qRc2;
	BYTE chTH=0;
	int nTrans=0;
	int nSel = lv->GetSelectionMark ();
	int nCnt = lv->GetSelectedCount ();
	CColorize dlgColorize;
	CIcoImage * img = GetSelectedImage();

	if (dwAction & IE_FILTER_COLORIZE)
	{
		if ((img->GetBpp() == 1) && (nCnt == 1)) {
			MessageBox ("The selected image has no colors in its palette, please convert it to at least 4-bit color depth mode.",
				"Warning", MB_OK|MB_ICONWARNING);
			return;
		}
		if (dlgColorize.DoModal () != IDOK) return;
	}

	if (dwAction & IE_ACTION_CREPLACE)
	{
		RGBQUAD qGuess = img->GetPixelColor (0, 0, FALSE);
		CColorDialog cdlg;

		cdlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
		cdlg.m_cc.rgbResult = CxImage::RGBQUADtoRGB(qGuess);

		if (cdlg.DoModal ()!=IDOK) return;
		qRc1 = CxImage::RGBtoRGBQUAD (cdlg.GetColor ());

		if (cdlg.DoModal ()!=IDOK) return;
		qRc2 = CxImage::RGBtoRGBQUAD (cdlg.GetColor ());
	}

	if (dwAction & IE_ACTION_SETTRANS)
	{
		RGBQUAD qGuess = img->GetPixelColor (0, 0, FALSE);
		COLORREF crGuess = RGB(qGuess.rgbRed,qGuess.rgbGreen,qGuess.rgbBlue);
		CColorDialog cdlg;

		cdlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
		cdlg.m_cc.rgbResult = crGuess;

		if (cdlg.DoModal ()!=IDOK) return;

		qTrans = CxImage::RGBtoRGBQUAD (cdlg.GetColor ());
	}

	if (dwAction & IE_FILTER_INTERACTIVETH)
	{
		DWORD nF1, nF2=0;
		BYTE chAm=5;
		MSG msg;

		GetMainWnd()->m_Actions.Add (*img);

		img->AlphaStrip ();

		m_bInteractive=TRUE;
		this->SetFocus ();
		CIcoImage copy; copy = *img;

		while (m_bInteractive)
		{
			nF1=GetTickCount();

			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (nF2 >= 150)
			{
				chTH+=chAm;
				if (chTH>=255 || chTH<=0) {
					chAm = -chAm;
				}
				
				img->Copy (copy);
				img->Threshold (chTH);

				nF2=0;
				RedrawWindow();
			}
			
			nF2+=GetTickCount()-nF1;
		}
	}


	POSITION pos = lv->GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		while (pos)
		{

			nSel = lv->GetNextSelectedItem(pos);
			img = &wnd->m_Imported[(int)lv->GetItemData (nSel)];
			GetMainWnd()->m_Actions.Add (*img);


			if (dwAction & IE_ACTION_FLIP)
				img->Flip ();
			if (dwAction & IE_ACTION_MIRROR)
				img->Mirror ();

			if (dwAction & IE_ACTION_REMOVETRANS)
				if (img->GetBpp() < 32)
					img->SetTransIndex (-1);
				else		
					b32BitTransWarning=TRUE;

			if (dwAction & IE_ACTION_SETTRANS)
			{
				img->SetTransColor (qTrans);
				nTrans=(int)img->GetNearestIndex (qTrans);
				if (img->GetBpp () <= 8)
					img->SetTransIndex (nTrans);
				else
					img->SetTransIndex (0);
			}

			if (dwAction & IE_ACTION_PICKTRANS)
			{
				img->SetTransColor (this->m_crTransparent);
				if (img->GetBpp () <= 8)
					img->SetTransIndex (img->GetNearestIndex (this->m_crTransparent));
				else
					img->SetTransIndex (0);
			}

			RGBQUAD * pal;

			// Color depths
			if (dwAction & IE_ACTION_1BPP)							// 2 colors
			{
				img->AlphaStrip ();

				if (img->GetBpp() > 1) {
					img->DecreaseBpp (1, TRUE);
				}
			}
			if (dwAction & IE_ACTION_4BPP)							// 16 colors
			{
				img->AlphaStrip ();
				img->AlphaDelete ();

				img->SetTransIndex (-1);

				if (img->GetBpp() > 4) {
					img->DecreaseBpp (4, TRUE);
				}
				else if (img->GetBpp() < 4)
					img->IncreaseBpp (4);

				//delete pal;
			}
			if (dwAction & IE_ACTION_8BPP)							// 256 colors
			{
				img->AlphaStrip ();

				CQuantizer q(256,8);
				q.ProcessImage (img->GetDIB ());
				pal=(RGBQUAD*)calloc(256*sizeof(RGBQUAD),1);
				q.SetColorTable (pal);

				if (img->GetBpp() > 8) {
					img->DecreaseBpp (8, TRUE, pal);
				}
				else if (img->GetBpp() < 8)
					img->IncreaseBpp (8);

				delete pal;
			}
			
			if (dwAction & IE_ACTION_24BPP)							// not paletted
			{
				img->AlphaStrip ();
				
				if (img->GetBpp() > 24) {
					img->DecreaseBpp (24, TRUE);
				}
				else if (img->GetBpp() < 24)
					img->IncreaseBpp (24);
			}


			if (dwAction & IE_FILTER_THRESHOLD)
			{
				img->AlphaStrip ();
				img->Threshold (255/2);
			}

			if (dwAction & IE_FILTER_INTERACTIVETH)
			{
				img->AlphaStrip ();
				img->Threshold (chTH);
			}

			if (dwAction & IE_FILTER_GAMMA) {
				if ((int)dwParam1 > 0)
					img->Gamma (1.23f);
				else
					img->Gamma (0.9f);
				bDontRefresh=TRUE;
			}

			if (dwAction & IE_FILTER_CONTRAST) {
				if ((int)dwParam1 > 0)
					img->Light (10, 25);
				else
					img->Light (10, -25);
				bDontRefresh=TRUE;
			}

			if (dwAction & IE_FILTER_LIGHT) {
				if ((int)dwParam1 > 0)
					img->Light (20);
				else
					img->Light (-20);
				bDontRefresh=TRUE;
			}
		
			if (dwAction & IE_FILTER_SOFTEN)
			{
				long kernel[]={1,1,1,1,8,1,1,1,1};
				img->Filter (kernel,3,16,0);
			}
			if (dwAction & IE_FILTER_SHARPEN)
			{
				long kernel[]={-1,-1,-1,-1,15,-1,-1,-1,-1};
				img->Filter (kernel,3,7,0);
			}
			if (dwAction & IE_FILTER_EDGE)
			{
				long kernel[]={-1,-1,-1,-1,8,-1,-1,-1,-1};
				img->Filter (kernel,3,-1,255);
			}

			if (dwAction & IE_FILTER_COLORIZE)
				img->Colorize (dlgColorize.m_nHue, 
					dlgColorize.m_nSat, 
					dlgColorize.m_nBlend/100.0f);

			if (dwAction & IE_FILTER_NEGATIVE)
				img->Negative ();

			if (dwAction & IE_ACTION_DUPLICATE)
			{
				CString szFile = img->m_FileName;
				wnd->m_Imported.Add (*img);
				CIcoImage * tmp = &wnd->m_Imported[wnd->m_Imported.GetCount()-1];
				int c=1;

				for (int i=0; i<wnd->m_Imported.GetCount (); ++i)
					if (wnd->m_Imported[i].m_FileName == szFile)
						c++;
				
				tmp->SetFrame (c);
			}

			if (dwAction & IE_ACTION_REVERT)
			{
				CMWnd * wnd = GetMainWnd();
				BOOL bRev = FALSE;
				BOOL bClean = TRUE;

				while(bClean)
				{
					bClean=FALSE;
					for (int i=0; i<wnd->m_Actions.GetCount(); ++i)
					{
						CIcoImage * undo = &wnd->m_Actions[i];
						if ((img->m_FileName == undo->m_FileName) &&
							(img->GetFrame() == undo->GetFrame() ))
						{
							if (!bRev) 
							{
								*img = *undo;
								bRev=TRUE;
							}
							bClean=TRUE;
							wnd->m_Actions.RemoveAt(i);
							break;
						}
					}
				}
			}

			if (dwAction & IE_ACTION_CREPLACE)
			{
				TRACE2("Q1:%d, Q2:%d\n", qRc1.rgbRed, qRc2.rgbRed);
				for (UINT x=0; x<img->GetWidth (); ++x)
					for (UINT y=0; y<img->GetHeight(); ++y)
						if (CxImage::RGBQUADtoRGB (img->GetPixelColor (x,y))==
							CxImage::RGBQUADtoRGB(qRc1))
							img->SetPixelColor (x,y, qRc2);
			}

		} // while(pos)
	}

	if (b32BitTransWarning)
		MessageBox ("You tried to remove transparency from 32-bit image(s), you must first remove the alpha channel, in order to do that convert image(s) to lower bit depth."
		,"Warning", MB_ICONWARNING|MB_OK);

	RedrawWindow();
	if (!bDontRefresh)
		wnd->RefreshView ();
	
	if (m_bClose) ::AfxGetApp ()->CloseAllDocuments (TRUE);
}


BOOL CIconEditor::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_bPicker)
	{
		CString sClassName;
		::GetClassName(pWnd->GetSafeHwnd(),sClassName.GetBuffer(80),80);
		::SetCursor(m_hPicker);
		return TRUE;
	}

	return CTreeView::OnSetCursor(pWnd, nHitTest, message);
}

void CIconEditor::OnLButtonUp(UINT nFlags, CPoint point)
{

	CTreeView::OnLButtonUp(nFlags, point);
}

void CIconEditor::OnLButtonDown(UINT nFlags, CPoint point)
{
	/*
	CIcoImage * img = this->GetSelectedImage ();
	img->DrawString (0, 1,17, "IconMasterXP DEMO", 
	CxImage::RGBtoRGBQUAD (RGB(255,255,255)), "Arial", 17, 17, 1, 0, FALSE);
	Invalidate(0);
	*/
	m_bInteractive = false;

	if (m_bPicker)
	{
		RedrawWindow();

		CIcoImage * img = this->GetSelectedImage ();

		int x, y;
		GetMouseXY(&x, &y, point);

		if (x < 0 || y < 0) return;

		m_crTransparent = img->GetPixelColor (x, y, FALSE);
		m_nTransparent = img->GetPixelIndex (x, y);
		
		CustomAction (IE_ACTION_PICKTRANS);

		RedrawWindow();
		m_bPicker=FALSE;
	}
	CTreeView::OnLButtonDown(nFlags, point);
}

void CIconEditor::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	m_bPicker=FALSE;
	m_bInteractive=FALSE;
	SetCursor (::AfxGetApp()->LoadStandardCursor (IDC_ARROW));
	CTreeView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CIconEditor::OnKillFocus(CWnd* pNewWnd)
{
	CTreeView::OnKillFocus(pNewWnd);

	m_bPicker=FALSE;
	m_bInteractive=FALSE;
	SetCursor (::AfxGetApp()->LoadStandardCursor (IDC_ARROW));
}

void CIconEditor::OnDestroy()
{
	m_bInteractive=FALSE;

	CTreeView::OnDestroy();
}

void CIconEditor::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bPicker)
	{
		CIcoImage * img = this->GetSelectedImage ();

		int x, y;
		GetMouseXY (&x, &y, point);

		if (x>0 && y>0)
		{
			CString szPane;
			RGBQUAD q = img->GetPixelColor ((int)x,(int)y);
			szPane.Format ("x:%d; y:%d; r:%d; g:%d; b:%d;", 
				(int)x, img->GetHeight()-(int)y, q.rgbRed, q.rgbGreen, q.rgbBlue);
			((CStatusBar*)(this->GetMainWnd ()->GetControlBar (AFX_IDW_STATUS_BAR)))->SetPaneText (0, szPane);
		}
	}

	CTreeView::OnMouseMove(nFlags, point);
}

void CIconEditor::GetMouseXY (int * nx, int * ny, CPoint &point)
{
	CIcoImage * img = this->GetSelectedImage ();
	float fact = (float)(img->m_rtPosition.right-img->m_rtPosition.left)/(float)img->GetWidth();
	float x=(float)(point.x-img->m_rtPosition.left);
	float y=(float)(point.y-img->m_rtPosition.top);

	x/=fact;
	y/=fact;

	y=img->GetHeight()-y;

	*nx = (int)x;
	*ny = (int)y;
}


void CIconEditor::OnSize(UINT nType, int cx, int cy)
{
	CTreeView::OnSize(nType, cx, cy);

	this->RedrawWindow();
}


BOOL CIconEditor::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

