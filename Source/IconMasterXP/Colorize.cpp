// Colorize.cpp : implementation file
//

#include "stdafx.h"
#include "IconMasterXP.h"
#include "Colorize.h"


// CColorize dialog

IMPLEMENT_DYNAMIC(CColorize, CDialog)
CColorize::CColorize(CWnd* pParent /*=NULL*/)
	: CDialog(CColorize::IDD, pParent)
	, m_nHue(0)
	, m_nSat(0)
	, m_nBlend(0)
	, m_Color (CxImage::RGBtoRGBQUAD (RGB(255,0,128)))
{
}

CColorize::~CColorize()
{
}

void CColorize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HUE, m_wndHue);
	DDX_Control(pDX, IDC_SAT, m_wndSat);
	DDX_Control(pDX, IDC_BLEND, m_wndBlend);
	DDX_Slider(pDX, IDC_HUE, m_nHue);
	DDX_Slider(pDX, IDC_SAT, m_nSat);
	DDX_Slider(pDX, IDC_BLEND, m_nBlend);
}


BEGIN_MESSAGE_MAP(CColorize, CDialog)
//	ON_WM_ACTIVATE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SELECT, OnBnClickedSelect)
	ON_WM_HSCROLL()
	ON_STN_CLICKED(IDC_COLOR, OnStnClickedColor)
	ON_WM_HELPINFO()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDCSHOWHELP, OnBnClickedHelp)
END_MESSAGE_MAP()


// CColorize message handlers


void CColorize::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CWnd * wnd = this->GetDlgItem (IDC_COLOR);
	CRect rt;

	CDC * dcc = wnd->GetDC();
	wnd->GetClientRect (&rt);
	dcc->FillRect (rt, &CBrush(CxImage::RGBQUADtoRGB(CxImage::HSLtoRGB (m_Color))));
	wnd->ReleaseDC (dcc);
}

void CColorize::OnBnClickedSelect()
{
	CColorDialog cdlg;

	cdlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
	cdlg.m_cc.rgbResult = CxImage::RGBQUADtoRGB (CxImage::HSLtoRGB (m_Color));

	if (cdlg.DoModal ()!=IDOK) return;

	m_Color = CxImage::RGBtoHSL (CxImage::RGBtoRGBQUAD (cdlg.GetColor ()));

	m_wndHue.SetPos (m_Color.rgbRed);
	m_wndSat.SetPos (m_Color.rgbGreen);

	this->OnPaint ();
}

void CColorize::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl * wnd = (CSliderCtrl*)pScrollBar;
	int h=0, s=0;

	switch (wnd->GetDlgCtrlID ())
	{
	case (IDC_HUE):
		m_Color.rgbRed = wnd->GetPos ();
		break;
	case (IDC_SAT):
		m_Color.rgbGreen = wnd->GetPos ();
		break;
	}

	this->OnPaint ();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CColorize::OnStnClickedColor()
{
	OnBnClickedSelect();
}

BOOL CColorize::OnHelpInfo(HELPINFO* pHelpInfo)
{
	/*
	switch (pHelpInfo->iCtrlId)
	{
	case IDC_HUE:
	*/
		::HtmlHelp (this->m_hWnd, ((CIconMasterXPApp*)::AfxGetApp())->GetHelpFile(), HH_HELP_CONTEXT, IDH_COLORIZE); 
	//	break;
	//}

	return CDialog::OnHelpInfo(pHelpInfo);
}

void CColorize::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	m_wndHue.SetRangeMax		(255);
	m_wndSat.SetRangeMax		(255);
	m_wndBlend.SetRangeMax	(100);

	m_wndHue.SetTicFreq (5);
	m_wndSat.SetTicFreq (5);
	m_wndBlend.SetTicFreq (5);

	m_wndBlend.SetPos (50);

	m_wndHue.SetPos (m_Color.rgbRed);
	m_wndSat.SetPos (m_Color.rgbGreen);
}

void CColorize::OnBnClickedHelp()
{
	CString szFile = CString(((CIconMasterXPApp*)::AfxGetApp())->GetHelpFile()) + ">wnd_context";
	::HtmlHelp (this->m_hWnd, szFile, 
		HH_HELP_CONTEXT, IDH_COLORIZE);
}
