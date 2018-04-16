// IconView.cpp : implementation of the CIconView class
//

#include "stdafx.h"
#include "IconMasterXP.h"
#include "MWnd.h"

#include "Doc.h"
#include "MWnd.h"
#include "IconEditor.h"
#include "IconView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIconView

IMPLEMENT_DYNCREATE(CIconView, CListView)

BEGIN_MESSAGE_MAP(CIconView, CListView)
	ON_WM_STYLECHANGED()
	ON_COMMAND(ID_EDIT_REMOVEITEM, OnEditRemoveitem)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REMOVEITEM, OnUpdateEditRemoveitem)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECTALL, OnUpdateEditSelectall)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnNMRclick)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdraw)
ON_WM_DESTROY()
ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &CIconView::OnLvnItemchanged)
ON_NOTIFY_REFLECT(LVN_DELETEITEM, &CIconView::OnLvnDeleteitem)
ON_WM_TIMER()
ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CIconView construction/destruction

CIconView::CIconView()
	: m_nLvTimer(0)
{
	// TODO: add construction code here
}

CIconView::~CIconView()
{
}

BOOL CIconView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CIconView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().

}


// CIconView diagnostics

#ifdef _DEBUG
void CIconView::AssertValid() const
{
	CListView::AssertValid();
}

void CIconView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CDoc* CIconView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDoc)));
	return (CDoc*)m_pDocument;
}
#endif //_DEBUG


// CIconView message handlers
void CIconView::OnStyleChanged(int /*nStyleType*/, LPSTYLESTRUCT /*lpStyleStruct*/)
{
	//TODO: add code to react to the user changing the view style of your window
	
	Default();
}

CIconEditor * CIconView::GetIconEditor ()
{
	CMWnd * wnd = (CMWnd*)::AfxGetMainWnd ();
	CIconEditor * ed = (CIconEditor*)wnd->m_wndSplitter.GetPane (0,0);
	return ed;
}

CMWnd * CIconView::GetMainWnd ()
{
	CMWnd * wnd = (CMWnd*)::AfxGetMainWnd ();
	return wnd;
}


void CIconView::OnEditRemoveitem()
{
	CMWnd * wnd = GetMainWnd();
	CListCtrl * lv = &this->GetListCtrl ();

	//int nPrevItm = lv->GetSelectionMark();
	//int nAbovePrevItm = lv->GetNextItem(nPrevItm, LVNI_ABOVE);
	//int nBellowPrevItm = lv->GetNextItem(nPrevItm, LVNI_BELOW);

	POSITION pos = lv->GetFirstSelectedItemPosition();

	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		while (pos)
		{
			int nSel = lv->GetNextSelectedItem(pos);
			int nItem = (DWORD)lv->GetItemData (nSel);
			
			for (int i=0; i<wnd->m_Imported.GetCount ();++i)
			{
				if (wnd->m_Imported[i].dwID == nItem)
				{
					// Remove associated undo/redo actions
					BOOL bCleaning=TRUE;
					while (bCleaning)
					{
						bCleaning=FALSE;
						for (int u=0; u<GetMainWnd()->m_Actions.GetCount (); ++u)
						{
							CIcoImage * undo = (CIcoImage*)&GetMainWnd()->m_Actions[u];
							if ((wnd->m_Imported[i].m_FileName == undo->m_FileName) &&
								(wnd->m_Imported[i].GetFrame() == undo->GetFrame() )) 
							{
								GetMainWnd()->m_Actions.RemoveAt (u);
								bCleaning=TRUE;
								break;
							}
						}
					}
					
					wnd->m_Imported.RemoveAt (i);
				}
			}
		} // while(pos)
	}
	
	//int nNewItm = -1;

	wnd->RefreshView ();

	//if (nBellowPrevItm > -1)
	//	nNewItm = nBellowPrevItm-1;
	//else
	//	nNewItm = nAbovePrevItm;
	//
	//if (nNewItm > -1)
	//{
	//	lv->SetSelectionMark(nNewItm);
	//	lv->SetItemState(nNewItm, LVIS_SELECTED, LVIS_SELECTED);
	//	lv->EnsureVisible(nNewItm, false);
	//	
	//	///////////////
	//	// Strawman's pathetic attempts at fixing listview default behaviour.... many hours spent
	//	// to no avail.
	//	//
	//	//NMITEMACTIVATE itma;
	//	//ZeroMemory(&itma, sizeof(NMITEMACTIVATE));
	//	//itma.hdr.code = NM_CLICK;
	//	//itma.hdr.hwndFrom = lv->m_hWnd;
	//	//itma.hdr.idFrom = lv->GetDlgCtrlID();
	//	//itma.iItem = nNewItm;
	//	//lv->SendMessage(WM_NOTIFY, (WPARAM)itma.hdr.idFrom, (LPARAM)&itma);

	//	//SendMessage(WM_NOTIFY, NM_CLICK, (LPARAM)&NMListView);
	//	//Sleep(1000);
	//	//POINT pt;
	//	//GetCursorPos(&pt);
	//	//lv->ScreenToClient(&pt);
	//	//lv->SendMessage(WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pt.x, pt.y));
	//	//Sleep(1000);
	//	//lv->SendMessage(WM_MOUSEMOVE, 0U, MAKELPARAM(pt.x, pt.y));
	//	//Sleep(1000);
	//	//lv->SendMessage(WM_LBUTTONUP, 0U, MAKELPARAM(pt.x, pt.y));
	//	//Sleep(1000);
	//	//lv->SendMessage(WM_MOUSEMOVE, 0U, MAKELPARAM(pt.x, pt.y));
	//	///////////////
	//	//TRACE2("SELECTED:%d; OLD:%d\n", nNewItm, nPrevItm);
	//}

	//m_CurrLvItm = nNewItm;

	GetIconEditor()->RedrawWindow();
}

