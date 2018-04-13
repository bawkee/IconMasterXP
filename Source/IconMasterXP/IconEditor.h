// IconEditor.h : interface of the CIconEditor class
//
// This is a top pane, serves as icon preview. 2018 me to 2005 me: CTreeView? What was my intention with tree view for icon preview? No idea.

#pragma once

#define IE_ACTION_FLIP				0x00000004
#define IE_ACTION_MIRROR			0x00000008

#define IE_ACTION_1BPP				0x00000010
#define IE_ACTION_4BPP				0x00000020
#define IE_ACTION_8BPP				0x00000040
#define IE_ACTION_24BPP				0x00000080
#define IE_ACTION_32BPP				0x00000100

#define IE_ACTION_REMOVETRANS		0x00000200
#define IE_ACTION_SETTRANS			0x00000400
#define IE_ACTION_PICKTRANS		0x01000000

#define IE_FILTER_GAMMA				0x00000800
#define IE_FILTER_THRESHOLD		0x00001000
#define IE_FILTER_CONTRAST			0x00002000
#define IE_FILTER_LIGHT				0x00004000
#define IE_FILTER_INTERACTIVETH	0x00008000
#define IE_FILTER_SOFTEN			0x00010000
#define IE_FILTER_SHARPEN			0x00020000
#define IE_FILTER_NEGATIVE			0x00040000
#define IE_FILTER_COLORIZE			0x00080000
#define IE_FILTER_EDGE				0x00100000

#define IE_ACTION_REVERT			0x00200000
#define IE_ACTION_CREPLACE			0x00400000
#define IE_ACTION_DUPLICATE		0x00800000

#include "MWnd.h"

class CDoc;

class CIconEditor : public CTreeView
{
protected: // create from serialization only
	CIconEditor();
	DECLARE_DYNCREATE(CIconEditor)

// Attributes
public:
	CDoc* GetDocument();

// Operations
public:
	void Resample();
	void CIconEditor::Zoom (int x);
	void Rotate ();
	
	void CustomAction (DWORD dwAction, DWORD dwParam1);
	void CustomAction (DWORD dwAction) {
		CustomAction (dwAction, 0);
	};

	void GetMouseXY (int * nx, int * ny, CPoint &point);


	CMWnd * GetMainWnd ();
	CIcoImage * GetSelectedImage ();

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CIconEditor();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	int m_nZoom;
	HCURSOR m_hPicker;
	RGBQUAD m_crTransparent;
	long m_nTransparent;
	BOOL m_bPicker;
	BOOL m_bInteractive;
	BOOL m_bClose;
	BOOL m_ZoomAlias;
	HBRUSH m_hPatBrush;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnNcPaint();
//	virtual void PreSubclassWindow();
//	afx_msg void OnNcPaint();
};

#ifndef _DEBUG  // debug version in IconEditor.cpp
inline CDoc* CIconEditor::GetDocument()
   { return reinterpret_cast<CDoc*>(m_pDocument); }
#endif

