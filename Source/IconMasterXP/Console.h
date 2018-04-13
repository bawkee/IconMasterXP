#pragma once
#include "afxwin.h"


// CConsole dialog

class CConsole : public CDialog
{
	DECLARE_DYNAMIC(CConsole)

public:
	CConsole(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConsole();

// Dialog Data
	enum { IDD = IDD_CONSOLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_wndOut;
	CEdit m_wndIn;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnSetfocusIn();
};
