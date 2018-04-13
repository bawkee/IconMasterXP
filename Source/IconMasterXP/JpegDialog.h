#pragma once
#include "afxcmn.h"


// CJpegDialog dialog

class CJpegDialog : public CDialog
{
	DECLARE_DYNAMIC(CJpegDialog)

public:
	CJpegDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CJpegDialog();

// Dialog Data
	enum { IDD = IDD_JPEG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_wndCompression;
	int m_nCompression;
	BOOL m_bProgressive;
	BOOL m_bOptimize;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedCshowhelp();
};
