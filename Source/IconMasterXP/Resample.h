#pragma once
#include "afxwin.h"
#include "AmsEdit.h"

// CResample dialog

class CResample : public CDialog
{
	DECLARE_DYNAMIC(CResample)

public:
	CResample(CWnd* pParent = NULL);   // standard constructor
	virtual ~CResample();

// Dialog Data
	enum { IDD = IDD_RESAMPLE };

	enum Element {Width, Height};
	enum ElementType {Percent, Size};

private:
	void ValidateElements(CResample::Element elem, CResample::ElementType type, bool bIgnoreFocus = false);
	void ValidateSizeVariables ();

public:
	CxImage::InterpolationMethod m_dwInterpolation;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	long m_nWidth;
	long m_nHeight;
	long m_nWidthO;
	long m_nHeightO;
	CString m_szWidthO;
	CString m_szHeightO;
	CListBox m_wndSizes;
	afx_msg void OnEnSetfocusWidth();
	afx_msg void OnEnSetfocusHeight();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnLbnSelchangeSizes();
	CComboBox m_wndAntialias;
	int m_nAntialias;
	afx_msg void OnCbnSelendokAntialias();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnDblclkSizes();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedCshowhelp();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CEdit m_Width;
	CEdit m_Height;
	CAMSNumericEdit m_Widthp;
	CAMSNumericEdit m_Heightp;
	CButton m_Ratio;
	afx_msg void OnEnChangeWidth();
	afx_msg void OnEnChangeHeight();
	afx_msg void OnEnChangeWidthp();
	afx_msg void OnEnChangeHeightp();
	afx_msg void OnBnClickedRatio();
	float m_nWidthp;
	float m_nHeightp;
};
