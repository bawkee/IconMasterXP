#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CProgressDialog dialog

class CProgressDialog : public CDialog
{
	DECLARE_DYNAMIC(CProgressDialog)

public:
	CProgressDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProgressDialog();

// Dialog Data
	enum { IDD = IDD_PROGRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_Prog;
	int m_Index;
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	CStatic m_Stat;
};
