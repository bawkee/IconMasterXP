#pragma once
#include "hyperlink.h"
#include "afxwin.h"


// CAppAbout dialog

class CAppAbout : public CDialog
{
	DECLARE_DYNAMIC(CAppAbout)

public:
	CAppAbout(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAppAbout();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

public:
	CxImage m_Img;
	CDC m_hdcBuf;
	CBrush m_brBack;
	HBITMAP m_hbmpBuf;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//CHyperLink m_urlTheAlas;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CEdit m_Credits;
};
