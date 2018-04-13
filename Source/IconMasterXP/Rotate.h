#pragma once
#include "afxwin.h"


// CRotate dialog

class CRotate : public CDialog
{
	DECLARE_DYNAMIC(CRotate)

public:
	CRotate(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRotate();

// Dialog Data
	enum { IDD = IDD_ROTATE };

public:
	CxImage::InterpolationMethod m_dwInterpolation;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_nAngle;
	CComboBox m_wndAntialias;
	afx_msg void OnCbnSelendokAntialias();
	afx_msg void OnBnClickedOk();
	BOOL m_bKeepSize;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedCshowhelp();
};
