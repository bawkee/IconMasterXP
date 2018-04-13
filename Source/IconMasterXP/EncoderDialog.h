#pragma once
#include "afxwin.h"


// CEncoderDialog dialog

class CEncoderDialog : public CDialog
{
	DECLARE_DYNAMIC(CEncoderDialog)

public:
	CEncoderDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEncoderDialog();

// Dialog Data
	enum { IDD = IDD_FORMATS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_wndEncoders;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLbnDblclkEncoders();
	int m_nEncoder;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCshowhelp();
};
