#pragma once


// CPaletteEd dialog

class CPaletteEd : public CDialog
{
	DECLARE_DYNAMIC(CPaletteEd)

public:
	CPaletteEd(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPaletteEd();

// Dialog Data
	enum { IDD = IDD_PALETTE };

	RGBQUAD *	m_rgbPal;
	int			m_nColors;

private:
	int			m_nSelCol;
	BOOL			m_bValidPoint;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedCshowhelp();
};
