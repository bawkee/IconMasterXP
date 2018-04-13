// MWnd.h : interface of the CMWnd class
//
// This is the main window.

#include "Spawn.h"
#include "Console.h"
#include "SplitterWndEx.h"

#pragma once

#define ICON_ORDER_BITCOUNT	<
#define ICON_ORDER_SIZE			>

#define BACK_PATTERN		0x0
#define BACK_COLOR		0x1

class CPSDSpawnConsumer;
class CIconView;

class CPSDSpawnConsumer: public CSpawnConsumer
{
public:
	CPSDSpawnConsumer() 
	{
		b_Interrupt=FALSE;
	}

	void Consume(TCHAR* p, DWORD)
	{
		m_szOut.Append (CString("\r\n" + CString(p)));
		if (!m_Spawn->IsExecuting ()) m_bBusy=FALSE;

		TRACE1("CONSOLE:%s\n", p);
		//if (!m_bBusy)
		//{
			//m_wndOut->m_wndOut.SetWindowText (m_szOut);
			//m_wndOut->m_wndOut.SetSel(-1, -1, FALSE);
		//}
		Append(p);
	}	

	void Append (TCHAR* p)
	{
		m_wndOut->m_wndOut.SetSel(-1, -1, TRUE);
		m_wndOut->m_wndOut.ReplaceSel(p);
	}

	void __cdecl fa( LPSTR fmt, ... )
	{
		char    buff[512];
		va_list  va;

		va_start(va, fmt);

		// format message with header
		lstrcpy( buff, "" );
		wvsprintf( &buff[lstrlen(buff)], fmt, va );
		lstrcat( buff, "\r\n" );

		Append( buff );
	}

public:
	CConsole * m_wndOut;
	CString m_szOut;
	CSpawn * m_Spawn;
	BOOL m_bBusy;
	BOOL b_Interrupt;
};

class CMWnd : public CFrameWnd
{
protected: // create from serialization only
	CMWnd();
	DECLARE_DYNCREATE(CMWnd)

// Attributes
public:
	CSplitterWndEx m_wndSplitter;

// Operations
public:
	void InsertImageIntoView (CString szName, CIcoImage * img, DWORD nIndex);
	void ImportImages (CArray<CString, CString> * files);
	CxImage * InsertImage (CString szPath, int nFrame);
	CxImage * InsertImage (CString szPath) {
		return InsertImage(szPath, 0);
	};

	void SortImages ();
	void SwapImages (int x, int y);
	void RefreshView ();
	void ChangeIdlePaneText();

protected:
	CIconView * CMWnd::GetIconView ();
	void UpdateBitCount(CCmdUI *pCmdUI);
	

// Overrides
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMWnd();
	CIconView* GetRightPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar							m_wndStatusBar;
	CToolBar								m_wndToolBar;
	CReBar								m_wndReBar;
	CDialogBar							m_wndDlgBar;
	CImageList							m_imlTlb;
	CImageList							m_imlLv;

	BOOL			m_bMultiPage;
	BOOL			m_bDontExportInvalid;
	int			m_nCompression;
	int			m_dwOptions;

	UINT			m_nView;

public:
	CArray <CIcoImage, CIcoImage>		m_Imported;	
	CArray <CIcoImage, CIcoImage>		m_Actions;	// For undo/redo mostly

	CPSDSpawnConsumer					m_scPSD;
	CSpawn								m_sConsole;
	CConsole								m_wndConsole;

	DWORD									m_dwBackColor;
	int									m_nBackground;

	BOOL									m_bBusy;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
	afx_msg void OnFileImport();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnTransparentcolorPickfromimage();
	afx_msg void OnTransparentcolorRemove();
	afx_msg void OnTransparentcolorWritergbvalues();
	afx_msg void OnUpdateTransparentcolorWritergbvalues(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTransparentcolorPickfromimage(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTransparentcolorRemove(CCmdUI *pCmdUI);

	///////
	afx_msg void OnUpdateEditMirror(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditFlip(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditTransparentColor(CCmdUI *pCmdUI);
	afx_msg void OnGammaIncrease();
	afx_msg void OnGammaDecrease();
	afx_msg void OnLightIncrease();
	afx_msg void OnLightDecrease();
	afx_msg void OnContrastIncrease();
	afx_msg void OnContrastDecrease();
	afx_msg void OnFiltersThreshold();
	afx_msg void OnThresholdInteractive();
	afx_msg void OnBit24bit();
	afx_msg void OnBit8bit();
	afx_msg void OnBit4bit();
	afx_msg void OnBit2bit();
	afx_msg void OnUpdateEditResize(CCmdUI *pCmdUI);
	afx_msg void OnEditResize();
	afx_msg void OnZoomX4();
	afx_msg void OnZoomX3();
	afx_msg void OnZoomX2();
	afx_msg void OnZoom1();
	afx_msg void OnEditMirror();
	afx_msg void OnEditFlip();
	afx_msg void OnEditRotate();
	afx_msg void OnUpdateZoom(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditRotate(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFiltersThreshold(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGammaIncrease(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLightIncrease(CCmdUI *pCmdUI);
	afx_msg void OnUpdateContrastIncrease(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFiltersSoften(CCmdUI *pCmdUI);
	afx_msg void OnUpdateThresholdInteractive(CCmdUI *pCmdUI);
	afx_msg void OnFiltersSharpen();
	afx_msg void OnFiltersEdge();
	afx_msg void OnFiltersNegative();
	afx_msg void OnFiltersColorize();
	afx_msg void OnFiltersSoften();
	afx_msg void OnUpdateFiltersSharpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFiltersEdge(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFiltersNegative(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFiltersColorize(CCmdUI *pCmdUI);

	///////
	afx_msg void OnClose();
	afx_msg void OnUpdateBit32bit(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBit24bit(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBit8bit(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBit4bit(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBit2bit(CCmdUI *pCmdUI);
	afx_msg void OnFileExport();
	afx_msg void OnFileMulti();
	afx_msg void OnUpdateFileMulti(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileExport(CCmdUI *pCmdUI);
	afx_msg void OnFileJpegsettings();
	afx_msg void OnBitTips();
	afx_msg void OnEditRevert();
	afx_msg void OnUpdateEditRevert(CCmdUI *pCmdUI);
	afx_msg void OnEditReplacecolors();
	afx_msg void OnUpdateEditReplacecolors(CCmdUI *pCmdUI);
	afx_msg void OnEditDuplicate();
	afx_msg void OnUpdateEditDuplicate(CCmdUI *pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnZoomEnableanti();
	afx_msg void OnUpdateZoomEnableanti(CCmdUI *pCmdUI);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnViewConsole();
	afx_msg void OnHelp();
//	afx_msg void OnHelpHowtobuyfullversion();
	afx_msg void OnTransparentcolorHelp();
	afx_msg void OnThresholdHelp();
	afx_msg void OnEditPalette();
	afx_msg void OnUpdateEditPalette(CCmdUI *pCmdUI);
	afx_msg void OnBackgroundPattern();
	afx_msg void OnBackgroundColor();
	afx_msg void OnBackgroundEditcolor();
	afx_msg void OnUpdateBackgroundPattern(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBackgroundColor(CCmdUI *pCmdUI);
	afx_msg void OnFileDon();
	afx_msg void OnUpdateFileDon(CCmdUI *pCmdUI);
	afx_msg void OnDropFiles(HDROP hDropInfo);
};



