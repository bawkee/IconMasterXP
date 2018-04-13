// EncoderDialog.cpp : implementation file
//

#include "stdafx.h"
#include "IconMasterXP.h"
#include "EncoderDialog.h"
#include ".\encoderdialog.h"


// CEncoderDialog dialog

IMPLEMENT_DYNAMIC(CEncoderDialog, CDialog)
CEncoderDialog::CEncoderDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEncoderDialog::IDD, pParent)
	, m_nEncoder(0)
{
}

CEncoderDialog::~CEncoderDialog()
{
}

void CEncoderDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ENCODERS, m_wndEncoders);
	DDX_LBIndex(pDX, IDC_ENCODERS, m_nEncoder);
}


BEGIN_MESSAGE_MAP(CEncoderDialog, CDialog)
//	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_LBN_DBLCLK(IDC_ENCODERS, OnLbnDblclkEncoders)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCSHOWHELP, OnBnClickedCshowhelp)
END_MESSAGE_MAP()


// CEncoderDialog message handlers


void CEncoderDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if (m_wndEncoders)
	{
		while (m_wndEncoders.GetCount () > 0)
			m_wndEncoders.DeleteString (0);

		m_wndEncoders.InsertString (0,"Portable Network Graphics (*.png)");
		m_wndEncoders.InsertString (1,"Windows Bitmaps (*.bmp)");
		m_wndEncoders.InsertString (2,"Wireless Bitmaps (*.wbmp)");
		m_wndEncoders.InsertString (3,"Windows Icons (*.ico)");
		m_wndEncoders.InsertString (4,"Tagged Image Format (*.tif; *.tiff)");
		m_wndEncoders.InsertString (5,"Targa Bitmaps (*.tga)");
		m_wndEncoders.InsertString (6,"ZSoft Paintbrush Graphics (*.pcx)");
		m_wndEncoders.InsertString (7,"Windows Metafile (*.wmf)");
		m_wndEncoders.InsertString (8,"Enhanced Windows Metafile (*.emf)");
		m_wndEncoders.InsertString (9,"Joint Photographic Experts Group Format (*.jpg; *.jpeg)");
		m_wndEncoders.InsertString (10,"JPEG 2000 Format (*.jp2; *.j2k)");
		m_wndEncoders.InsertString (11,"Portable Pixmap Format (*.pnm)");
	}

	m_wndEncoders.SetCurSel (GetInt("export_individual_encoder",3));
}

void CEncoderDialog::OnLbnDblclkEncoders()
{
	if (m_wndEncoders.GetCurSel ()>=0)
		this->OnOK ();
}

void CEncoderDialog::OnBnClickedOk()
{
	if (m_wndEncoders.GetCurSel () < 0)
	{
		MessageBox ("Please select some of the available encoders, in the list to the right. Your exported images will be saved in that format.", "Information", MB_OK|MB_ICONINFORMATION);
		return;
	}

	OnOK();
}

void CEncoderDialog::OnBnClickedCshowhelp()
{
	CString szFile = CString(((CIconMasterXPApp*)::AfxGetApp())->GetHelpFile()) + ">wnd_context";
	::HtmlHelp (this->m_hWnd, szFile, 
		HH_HELP_CONTEXT, IDH_EXPORTING);
}
