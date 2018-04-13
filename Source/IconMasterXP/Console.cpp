// Console.cpp : implementation file
//

#include "stdafx.h"
#include "IconMasterXP.h"
#include "MWnd.h"
#include "Console.h"
#include ".\console.h"


// CConsole dialog

IMPLEMENT_DYNAMIC(CConsole, CDialog)
CConsole::CConsole(CWnd* pParent /*=NULL*/)
	: CDialog(CConsole::IDD, pParent)
{
}

CConsole::~CConsole()
{
}

void CConsole::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OUT, m_wndOut);
	DDX_Control(pDX, IDC_IN, m_wndIn);
}


BEGIN_MESSAGE_MAP(CConsole, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_SETFOCUS(IDC_IN, OnEnSetfocusIn)
END_MESSAGE_MAP()


// CConsole message handlers

void CConsole::OnBnClickedOk()
{
	CMWnd * wnd = (CMWnd*)::AfxGetMainWnd();
	CString szIn;

	m_wndIn.GetWindowText (szIn);

	if (szIn.GetLength() <= 0)
	{
		MessageBox ("You must type a command to execute.\nType HELP for a list of commands.", "Execute", MB_OK|MB_ICONINFORMATION);
		return;
	}

	if (wnd->m_sConsole.IsExecuting ())
	{
		szIn += "\n";
		wnd->m_sConsole.SendInput (szIn);
	}
	else
	{
		wnd->m_sConsole.Execute (szIn, &wnd->m_scPSD, TRUE);
	}

	m_wndIn.SetWindowText ("");
}

void CConsole::OnEnSetfocusIn()
{
	CString szOut;
	m_wndOut.GetWindowText (szOut);
	m_wndOut.SetSel (szOut.GetLength(), -1);
	
}
