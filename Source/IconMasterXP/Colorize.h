#pragma once
#include "afxcmn.h"


// CColorize dialog

class CColorize : public CDialog
{
	DECLARE_DYNAMIC(CColorize)

public:
	CColorize(CWnd* pParent = NULL);   // standard constructor
	virtual ~CColorize();

// Dialog Data
	enum { IDD = IDD_COLORIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_wndHue;
	CSliderCtrl m_wndSat;
	CSliderCtrl m_wndBlend;
	int m_nHue;
	int m_nSat;
	int m_nBlend;
	RGBQUAD m_Color; // HSL value
	afx_msg void OnPaint();
	afx_msg void OnBnClickedSelect();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnStnClickedColor();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedHelp();
};
