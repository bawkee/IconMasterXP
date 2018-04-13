// ProgressDialog.cpp : implementation file
//

#include "stdafx.h"
#include "IconMasterXP.h"
#include "MWnd.h"
#include "ProgressDialog.h"
#include ".\progressdialog.h"


// CProgressDialog dialog

IMPLEMENT_DYNAMIC(CProgressDialog, CDialog)
CProgressDialog::CProgressDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDialog::IDD, pParent)
{
	m_Index=1;
}

CProgressDialog::~CProgressDialog()
{
}

void CProgressDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_Prog);
	DDX_Control(pDX, IDC_STAT, m_Stat);
}


BEGIN_MESSAGE_MAP(CProgressDialog, CDialog)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CProgressDialog message handlers

void CProgressDialog::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	CRect rtm, rtt;

	((CMWnd*)::AfxGetMainWnd())->GetWindowRect (&rtm);
	GetClientRect (&rtt);

	this->SetWindowPos (NULL, 
		rtm.right-((rtm.right-rtm.left)/2) - rtt.right/2,
		(rtm.bottom-((rtm.bottom-rtm.top)/2) - ((rtt.bottom/2)*(m_Index+2)))+rtt.bottom*3, 0,0, SWP_NOSIZE);
}
