// Resample.cpp : implementation file
//

#include "stdafx.h"
#include "IconMasterXP.h"
#include "Resample.h"
#include ".\resample.h"


// CResample dialog

IMPLEMENT_DYNAMIC(CResample, CDialog)
CResample::CResample(CWnd* pParent /*=NULL*/)
	: CDialog(CResample::IDD, pParent)
	, m_nWidth(0)
	, m_nHeight(0)
	, m_nAntialias(0)
	, m_dwInterpolation(CxImage::IM_NEAREST_NEIGHBOUR)
	, m_nWidthp(0)
	, m_nHeightp(0)
{
}

CResample::~CResample()
{
}

void CResample::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WIDTH, m_nWidth);
	DDX_Text(pDX, IDC_HEIGHT, m_nHeight);
	DDX_Control(pDX, IDC_SIZES, m_wndSizes);
	DDX_Control(pDX, IDC_ANTIALIAS, m_wndAntialias);
	DDX_CBIndex(pDX, IDC_ANTIALIAS, m_nAntialias);
	DDX_Control(pDX, IDC_WIDTH, m_Width);
	DDX_Control(pDX, IDC_HEIGHT, m_Height);
	DDX_Control(pDX, IDC_WIDTHP, m_Widthp);
	DDX_Control(pDX, IDC_HEIGHTP, m_Heightp);
	DDX_Control(pDX, IDC_RATIO, m_Ratio);
	DDX_Text(pDX, IDC_WIDTHP, m_nWidthp);
	DDX_Text(pDX, IDC_HEIGHTP, m_nHeightp);
}


BEGIN_MESSAGE_MAP(CResample, CDialog)
	ON_EN_SETFOCUS(IDC_WIDTH, OnEnSetfocusWidth)
	ON_EN_SETFOCUS(IDC_HEIGHT, OnEnSetfocusHeight)
	ON_WM_ACTIVATE()
	ON_LBN_SELCHANGE(IDC_SIZES, OnLbnSelchangeSizes)
	ON_CBN_SELENDOK(IDC_ANTIALIAS, OnCbnSelendokAntialias)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_LBN_DBLCLK(IDC_SIZES, OnLbnDblclkSizes)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDCSHOWHELP, OnBnClickedCshowhelp)
	ON_WM_CREATE()
	ON_EN_CHANGE(IDC_WIDTH, OnEnChangeWidth)
	ON_EN_CHANGE(IDC_HEIGHT, OnEnChangeHeight)
	ON_EN_CHANGE(IDC_WIDTHP, OnEnChangeWidthp)
	ON_EN_CHANGE(IDC_HEIGHTP, OnEnChangeHeightp)

	ON_BN_CLICKED(IDC_RATIO, OnBnClickedRatio)
END_MESSAGE_MAP()


// CResample message handlers

void CResample::OnEnSetfocusWidth()
{
	this->m_Width.SetSel (0, 99);
}

void CResample::OnEnSetfocusHeight()
{
	this->m_Height.SetSel (0, 99);
}

void CResample::ValidateSizeVariables ()
{
	CString szBuf;
	this->m_Width.GetWindowText (szBuf); m_nWidth = atol(szBuf);
	this->m_Height.GetWindowText (szBuf); m_nHeight = atol(szBuf);
}

void CResample::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
}

void CResample::OnLbnSelchangeSizes()
{
	CString szBuf;
	int ns;

	switch (m_wndSizes.GetCurSel ())
	{
		case 0:ns=16;break;
		case 1:ns=32;break;
		case 2:ns=48;break;
		case 3:ns=64;break;
		case 4:ns=128;break;
		default: return;
	}
	szBuf.Format ("%d", ns);

	m_Ratio.SetCheck(0);

	this->m_Width.SetWindowText (szBuf);
	this->m_Height.SetWindowText (szBuf);

	this->ValidateElements(Element::Width, ElementType::Size, true);
	this->ValidateElements(Element::Height, ElementType::Size, true);

	m_Width.SetFocus();

	OnEnChangeWidth();
	OnEnChangeHeight();
}

void CResample::OnCbnSelendokAntialias()
{
	switch (m_wndAntialias.GetCurSel ())
	{
		case 0: m_dwInterpolation=CxImage::IM_NEAREST_NEIGHBOUR; break;
		case 1: m_dwInterpolation=CxImage::IM_BILINEAR; break;
		case 2: m_dwInterpolation=CxImage::IM_BICUBIC; break;
		case 3: m_dwInterpolation=CxImage::IM_BSPLINE; break;
		case 4: m_dwInterpolation=CxImage::IM_LANCZOS; break;
		case 5: m_dwInterpolation=CxImage::IM_HERMITE; break;
	}
}

void CResample::OnBnClickedOk()
{
	if ((this->m_nWidth <= 0) || (this->m_nHeight <= 0)) {
		this->MessageBox("You must enter valid values, width or height cannot be zero.", 
			"Resample", MB_OK | MB_ICONWARNING);
		return;
	}

	this->OnOK();
}

