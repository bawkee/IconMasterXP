// SplitterWndEx.cpp : implementation file
//

#include "stdafx.h"
#include "IconMasterXP.h"
#include "SplitterWndEx.h"

// CSplitterWndEx

IMPLEMENT_DYNAMIC(CSplitterWndEx, CSplitterWnd)

CSplitterWndEx::CSplitterWndEx()
{

}

CSplitterWndEx::~CSplitterWndEx()
{
}


BEGIN_MESSAGE_MAP(CSplitterWndEx, CSplitterWnd)
END_MESSAGE_MAP()



// CSplitterWndEx message handlers




void CSplitterWndEx::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect)
{
	// TODO: Add your specialized code here and/or call the base class

	if (pDC == NULL)
	{
		RedrawWindow(rect, NULL, RDW_INVALIDATE|RDW_NOCHILDREN);
		return;
	}
	
	if (!IsAppThemed())
	{
		CSplitterWnd::OnDrawSplitter(pDC, nType, rect);
		return;
	}

	//HTHEME theme = OpenThemeData(this->m_hWnd, L"ControlPanel");

	CBrush brushBack(GetSysColor(COLOR_WINDOW));

	if (nType == CSplitterWnd::ESplitType::splitBar)
	{
		CPen penSizeLine(PS_SOLID, 1, GetSysColor(COLOR_ACTIVEBORDER));

		int nCenterY = rect.top + ((rect.bottom - rect.top) / 2);

		pDC->FillRect(rect, &brushBack);
		pDC->SelectObject(penSizeLine);
		pDC->MoveTo(rect.left, nCenterY);
		pDC->LineTo(rect.right, nCenterY);
		//DrawThemeBackground(theme, pDC->m_hDC, 3, 2, &rect, NULL);
		
		penSizeLine.DeleteObject();
	}
	else if (nType == CSplitterWnd::ESplitType::splitBorder)
	{
		CPen penBorder(PS_SOLID, 2, GetSysColor(COLOR_WINDOW) /*RGB(255,0,0)*/);
		POINT ptsBorder[] = 
		{
			{rect.left, rect.top+1},
			{rect.right-1, rect.top+1},
			{rect.right-1, rect.bottom-1},
			{rect.left+1, rect.bottom-1},
			{rect.left+1, rect.top}
		};

		pDC->SelectObject(penBorder);
		pDC->Polyline(ptsBorder, 5);
		
		penBorder.DeleteObject();
	}

	brushBack.DeleteObject();

	//CloseThemeData(theme);
}