void CIconView::OnUpdateEditSelectAll(CCmdUI *pCmdUI)
{
	pCmdUI->Enable ((BOOL)GetListCtrl ().GetSelectedCount ()>0);
}

void CIconView::OnUpdateEditRemoveitem(CCmdUI *pCmdUI)
{
	pCmdUI->Enable ((BOOL)this->GetListCtrl ().GetSelectedCount ()>0);
	GetMainWnd()->ChangeIdlePaneText();
}

void CIconView::OnEditSelectall()
{
	CListCtrl * lv = &this->GetListCtrl ();
	for (int i=0; i<lv->GetItemCount (); ++i)
		lv->SetItemState (i, LVIS_SELECTED, LVIS_SELECTED);
}

void CIconView::OnUpdateEditSelectall(CCmdUI *pCmdUI)
{
	pCmdUI->Enable ((BOOL)GetListCtrl ().GetItemCount ()>0);
}


void CIconView::OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint pt;
	UINT nMenu;

	GetCursorPos(&pt);

	if (GetListCtrl().GetSelectedCount() > 0)
		nMenu=0;
	else
		nMenu=1;

	m_ItemPopup.GetSubMenu (nMenu)->TrackPopupMenu (TPM_RIGHTBUTTON, pt.x, pt.y, ::AfxGetMainWnd());

	*pResult = 0;
}

int CIconView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_ItemPopup.LoadMenu (IDR_LVPOPUP);

	m_ItemIco[0].LoadResource(FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PAPER), _T("PNG")), CXIMAGE_FORMAT_PNG);
	m_ItemIco[1].LoadResource(FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PAPER_INVALID), _T("PNG")), CXIMAGE_FORMAT_PNG);
	m_ItemIco[2].LoadResource(FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PAPER_ERROR), _T("PNG")), CXIMAGE_FORMAT_PNG);

	/* Fonts */
	CFont * lpfntOldFont = this->GetListCtrl().GetFont ();
	LOGFONT logFont;

	lpfntOldFont->GetLogFont (&logFont);

	logFont.lfItalic = TRUE;
	m_hfntViewItalic = CreateFontIndirect(&logFont);

	logFont.lfItalic = FALSE;
	m_hfntViewRegular = CreateFontIndirect(&logFont);

	logFont.lfWeight = FW_BOLD;
	m_hfntViewBold = CreateFontIndirect(&logFont);

	return 0;
}