void CResample::OnLbnDblclkSizes()
{
	if (m_wndSizes.GetCurSel() >= 0) OnBnClickedOk();
}

void CResample::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	while (m_wndSizes.GetCount () > 0)
		m_wndSizes.DeleteString (0);
	
	m_Widthp.SetMaxDecimalPlaces(2);
	m_Heightp.SetMaxDecimalPlaces(2);

	m_wndSizes.InsertString (0, "16 x 16");
	m_wndSizes.InsertString (1, "32 x 32");
	m_wndSizes.InsertString (2, "48 x 48");
	m_wndSizes.InsertString (3, "64 x 64");
	m_wndSizes.InsertString (4, "128 x 128");

	while (m_wndAntialias.GetCount () > 0)
		m_wndAntialias.DeleteString (0);
	
	m_wndAntialias.InsertString (0, "No Antialias");
	m_wndAntialias.InsertString (1, "Bilinear");
	m_wndAntialias.InsertString (2, "Bicubic");
	m_wndAntialias.InsertString (3, "BSpline");
	m_wndAntialias.InsertString (4, "Lanzcos");
	m_wndAntialias.InsertString (5, "Hermite");

	m_wndAntialias.SetCurSel(1);
	m_dwInterpolation=CxImage::IM_BILINEAR;

	// Remember original sizes
	m_nWidthO = m_nWidth;
	m_nHeightO = m_nHeight;

	CString szBuf;

	szBuf.Format("%d", m_nWidth); this->m_Width.SetWindowText (szBuf);
	szBuf.Format("%d", m_nHeight); this->m_Height.SetWindowText (szBuf);

	this->m_Widthp.SetWindowText ("100");
	this->m_Heightp.SetWindowText ("100");

	m_Ratio.SetCheck (1);
}

void CResample::OnBnClickedCshowhelp()
{
	CString szFile = CString(((CIconMasterXPApp*)::AfxGetApp())->GetHelpFile()) + ">wnd_context";
	::HtmlHelp (this->m_hWnd, szFile, 
		HH_HELP_CONTEXT, IDH_RESAMPLE);
}

int CResample::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CResample::OnEnChangeWidth()
{
	this->ValidateElements(Element::Width, ElementType::Size);
}

void CResample::OnEnChangeHeight()
{
	this->ValidateElements(Element::Height, ElementType::Size);
}

void CResample::OnEnChangeWidthp()
{
	this->ValidateElements(Element::Width, ElementType::Percent);
}

void CResample::OnEnChangeHeightp()
{
	this->ValidateElements(Element::Height, ElementType::Percent);
}

void CResample::ValidateElements(CResample::Element elem, CResample::ElementType type, bool bIgnoreFocus)
{
	CEdit * wndSize, * wndPercent;
	CString szSize, szPercent;
	long nOriginalSize, nSize;
	float nPercent;
	
	switch (elem)
	{
	case Element::Width: 
		wndSize = &this->m_Width; wndPercent = &this->m_Widthp; nOriginalSize = this->m_nWidthO; break;
	case Element::Height:
		wndSize = &this->m_Height; wndPercent = &this->m_Heightp; nOriginalSize = this->m_nHeightO; break;
	}

	switch (type)
	{
	case ElementType::Percent:
		if (!bIgnoreFocus)
			if (::GetFocus() != wndPercent->m_hWnd) return;
		wndPercent->GetWindowText (szPercent); nPercent = (float)atof(szPercent);
		nSize = (int)((nPercent * (float)nOriginalSize) / 100.0f);
		szSize.Format("%d", nSize); wndSize->SetWindowText(szSize);
		break;
	case ElementType::Size:
		if (!bIgnoreFocus)
			if (::GetFocus() != wndSize->m_hWnd) return;
		this->ValidateSizeVariables();
		wndSize->GetWindowText (szSize); nSize = atol(szSize);
		nPercent = ((float)nSize * 100.0f) / (float)nOriginalSize;
		szPercent.Format("%.2f", nPercent); wndPercent->SetWindowText(szPercent);
		break;
	}

	if ((this->m_Ratio.GetCheck() == BST_CHECKED) && (bIgnoreFocus == false))
	{
		switch (elem)
		{
		case Element::Width: 
			this->m_Heightp.SetWindowText (szPercent); 
			this->ValidateElements (Element::Height, ElementType::Percent, true); break;
		case Element::Height: 
			this->m_Widthp.SetWindowText (szPercent);
			this->ValidateElements (Element::Width, ElementType::Percent, true); break;
		}
	}
}


void CResample::OnBnClickedRatio()
{
	if (this->m_Ratio.GetCheck() != BST_CHECKED) return;

	CString szPercent; this->m_Widthp.GetWindowText (szPercent);
	this->m_Heightp.SetWindowText (szPercent);
	this->ValidateElements (Element::Height, ElementType::Percent, true);
}
