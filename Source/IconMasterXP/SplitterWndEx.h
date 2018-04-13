
#pragma once


// CSplitterWndEx

class CSplitterWndEx : public CSplitterWnd
{
	DECLARE_DYNAMIC(CSplitterWndEx)

public:
	CSplitterWndEx();
	virtual ~CSplitterWndEx();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);
};