/*
Custom Drawn List View
Credits also go to Michael Dunn for his wonderful article
http://www.codeproject.com/listctrl/lvcustomdraw.asp
*/
void CIconView::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	CListCtrl * lv = &this->GetListCtrl();
	CIcoImage * img;
	CMWnd * wnd = (CMWnd*)::AfxGetMainWnd ();


	*pResult = 0;

	// Request item-specific notifications if this is the
	// beginning of the paint cycle.

	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		// This is the beginning of an item's paint cycle.
		LVITEM   rItem;
		int      nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );
		CDC*     pDC   = CDC::FromHandle ( pLVCD->nmcd.hdc );
		COLORREF crBkgnd;
		BOOL     bListHasFocus;
		CRect    rcItem;
		CRect    rcText;
		CString  sText;

		bListHasFocus = ( lv->GetSafeHwnd() == ::GetFocus() );

		// Get the image index and selected/focused state of the
		// item being drawn.
		ZeroMemory ( &rItem, sizeof(LVITEM) );
		rItem.mask  = LVIF_IMAGE | LVIF_STATE;
		rItem.iItem = nItem;
		rItem.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
		lv->GetItem ( &rItem );

		// Get the rect that holds the item's icon.
		lv->GetItemRect ( nItem, &rcItem, LVIR_ICON );

		img = &(wnd->m_Imported[(int)lv->GetItemData (nItem)]);
		
		/* Position the icon within paper */
		CRect rtd;
		CRect wrt; 
		
		wrt.right=rcItem.right-rcItem.left;
		wrt.bottom=rcItem.bottom-rcItem.top;
		wrt.left=0; wrt.top=0;
		
		int w = img->GetWidth ();
		int h = img->GetHeight ();
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
		
		rtd.left=(wrt.right/2-rtd.right/2)+rcItem.left;
		rtd.top=(wrt.bottom/2-rtd.bottom/2)+rcItem.top+6;

		rtd.right+=rtd.left;rtd.bottom+=rtd.top;
		/* End positioning */

		crBkgnd = GetSysColor ( COLOR_WINDOW );
		
		pDC->FillSolidRect (rcItem, crBkgnd);

		int nPrevIco = 0;

		if (img->m_dwFlags & IM_ICON_INVALIDSIZE) nPrevIco = 1;
		if (img->m_dwFlags & IM_ICON_ERRORSIZE) nPrevIco = 2;

		m_ItemIco[nPrevIco].Draw (pDC->m_hDC, rcItem);

		if (img->m_dwFlags == 0)
			img->Draw (pDC->m_hDC, rtd);
		
		// Get the rect that bounds the text label.
		lv->GetItemRect ( nItem, rcItem, LVIR_LABEL );

		// Draw the background of the list item.  Colors are selected 
		// according to the item's state.

		if ( rItem.state & LVIS_SELECTED )
		{
			if ( bListHasFocus )
			{
				crBkgnd = GetSysColor ( COLOR_HIGHLIGHT );
				pDC->SetTextColor ( GetSysColor ( COLOR_HIGHLIGHTTEXT ));
			}
			else
			{
				crBkgnd = GetSysColor ( COLOR_BTNFACE );
				pDC->SetTextColor ( GetSysColor ( COLOR_BTNTEXT ));
			}
		}
		else
		{
			crBkgnd = GetSysColor ( COLOR_WINDOW );
			pDC->SetTextColor ( GetSysColor ( COLOR_BTNTEXT ));
		}

		// Draw the background & prep the DC for the text drawing.  Note
		// that the entire item RECT is filled in, so this emulates the full-
		// row selection style of normal lists.
		pDC->FillSolidRect ( rcItem, crBkgnd );
		pDC->SetBkMode ( TRANSPARENT );


		// Tweak the rect a bit for nicer-looking text alignment.
		rcText = rcItem;
		rcText.left += 3;
		rcText.top++;

		// Name
		sText.Format ("Name: %s", 
			lv->GetItemText ( nItem, 0 ));

		pDC->SelectObject (m_hfntViewBold);
		pDC->DrawText ( sText, rcText, DT_HIDEPREFIX|DT_TOP|DT_SINGLELINE );

		CString sInvalid((img->m_dwFlags & IM_ICON_ERRORSIZE) ? "\nThis icon has an invalid size" : "");

		// Draw the text.
		sText.Format ("\n%s%s\nSize: %s\nPalette: %s Colors",
			lv->GetItemText ( nItem, 3 ), sInvalid,
			lv->GetItemText ( nItem, 1 ),
			lv->GetItemText ( nItem, 2 ));

		COLORREF crShadeText = (COLORREF)GetSysColor (COLOR_GRAYTEXT);

		pDC->SetTextColor (crShadeText);
		pDC->SelectObject (m_hfntViewRegular);
		pDC->DrawText ( sText, rcText, DT_VCENTER|DT_HIDEPREFIX );

		// Draw a focus rect around the item if necessary.
		if ( bListHasFocus && ( rItem.state & LVIS_FOCUSED ))
		{
			pDC->DrawFocusRect ( rcItem );
		}

		*pResult = CDRF_SKIPDEFAULT;    // We've painted everything.
	}
}


