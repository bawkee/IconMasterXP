// IconView.h : interface of the CIconView class
//
// This is the bottom pane, a list of icons

#pragma once

#include "MWnd.h"

class CIconView : public CListView
{
protected: // create from serialization only
	CIconView();
	DECLARE_DYNCREATE(CIconView)

// Attributes
public:
	CDoc* GetDocument() const;

// Operations
public:
	CIconEditor * GetIconEditor ();

protected:
	CMWnd * GetMainWnd ();

// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CIconView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CMenu m_ItemPopup;
	CxImage m_ItemIco[4];

	HFONT m_hfntViewBold;
	HFONT m_hfntViewRegular;
	HFONT m_hfntViewItalic;

// Generated message map functions
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditRemoveitem();
	afx_msg void OnUpdateEditRemoveitem(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditSelectAll(CCmdUI *pCmdUI);
	afx_msg void OnEditSelectall();
	afx_msg void OnUpdateEditSelectall(CCmdUI *pCmdUI);
	afx_msg void OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
public:
	afx_msg void OnLvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	UINT m_nLvTimer;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in IconView.cpp
inline CDoc* CIconView::GetDocument() const
   { return reinterpret_cast<CDoc*>(m_pDocument); }
#endif

