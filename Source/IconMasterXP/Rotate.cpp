// Rotate.cpp : implementation file
//

#include "stdafx.h"
#include "IconMasterXP.h"
#include "Rotate.h"
#include ".\rotate.h"


// CRotate dialog

IMPLEMENT_DYNAMIC(CRotate, CDialog)
CRotate::CRotate(CWnd* pParent /*=NULL*/)
	: CDialog(CRotate::IDD, pParent)
	, m_nAngle(0)
	, m_bKeepSize(FALSE)
{
}

CRotate::~CRotate()
{
}

void CRotate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ANGLE, m_nAngle);
	DDX_Control(pDX, IDC_ANTIALIAS, m_wndAntialias);
	DDX_Check(pDX, IDC_KEEPSIZE, m_bKeepSize);
}


BEGIN_MESSAGE_MAP(CRotate, CDialog)
//	ON_WM_ACTIVATE()
	ON_CBN_SELENDOK(IDC_ANTIALIAS, OnCbnSelendokAntialias)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDCSHOWHELP, OnBnClickedCshowhelp)
END_MESSAGE_MAP()


// CRotate message handlers


void CRotate::OnCbnSelendokAntialias()
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

void CRotate::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	/* :o ima m0r0n ->
	CEdit * ed = (CEdit*)this->GetDlgItem (IDC_ANGLE);
	CString szBuf;

	ed->GetWindowText (szBuf);

	if (atol(szBuf) <
	*/
	OnOK();
}

void CRotate::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	while (m_wndAntialias.GetCount () > 0)
		m_wndAntialias.DeleteString (0);

	m_wndAntialias.InsertString (0, "No Antialias");
	m_wndAntialias.InsertString (1, "Bilinear");
	m_wndAntialias.InsertString (2, "Bicubic");
	m_wndAntialias.InsertString (3, "BSpline");
	m_wndAntialias.InsertString (4, "Lanzcos");
	m_wndAntialias.InsertString (5, "Hermite");

	m_wndAntialias.SetCurSel(0);
}

void CRotate::OnBnClickedCshowhelp()
{
	CString szFile = CString(((CIconMasterXPApp*)::AfxGetApp())->GetHelpFile()) + ">wnd_context";
	::HtmlHelp (this->m_hWnd, szFile, 
		HH_HELP_CONTEXT, IDH_ROTATE);
}
