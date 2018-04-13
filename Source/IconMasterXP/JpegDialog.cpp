// JpegDialog.cpp : implementation file
//

#include "stdafx.h"
#include "IconMasterXP.h"
#include "JpegDialog.h"
#include ".\jpegdialog.h"


// CJpegDialog dialog

IMPLEMENT_DYNAMIC(CJpegDialog, CDialog)
CJpegDialog::CJpegDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CJpegDialog::IDD, pParent)
	, m_nCompression(0)
	, m_bProgressive(FALSE)
	, m_bOptimize(FALSE)
{
}

CJpegDialog::~CJpegDialog()
{
}

void CJpegDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPRESSION, m_wndCompression);
	DDX_Slider(pDX, IDC_COMPRESSION, m_nCompression);
	DDX_Check(pDX, IDC_PROGRESSIVE, m_bProgressive);
	DDX_Check(pDX, IDC_OPTIMIZE, m_bOptimize);
}


BEGIN_MESSAGE_MAP(CJpegDialog, CDialog)
	ON_WM_HSCROLL()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDCSHOWHELP, OnBnClickedCshowhelp)
END_MESSAGE_MAP()


// CJpegDialog message handlers

void CJpegDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl * wnd = (CSliderCtrl*)pScrollBar;
	CString szC;
	int h=0, s=0;

	szC.Format ("Compression level: %d%%", wnd->GetPos ());
	CWnd * st = this->GetDlgItem (IDC_COMPRESSIONSTATUS);
	st->SetWindowText (szC);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CJpegDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	m_wndCompression.SetRangeMax (100);
	m_wndCompression.SetPos (m_nCompression);

	CString szC;
	szC.Format ("Compression level: %d%%", m_wndCompression.GetPos ());
	CWnd * st = this->GetDlgItem (IDC_COMPRESSIONSTATUS);
	st->SetWindowText (szC);
}

void CJpegDialog::OnBnClickedCshowhelp()
{
	CString szFile = CString(((CIconMasterXPApp*)::AfxGetApp())->GetHelpFile()) + ">wnd_context";
	::HtmlHelp (this->m_hWnd, szFile, 
		HH_HELP_CONTEXT, IDH_EXPORTING);
}
