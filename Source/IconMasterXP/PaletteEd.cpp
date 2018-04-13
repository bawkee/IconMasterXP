// PaletteEd.cpp : implementation file
//

#include "stdafx.h"
#include "IconMasterXP.h"
#include "PaletteEd.h"
#include ".\paletteed.h"


// CPaletteEd dialog

IMPLEMENT_DYNAMIC(CPaletteEd, CDialog)
CPaletteEd::CPaletteEd(CWnd* pParent /*=NULL*/)
	: CDialog(CPaletteEd::IDD, pParent)
{
	m_nSelCol=0;
}

CPaletteEd::~CPaletteEd()
{
}

void CPaletteEd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPaletteEd, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDCSHOWHELP, OnBnClickedCshowhelp)
END_MESSAGE_MAP()


// CPaletteEd message handlers

void CPaletteEd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// Do not call CDialog::OnPaint() for painting messages

	int cc = m_nColors;
	const int sx=10, sy=10, cw=12;
	int x=sx, y=sy;

	if ((cc>256)||(cc<=0)) {
		MessageBox ("Palette for selected image is invalid.", "Error", MB_OK|MB_ICONINFORMATION);
		return;
	}

	 
	int scy = m_nSelCol/16;
	int scx = m_nSelCol-scy*16;

	dc.FillSolidRect (CRect (sx+cw*scx-2, sy+cw*scy-2,
									(sx+cw*scx)+cw, (sy+cw*scy)+cw), RGB(255,0,0));

	for (int c=0; c<cc; c++)
	{
		dc.FillSolidRect (CRect (x,y,x+cw-2,y+cw-2), CxImage::RGBQUADtoRGB (m_rgbPal[c]));

		x += cw; 
		if (x>=cw*16) { 
			y+=cw;
			x=sx;
		}
	}


	dc.DrawEdge (CRect (sx-4, sy-4, cw*16+12, cw*16+12), 
		BDR_RAISEDINNER, BF_BOTTOMLEFT|BF_TOPRIGHT); 
}

void CPaletteEd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	const int sx=10, sy=10, cw=12;
	const int pw = sx+cw*16, ph = sy+cw*16;
	int nsel;

	if ((point.x>sx && point.y>sy) && (point.x<pw && point.y<ph))
	{
		nsel=((point.x-sx)/cw)+((point.y-sy)/cw)*16;

		if (nsel < m_nColors)
		{
			m_bValidPoint=TRUE;
			m_nSelCol=nsel;

			int r = m_rgbPal[nsel].rgbRed;
			int g = m_rgbPal[nsel].rgbGreen;
			int b = m_rgbPal[nsel].rgbBlue;

			CString szCol;
			szCol.Format ("#%d\tR:%d\tG:%d\tB:%d", nsel+1, r, g, b);

			this->GetDlgItem(IDC_COLOR)->SetWindowText(szCol);

			this->RedrawWindow();
		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CPaletteEd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bValidPoint=FALSE;
	OnLButtonDown (nFlags, point);

	if (m_bValidPoint)
	{
		// Show color editor
		CColorDialog cdlg;

		cdlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
		cdlg.m_cc.rgbResult = CxImage::RGBQUADtoRGB(m_rgbPal[m_nSelCol]);

		if (cdlg.DoModal ()!=IDOK) goto fin;

		m_rgbPal[m_nSelCol] = CxImage::RGBtoRGBQUAD (cdlg.GetColor ());
	
		OnLButtonDown (nFlags, point);
	}

fin:
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CPaletteEd::OnBnClickedCshowhelp()
{
	CString szFile = CString(((CIconMasterXPApp*)::AfxGetApp())->GetHelpFile()) + ">wnd_context";
	::HtmlHelp (this->m_hWnd, szFile, 
		HH_HELP_CONTEXT, IDH_PALETTE_EDITOR);
}