void CIconView::OnDestroy()
{
	CListView::OnDestroy();

	::DeleteFont (m_hfntViewRegular);
	::DeleteFont (m_hfntViewBold);
	::DeleteFont (m_hfntViewItalic);
}

void CIconView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: Add your specialized code here and/or call the base class

	CListView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


void CIconView::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if (!((CMWnd*)AfxGetMainWnd())->m_bBusy && 
		((pNMLV->uNewState & LVIS_FOCUSED) == LVIS_FOCUSED) ||
		((pNMLV->uNewState & LVIS_SELECTED) == LVIS_SELECTED))
	{
		if ((pNMLV->uNewState & LVIS_FOCUSED) == LVIS_FOCUSED)
			this->GetListCtrl().SetSelectionMark(pNMLV->iItem);
						
		if (m_nLvTimer != 0)
			this->KillTimer(m_nLvTimer);
		
		m_nLvTimer = this->SetTimer(100, 50, NULL);
	}
	
	//TRACE3("ITEM %d (%d) STATE: %d\n", pNMLV->iItem, m_CurrLvItm, pNMLV->uNewState);

	*pResult = 0;
}


void CIconView::OnLvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	*pResult = 0;
}


void CIconView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == m_nLvTimer)
		GetIconEditor()->RedrawWindow();

	CListView::OnTimer(nIDEvent);
}


BOOL CIconView::OnEraseBkgnd(CDC* pDC)
{
	CListCtrl * lv = &this->GetListCtrl();

	if(lv->GetItemCount() <= 0)
	{
		int nSavedDC = pDC->SaveDC();

		COLORREF clrText = RGB(120,120,120);
		COLORREF clrBack = ::GetSysColor(COLOR_WINDOW);
		CRect rc;
		CFont fnt;
		lv->GetClientRect(&rc);

		fnt.CreateFontA(-MulDiv(9, pDC->GetDeviceCaps(88), 71), 0, 0, 0, 400, TRUE, FALSE, FALSE, 238, 0, 0, 2, 0, "Tahoma");

		CString strText = ((CMWnd*)::AfxGetMainWnd())->m_bBusy ? 
				"Working, please wait..." : "Use import button to insert some images to convert.";

		pDC->SetTextColor(clrText);
		pDC->SetBkColor(clrBack);
		pDC->FillRect(rc, &CBrush(clrBack));
		pDC->SelectObject(&fnt);
		pDC->DrawText(strText, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

		fnt.DeleteObject();

		pDC->RestoreDC(nSavedDC);		
		ReleaseDC(pDC);
	}
	else
	{
		return CListView::OnEraseBkgnd(pDC);
	}

	return true;
}
