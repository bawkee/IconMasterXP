// MWnd.cpp : implementation of the CMWnd class
//

#include "stdafx.h"
#include "IconMasterXP.h"

#include "FolderDlg.h"
#include "EncoderDialog.h"
#include "JpegDialog.h"
//#include <freeimageplus.h>

#include "Console.h"

#include "IconEditor.h"
#include "IconView.h"
#include "ProgressDialog.h"
#include "PaletteEd.h"

#include "Spawn.h"
#include "MWnd.h"
#include ".\mwnd.h"
//#include "Doc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMWnd

IMPLEMENT_DYNCREATE(CMWnd, CFrameWnd)

BEGIN_MESSAGE_MAP(CMWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnViewStyle)
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_IMPORT, OnFileImport)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_TRANSPARENTCOLOR_PICKFROMIMAGE, OnTransparentcolorPickfromimage)
	ON_COMMAND(ID_TRANSPARENTCOLOR_REMOVE, OnTransparentcolorRemove)
	ON_COMMAND(ID_TRANSPARENTCOLOR_WRITERGBVALUES, OnTransparentcolorWritergbvalues)
	ON_UPDATE_COMMAND_UI(ID_TRANSPARENTCOLOR_WRITERGBVALUES, OnUpdateTransparentcolorWritergbvalues)
	ON_UPDATE_COMMAND_UI(ID_TRANSPARENTCOLOR_PICKFROMIMAGE, OnUpdateTransparentcolorPickfromimage)
	ON_UPDATE_COMMAND_UI(ID_TRANSPARENTCOLOR_REMOVE, OnUpdateTransparentcolorRemove)

	///////
	ON_UPDATE_COMMAND_UI(ID_EDIT_MIRROR, OnUpdateEditMirror)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FLIP, OnUpdateEditFlip)
	ON_UPDATE_COMMAND_UI(ID_EDIT_TRANSPARENTCOLOR, OnUpdateEditTransparentColor)
	ON_COMMAND(ID_GAMMA_INCREASE, OnGammaIncrease)
	ON_COMMAND(ID_GAMMA_DECREASE, OnGammaDecrease)
	ON_COMMAND(ID_LIGHT_INCREASE, OnLightIncrease)
	ON_COMMAND(ID_LIGHT_DECREASE, OnLightDecrease)
	ON_COMMAND(ID_CONTRAST_INCREASE, OnContrastIncrease)
	ON_COMMAND(ID_CONTRAST_DECREASE, OnContrastDecrease)
	ON_COMMAND(ID_FILTERS_THRESHOLD, OnFiltersThreshold)
	ON_COMMAND(ID_THRESHOLD_INTERACTIVE, OnThresholdInteractive)
	ON_COMMAND(ID_BIT_24BIT, OnBit24bit)
	ON_COMMAND(ID_BIT_8BIT, OnBit8bit)
	ON_COMMAND(ID_BIT_4BIT, OnBit4bit)
	ON_COMMAND(ID_BIT_2BIT, OnBit2bit)
	ON_UPDATE_COMMAND_UI(ID_EDIT_RESIZE, OnUpdateEditResize)
	ON_COMMAND(ID_EDIT_RESIZE, OnEditResize)
	ON_COMMAND(ID_ZOOM_X4, OnZoomX4)
	ON_COMMAND(ID_ZOOM_X3, OnZoomX3)
	ON_COMMAND(ID_ZOOM_X2, OnZoomX2)
	ON_COMMAND(ID_ZOOM_1, OnZoom1)
	ON_COMMAND(ID_EDIT_MIRROR, OnEditMirror)
	ON_COMMAND(ID_EDIT_FLIP, OnEditFlip)
	ON_COMMAND(ID_EDIT_ROTATE, OnEditRotate)
	ON_UPDATE_COMMAND_UI_RANGE(ID_ZOOM_1, ID_ZOOM_X4, OnUpdateZoom)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ROTATE, OnUpdateEditRotate)
	ON_UPDATE_COMMAND_UI(ID_FILTERS_THRESHOLD, OnUpdateFiltersThreshold)
	ON_UPDATE_COMMAND_UI_RANGE(ID_GAMMA_INCREASE, ID_GAMMA_DECREASE, OnUpdateGammaIncrease)
	ON_UPDATE_COMMAND_UI_RANGE(ID_LIGHT_INCREASE, ID_LIGHT_DECREASE, OnUpdateLightIncrease)
	ON_UPDATE_COMMAND_UI_RANGE(ID_CONTRAST_INCREASE, ID_CONTRAST_DECREASE, OnUpdateContrastIncrease)
	ON_UPDATE_COMMAND_UI(ID_FILTERS_SOFTEN, OnUpdateFiltersSoften)
	ON_UPDATE_COMMAND_UI(ID_THRESHOLD_INTERACTIVE, OnUpdateThresholdInteractive)
	ON_COMMAND(ID_FILTERS_SHARPEN, OnFiltersSharpen)
	ON_COMMAND(ID_FILTERS_EDGE, OnFiltersEdge)
	ON_COMMAND(ID_FILTERS_NEGATIVE, OnFiltersNegative)
	ON_COMMAND(ID_FILTERS_COLORIZE, OnFiltersColorize)
	ON_COMMAND(ID_FILTERS_SOFTEN, OnFiltersSoften)
	ON_UPDATE_COMMAND_UI(ID_FILTERS_SHARPEN, OnUpdateFiltersSharpen)
	ON_UPDATE_COMMAND_UI(ID_FILTERS_EDGE, OnUpdateFiltersEdge)
	ON_UPDATE_COMMAND_UI(ID_FILTERS_NEGATIVE, OnUpdateFiltersNegative)
	ON_UPDATE_COMMAND_UI(ID_FILTERS_COLORIZE, OnUpdateFiltersColorize)
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_BIT_32BIT, OnUpdateBit32bit)
	ON_UPDATE_COMMAND_UI(ID_BIT_24BIT, OnUpdateBit24bit)
	ON_UPDATE_COMMAND_UI(ID_BIT_8BIT, OnUpdateBit8bit)
	ON_UPDATE_COMMAND_UI(ID_BIT_4BIT, OnUpdateBit4bit)
	ON_UPDATE_COMMAND_UI(ID_BIT_2BIT, OnUpdateBit2bit)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	ON_COMMAND(ID_FILE_MULTI, OnFileMulti)
	ON_UPDATE_COMMAND_UI(ID_FILE_MULTI, OnUpdateFileMulti)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT, OnUpdateFileExport)
	ON_COMMAND(ID_FILE_JPEGSETTINGS, OnFileJpegsettings)
	ON_COMMAND(ID_BIT_TIPS, OnBitTips)
	ON_COMMAND(ID_EDIT_REVERT, OnEditRevert)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REVERT, OnUpdateEditRevert)
	ON_COMMAND(ID_EDIT_REPLACECOLORS, OnEditReplacecolors)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REPLACECOLORS, OnUpdateEditReplacecolors)
	ON_COMMAND(ID_EDIT_DUPLICATE, OnEditDuplicate)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DUPLICATE, OnUpdateEditDuplicate)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_ZOOM_ENABLEANTI, OnZoomEnableanti)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_ENABLEANTI, OnUpdateZoomEnableanti)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_VIEW_CONSOLE, OnViewConsole)
	ON_COMMAND(ID_HELP, OnHelp)
//	ON_COMMAND(ID_HELP_HOWTOBUYFULLVERSION, OnHelpHowtobuyfullversion)
	ON_COMMAND(ID_TRANSPARENTCOLOR_HELP, OnTransparentcolorHelp)
	ON_COMMAND(ID_THRESHOLD_HELP, OnThresholdHelp)
	ON_COMMAND(ID_EDIT_PALETTE, OnEditPalette)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PALETTE, OnUpdateEditPalette)
	ON_COMMAND(ID_BACKGROUND_PATTERN, OnBackgroundPattern)
	ON_COMMAND(ID_BACKGROUND_COLOR, OnBackgroundColor)
	ON_COMMAND(ID_BACKGROUND_EDITCOLOR, OnBackgroundEditcolor)
	ON_UPDATE_COMMAND_UI(ID_BACKGROUND_PATTERN, OnUpdateBackgroundPattern)
	ON_UPDATE_COMMAND_UI(ID_BACKGROUND_COLOR, OnUpdateBackgroundColor)
	ON_COMMAND(ID_FILE_DON, OnFileDon)
	ON_UPDATE_COMMAND_UI(ID_FILE_DON, OnUpdateFileDon)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	//IDS_INFO,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

static TCHAR cszTlbStrings[512] 
	= "Import\0Export\0Delete\0Undo\0Transparent\0Resample\0Multipage\0Help";

// CMWnd construction/destruction

CMWnd::CMWnd()
{
	GetInt ("backgroundmode", &m_nBackground, BACK_COLOR);
	GetInt ("backcolor", (int*)&m_dwBackColor, RGB(255,255,255));
	GetInt ("dei", &m_bDontExportInvalid, FALSE);

	m_bBusy=FALSE;
	m_bMultiPage=FALSE;
}

CMWnd::~CMWnd()
{
}


int CMWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_imlTlb.Create (48, 48, ILC_COLOR32|ILC_MASK, 7, 8))
	{
		TRACE0("Failed to load 32bit icons for toolbars\n");
		return -1;
	}

	m_imlTlb.Add ((HICON)LoadImage (::AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_IMPORT), IMAGE_ICON, 48, 48, LR_CREATEDIBSECTION));
	m_imlTlb.Add ((HICON)LoadImage (::AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_EXPORT), IMAGE_ICON, 48, 48, LR_CREATEDIBSECTION));
	m_imlTlb.Add ((HICON)LoadImage (::AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_DELETE), IMAGE_ICON, 48, 48, LR_CREATEDIBSECTION));
	m_imlTlb.Add ((HICON)LoadImage (::AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_UNDO), IMAGE_ICON, 48, 48, LR_CREATEDIBSECTION));
	m_imlTlb.Add ((HICON)LoadImage (::AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_TRANSPARENT), IMAGE_ICON, 48, 48, LR_CREATEDIBSECTION));
	m_imlTlb.Add ((HICON)LoadImage (::AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_RESAMPLE), IMAGE_ICON, 48, 48, LR_CREATEDIBSECTION));
	m_imlTlb.Add ((HICON)LoadImage (::AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_MULTIPAGE), IMAGE_ICON, 48, 48, LR_CREATEDIBSECTION));
	m_imlTlb.Add ((HICON)LoadImage (::AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_HELP), IMAGE_ICON, 48, 48, LR_CREATEDIBSECTION));

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT|TBSTYLE_TRANSPARENT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	//m_wndToolBar.ShowWindow (GetInt("toolbar",1)==1?SW_SHOW:SW_HIDE);
	m_wndToolBar.GetToolBarCtrl ().SetButtonSize (CSize (57,74));
	m_wndToolBar.GetToolBarCtrl ().SetImageList (&m_imlTlb);	

	// Add buttons
	TBBUTTON btn;

	m_wndToolBar.GetToolBarCtrl ().AddStrings (cszTlbStrings);
	
	btn.fsState = TBSTATE_ENABLED;
	btn.fsStyle = TBSTYLE_BUTTON;

	btn.iString = 0;btn.iBitmap = 0;btn.idCommand = ID_FILE_IMPORT;
	m_wndToolBar.GetToolBarCtrl ().InsertButton (0, &btn);

	btn.iString = 1;btn.iBitmap = 1;btn.idCommand = ID_FILE_EXPORT;
	m_wndToolBar.GetToolBarCtrl ().InsertButton (1, &btn);

	btn.iString = 2;btn.iBitmap = 2;btn.idCommand = ID_EDIT_REMOVEITEM;
	m_wndToolBar.GetToolBarCtrl ().InsertButton (2, &btn);

	btn.iString = 3;btn.iBitmap = 3;btn.idCommand = ID_EDIT_UNDO;
	m_wndToolBar.GetToolBarCtrl ().InsertButton (3, &btn);

	btn.iString = 4;btn.iBitmap = 4;btn.idCommand = ID_TRANSPARENTCOLOR_PICKFROMIMAGE;
	m_wndToolBar.GetToolBarCtrl ().InsertButton (4, &btn);

	btn.iString = 5;btn.iBitmap = 5;btn.idCommand = ID_EDIT_RESIZE;
	m_wndToolBar.GetToolBarCtrl ().InsertButton (5, &btn);

	btn.iString = 6;btn.iBitmap = 6;btn.idCommand = ID_FILE_MULTI;
	m_wndToolBar.GetToolBarCtrl ().InsertButton (6, &btn);

	btn.iString = 7;btn.iBitmap = 7;btn.idCommand = ID_HELP;
	m_wndToolBar.GetToolBarCtrl ().InsertButton (7, &btn);


	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}
	this->ShowControlBar (&m_wndToolBar, GetInt("toolbar",1),FALSE);
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	//int parts[2]={50,-1};
	//m_wndStatusBar.GetStatusBarCtrl().SetParts (2, parts);
	//m_wndStatusBar.SetPaneText(1, "Omg uber!");
		//CStatusBarCtrl

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS );
	this->ShowControlBar (&m_wndStatusBar, GetInt("statusbar",1),FALSE);

	this->DragAcceptFiles();

	GetInt ("jpgc", &m_nCompression, 50);
	GetInt ("jpgo", &m_dwOptions, 0);

	return 0;
}

BOOL CMWnd::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 2, 1))
		return FALSE;
	
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CIconEditor), CSize(100, 100), pContext) ||
		!m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CIconView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	
	CListCtrl * lv = (CListCtrl*)&(((CIconView*)m_wndSplitter.GetPane (1, 0))->GetListCtrl ());
	CStringW wszGroup;

	SetWindowLong (lv->m_hWnd, GWL_STYLE,
		GetWindowLong (lv->m_hWnd, GWL_STYLE) |
		LVS_ICON | LVS_SHOWSELALWAYS | LVS_AUTOARRANGE | LVS_NOCOLUMNHEADER /* Only for tile view simulation */  );

	lv->SetView  (LV_VIEW_DETAILS); // Only change needed for view switch, and of course add/set proper icons 
	m_nView = LV_VIEW_TILE;

	lv->InsertColumn (0, "File Name", LVCFMT_LEFT, 450);
	lv->InsertColumn (1, "Size", LVCFMT_LEFT, 0);
	lv->InsertColumn (2, "Colors", LVCFMT_LEFT, 0);
	lv->InsertColumn (3, "Format", LVCFMT_LEFT, 0);
	
	if (!m_imlLv.Create (88, 88, ILC_COLOR32|ILC_MASK, 2, 3))
	{
		TRACE0("Failed to load 32bit icons for list view\n");
		return -1;
	}

	lv->SetImageList (&m_imlLv, LVSIL_NORMAL|LVSIL_SMALL);
		
	lv->EnableGroupView (TRUE);
	
	for (int f=0; f<5; ++f)
	{
		LVGROUP lvg;

		switch (f) {
			case 0: wszGroup.Format(L"32-bit Icons (24-bit with 8-bit alpha), Only Windows XP/2000 (NT5)"); break;
			case 1: wszGroup.Format(L"24-bit Icons (True Color), "); break;
			case 2: wszGroup.Format(L"8-bit Icons (Paletted, 256 Colors)"); break;
			case 3: wszGroup.Format(L"4-bit Icons (Standard VGA, 16 Colors)"); break;
			case 4: wszGroup.Format(L"1-bit Icons (Monochrome, No Colors)"); break;
		}
		
		ZeroMemory(&lvg, sizeof(lvg));
		lvg.cbSize = sizeof(lvg);
		lvg.mask = LVGF_HEADER | LVGF_GROUPID | LVGF_ALIGN;
		lvg.pszHeader = wszGroup.GetBuffer();
		lvg.cchHeader = (int)wcslen(lvg.pszHeader);
		lvg.iGroupId = f;
		lvg.uAlign = LVGA_HEADER_LEFT;
		lv->InsertGroup(f, &lvg);
	}

	m_wndConsole.Create (IDD_CONSOLE, this);
	m_scPSD.m_Spawn = &m_sConsole;
	m_scPSD.m_wndOut = &m_wndConsole;

	return TRUE;
}

BOOL CMWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~FWS_ADDTOTITLE;	
	//cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	return TRUE;
}


// CMWnd diagnostics

#ifdef _DEBUG
void CMWnd::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMWnd::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMWnd message handlers

CIconView* CMWnd::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CIconView* pView = DYNAMIC_DOWNCAST(CIconView, pWnd);
	return pView;
}

void CMWnd::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	if (!pCmdUI)
		return;

	// TODO: customize or extend this code to handle choices on the View menu

	CIconView* pView = GetRightPane(); 

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		// if the command is ID_VIEW_LINEUP, only enable command
		// when we're in LVS_ICON or LVS_SMALLICON mode

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// otherwise, use dots to reflect the style of the view
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}


void CMWnd::OnViewStyle(UINT nCommandID)
{
	// TODO: customize or extend this code to handle choices on the View menu
	CIconView* pView = GetRightPane();

	// if the right-hand pane has been created and is a CIconView,
	// process the menu commands...
	if (pView != NULL)
	{
		DWORD dwStyle = -1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// ask the list control to snap to grid
				CListCtrl& refListCtrl = pView->GetListCtrl();
				refListCtrl.Arrange(LVA_SNAPTOGRID);
			}
			break;

		// other commands change the style on the list control
		case ID_VIEW_DETAILS:
			dwStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			dwStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			dwStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			dwStyle = LVS_LIST;
			break;
		}

		// change the style; window will repaint automatically
		if (dwStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
}

void CMWnd::OnDestroy()
{
	CFrameWnd::OnDestroy();

	CRect rt;

	m_Imported.RemoveAll ();
	m_Actions.RemoveAll ();

	this->GetWindowRect (&rt);

	SaveInt ("dei", m_bDontExportInvalid);

	if (!::IsMaximized (this->m_hWnd))
	{
		::SaveInt ("x", rt.left);
		::SaveInt ("y", rt.top);
		::SaveInt ("r", rt.right-rt.left);
		::SaveInt ("b", rt.bottom-rt.top);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Import
////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMWnd::OnFileImport()
{
	CFileDialog * cf;
	CArray<CString, CString> files;
	TCHAR szBuf[10240]="";
	int fc=0;

	cf = (CFileDialog*)new CFileDialog (
		TRUE, 
		NULL,
		NULL,
		OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER,
		CxImage_GetFormatList (),
		NULL);

	//DESCRIPTION (*.EXT)|*.EXT
	GetStr ("import_folder", szBuf, "c:\\");
	cf->m_ofn.nFilterIndex = GetInt ("import_filter", 1);
	cf->m_ofn.lpstrFile = szBuf;
	cf->m_ofn.nMaxFile = sizeof(szBuf);
	cf->m_ofn.lpstrTitle = "Import Files";	

	if (cf->DoModal () != IDOK) {
		delete cf;
		m_bBusy = FALSE;
		return;
	}

	SaveInt ("import_filter", cf->m_ofn.nFilterIndex);
	SaveStr ("import_folder", szBuf);

	POSITION tfp = cf->GetStartPosition ();
	while (tfp)
	{
		files.Add(cf->GetNextPathName (tfp));
	}

	try
	{
		this->ImportImages(&files);
	}
	catch (CException * ex)
	{
		ex->ReportError();
		ex->Delete();
	}

	delete cf;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Import
////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMWnd::ImportImages (CArray<CString, CString> * files)
{
	CString szPath, szMsg;
	CProgressDialog wndProg[2];
	TCHAR szBuf[10240]="";
	int fc=files->GetCount();

	CIconView * iv = (CIconView*)m_wndSplitter.GetPane (1,0);

	if (iv->GetListCtrl ().GetItemCount () > 0)
	{
		if (MessageBox ("There are already some items in the list, remove them?", "Import", 
			MB_YESNO|MB_ICONQUESTION)==IDYES)
		{
			m_Imported.RemoveAll ();
			iv->GetListCtrl ().DeleteAllItems ();
		}
	}

	iv->GetIconEditor ()->RedrawWindow();

	this->EnableWindow(false);

	try
	{
		m_bBusy=TRUE;

		wndProg[0].Create (IDD_PROGRESS, this);
		wndProg[0].ShowWindow (SW_SHOW);
		wndProg[0].m_Prog.SetRange (0, fc);
		wndProg[0].m_Prog.SetPos (0);

		m_scPSD.m_szOut = "";
		m_scPSD.m_wndOut->m_wndOut.SetWindowText ("");

		/////////////////////////////////////////
		// Insert images

		for (int f=0; f < files->GetCount(); f++)
		{
			int c=(int)m_Imported.GetCount ();
			BOOL bFound=FALSE;

			szPath = files->GetAt(f);

			for (int i=0; i<c; ++i)
				if (szPath == m_Imported[i].m_FileName)
					bFound=TRUE; // Already exists

			if (bFound) continue;

			int nType = CxImage_FindType (szPath.Right (3));

			if (nType == ::CXIMAGE_FORMAT_UNKNOWN)
			{
				if (szPath.Right (3).MakeLower() != "psd")
				{
					szMsg.Format ("This program cannot import:\n%s\nUnrecognized format.", szPath);
					MessageBox (szMsg, "Import", MB_OK|MB_ICONSTOP);
					continue;
				}
			}

			CString szTitle = szPath.Right (szPath.GetLength () - 
				(szPath.ReverseFind ('\\')+1));

			wndProg[0].m_Stat.SetWindowText (szTitle);

			if (szTitle.Right (3).MakeLower() == "psd") {
				if (szTitle.Find (' ') > 0) {
					if (MessageBox ("Importer for PSD format does not support empty spaces in file names!\nCurrent file requested for importing contains empty space(s).\nDo you wish to continue?",
						"Warning", MB_YESNO|MB_ICONQUESTION) == IDYES)
						continue;
					else
						goto fin;
				}
			}

			if (!InsertImage (szPath))
				goto fin;

			if (!m_Imported[c].IsValid ())
			{
				szMsg.Format ("Unable to decode image:\n%s\nReturn code:\n%s", 
					szPath, m_Imported[c].GetLastError ());
				MessageBox (szMsg, "Import Error", MB_OK|MB_ICONSTOP);
				m_Imported.RemoveAt(c);
				goto fin;
			}

			MSG msg;

			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			/////////////////////////////////////////////////////
			// Everything is k, continue importing now
			int fc;
			if ((fc = m_Imported[c].GetNumFrames ()) > 1)	// Multipage file!
			{
				wndProg[1].Create (IDD_PROGRESS, &wndProg[0]);
				wndProg[1].ShowWindow (SW_SHOW);
				wndProg[1].m_Prog.SetRange (0, fc);
				wndProg[1].m_Prog.SetPos (0);
				wndProg[1].m_Index=2;

				for (int f=1; f<fc; ++f)
				{
					if (!InsertImage (szPath, f))
						goto fin;
				
					wndProg[1].m_Stat.SetWindowText ("Adding image pages...");
					wndProg[1].m_Prog.SetPos (wndProg[1].m_Prog.GetPos()+1);

					while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}

				wndProg[1].DestroyWindow ();
			}
			wndProg[0].m_Prog.SetPos (wndProg[0].m_Prog.GetPos()+1);
		}

	fin:
		m_bBusy = FALSE;

		if (!m_scPSD.b_Interrupt)
		{
			wndProg[0].m_Stat.SetWindowText ("Finishing...");
			RefreshView();
			this->EnableWindow(true);
			wndProg[0].DestroyWindow ();
		}
	}
	catch(CException* ex)
	{
		m_bBusy = FALSE;

		wndProg[0].DestroyWindow();
		wndProg[1].DestroyWindow();

		ex->ReportError();
		ex->Delete();
	}

	this->EnableWindow(true);

	if (m_scPSD.b_Interrupt) ::AfxGetApp()->CloseAllDocuments(TRUE);
}

void CMWnd::RefreshView ()
{
	CIconView * iv = (CIconView*)m_wndSplitter.GetPane (1,0);
	CListCtrl * lv = &iv->GetListCtrl ();
	CIcoImage * img = iv->GetIconEditor ()->GetSelectedImage ();
	CString szFile, szName;
	BOOL bSelect;
	int nFrame;

	lv->SetFocus ();

	if (lv->GetSelectedCount () <= 1)
		bSelect=TRUE;
	else
		bSelect=FALSE;

	if (img)
	{
		nFrame = img->GetFrame ();
		szFile = img->m_FileName;
		if (szFile.GetLength () > 0)
			szName = szFile.Right (szFile.GetLength () - 
				(szFile.ReverseFind ('\\')+1));
		else
			img = NULL;
	}

	m_bBusy = TRUE;

	try
	{
		lv->DeleteAllItems ();

		SortImages ();
	
		for (int i=0; i<m_Imported.GetCount(); ++i)
		{
			InsertImageIntoView (m_Imported[i].m_FileName, &m_Imported[i], i);
			m_Imported[i].dwID = i;
		}

		// Select image
		if (lv->GetItemCount () != m_Imported.GetCount ()) return;
		if (img && bSelect) 
		{
			for (int i=0; i<lv->GetItemCount (); ++i) {
				CString szLv;
			
				if (lv->GetItemText (i,0).GetLength () >= szName.GetLength ())
					szLv = lv->GetItemText (i,0).Left(szName.GetLength ());
				else
					continue;

				if (szLv ==szName) {
					if (m_Imported[lv->GetItemData (i)].GetFrame() == nFrame) {
						lv->EnsureVisible (i, FALSE);
						lv->SetSelectionMark (i);
						lv->SetItemState (i, LVIS_SELECTED, LVIS_SELECTED);
						break;
					}
				}
			}
		}
	}
	catch (CException * ex)
	{
		ex->ReportError();
		ex->Delete();
	}

	m_bBusy = FALSE;
}

CxImage * CMWnd::InsertImage (CString szPath, int nFrame)
{
	int nType = CxImage_FindType (szPath.Right (3));
	int nBpp;

	try
	{
		CIcoImage img;

		img.SetFrame (nFrame);

		if (szPath.Right (3).MakeLower () == "psd")
		{
			// omg, we need to make it PNG!

			CString szCD = GetAppPath();
			CString szNewPath;
			CString szFile = szPath.Right (szPath.GetLength () - 
				(szPath.ReverseFind ('\\')+1));
			CString szExec = "psd2png.exe " + szFile;
			CString szIMPath = ((CIconMasterXPApp*)::AfxGetApp())->m_szAppPath;
			BOOL bFatalErr=FALSE;
			BOOL bSuperUltraMegaGigaFatalErr=FALSE;

			m_scPSD.m_bBusy = TRUE;

			m_scPSD.fa("External import:%s", szExec);
			m_sConsole.Execute (szExec, &m_scPSD, FALSE);
			
			while (m_scPSD.m_bBusy && !m_scPSD.b_Interrupt)

			if (m_scPSD.b_Interrupt) 
				return NULL;
			

			/* Search for PNGs */
			WIN32_FIND_DATA FileData; 
			HANDLE hSearch; 
			BOOL bFinishedSearch=FALSE;

			hSearch = FindFirstFile(CString(szCD + "\\PNG\\*.PNG"), &FileData); 
			if (hSearch == INVALID_HANDLE_VALUE) 
			{ 
				bFatalErr=TRUE;
				goto ferr;
			} 

			while (!bFinishedSearch) 
			{ 
				CString szFilePNG (FileData.cFileName);
				
				if (szFilePNG.MakeLower() != "background.png")
				{
					szNewPath.Format ("%s\\%s\\%s", szCD, "PNG", szFilePNG);

					if (!img.Load (szNewPath, ::CXIMAGE_FORMAT_PNG))
					{
						return NULL;
					}
					if (!DeleteFile (szNewPath))
						m_scPSD.fa("Failed to delete %s", szNewPath);
				}

				if (!FindNextFile(hSearch, &FileData)) 
				{
					if (GetLastError() == ERROR_NO_MORE_FILES) 
						bFinishedSearch = TRUE; 
					else 
					{ 
						MessageBox ("Critical failure occured during external conversion!\nPlease check converter console output.", "Error", MB_OK|MB_ICONSTOP);
						bFatalErr=TRUE;
						bSuperUltraMegaGigaFatalErr=TRUE; // <--- TEH OMG!
						goto ferr;
					} 
				}
			} 

			FindClose(hSearch);
			/* Finished searching */

			if (!::RemoveDirectory (CString(szCD + "\\PNG")))
				m_scPSD.fa("Failed to remove the temporary directory.");

ferr:
			if (bFatalErr)
			{
				m_scPSD.m_szOut = "";
				m_scPSD.m_wndOut->m_wndOut.SetWindowText ("");
				m_sConsole.Execute (szExec, &m_scPSD, TRUE);

				if (!bSuperUltraMegaGigaFatalErr) // Well, let's not exaggerate now
					MessageBox ("External conversion failed!\nPlease check converter console output.", "Error", MB_OK|MB_ICONSTOP);

				return NULL;
			}
		}
		else
			if (!img.Load (szPath, nType))
				return NULL;

		m_Imported.Add (img);
	}
	catch (CMemoryException * er)
	{
		er->ReportError (MB_OK);
		return NULL;
	}

	m_Imported[m_Imported.GetCount ()-1].m_FileName = szPath;

	if (m_Imported[m_Imported.GetCount ()-1].AlphaIsValid () && m_Imported[m_Imported.GetCount ()-1].GetBpp()==24) 
		nBpp=32;
	else
		nBpp=m_Imported[m_Imported.GetCount ()-1].GetBpp();

	ChangeIdlePaneText();

	return &m_Imported[m_Imported.GetCount ()-1];

}


void CMWnd::SortImages ()
{
	int x,y;

	// First sort by colors
	for (x=0; x<m_Imported.GetCount (); ++x)
	{
		for (y=0; y<m_Imported.GetCount (); ++y)
		{
			if (m_Imported[x].GetBpp() ICON_ORDER_BITCOUNT m_Imported[y].GetBpp())
				SwapImages(x,y);
		}
	}

	// Now sort by size
	for (int g=0; g<5; ++g)
	{
		int cc;
		switch (g){
			case 0:cc=24;break;
			case 1:cc=-1;break;
			case 2:cc=8;break;
			case 3:cc=4;break;
			case 4:cc=1;break;
		}

		for (x=0; x<m_Imported.GetCount (); ++x)
		{
			for (y=0; y<m_Imported.GetCount (); ++y)
			{
				if (m_Imported[x].GetBpp ()==cc &&
					m_Imported[y].GetBpp ()==cc)
					if (m_Imported[x].GetWidth () ICON_ORDER_SIZE m_Imported[y].GetWidth ())
						SwapImages (x,y);

				if (cc==-1 &&(
					(m_Imported[x].AlphaIsValid () && m_Imported[y].AlphaIsValid()) &&
					m_Imported[x].GetBpp()==24 && m_Imported[y].GetBpp()==24))
					if (m_Imported[x].GetWidth () ICON_ORDER_SIZE m_Imported[y].GetWidth ())
						SwapImages (x,y);		
			}
		}
	}
}

void CMWnd::SwapImages (int x, int y)
{
	CIcoImage  iTemp = m_Imported[x];
	m_Imported[x]=m_Imported[y];
	m_Imported[y] = iTemp;
}

void CMWnd::InsertImageIntoView (CString szName, CIcoImage * img, DWORD nIndex)
{
	int nGroup, nIco=0, w, h;
	DWORD dwIcoFlags=0;
	CListCtrl * lv = &((CIconView*)m_wndSplitter.GetPane (1, 0))->GetListCtrl ();
	CString szCap;
	CString szSize;
	CString szColors;
	LVITEM lvi;

	if (img->AlphaIsValid () && img->GetBpp()==24) {
		nGroup = 0;
	}
	else
	{
		switch (img->GetBpp ())
		{
		case 24:
			nGroup = 1;
			break;
		case 8:
			nGroup = 2;
			break;
		case 4:
			nGroup = 3;
			break;
		case 1:
			nGroup = 4;
			break;
		}
	}

	w=img->GetWidth ();
	h=img->GetHeight ();

	CString szFile = szName.Right (szName.GetLength () - 
		(szName.ReverseFind ('\\')+1));

	if (m_nView == LV_VIEW_TILE)
		szCap.Format ("%s", szFile);
	else
		szCap.Format ("%s", szFile);

	if (w>48 || h>48)
		dwIcoFlags = IM_ICON_INVALIDSIZE;
	else if (w!=h)
		dwIcoFlags = IM_ICON_ERRORSIZE;

	img->m_dwFlags = dwIcoFlags;
	
	szCap.Append (CString(_T(' '), 96).GetString()); // 2004 me added spaces here manually, 2018 me fixed this unacceptable foolishness!

	int iItem = lv->InsertItem(lv->GetItemCount (), szCap, nIco);

	HANDLE hFile = CreateFile (szName, FILE_READ_DATA, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwSize = GetFileSize (hFile, NULL); 
	CloseHandle (hFile);

	if (dwSize == INVALID_FILE_SIZE) 
		szSize = "Invalid File Size";
	else
		szSize.Format ("%9.2f KB", (float)(dwSize)/1024);

	szCap.Format ("%d x %d, %s", w, h,szSize);
	lv->SetItemText (iItem, 1, szCap);

	if (img->GetNumColors() == 0)
		szColors = "No Palette";
	else
	{
		RGBQUAD * lprgbColors = img->GetPalette ();
		UINT nc=0;

		for (int c=0; c<(signed)img->GetNumColors(); ++c)
			if (lprgbColors[c].rgbBlue
				+lprgbColors[c].rgbRed
				+lprgbColors[c].rgbGreen > 0)
				nc++;

		szColors.Format ("%d", nc+1);
	}
	lv->SetItemText (iItem, 2, szColors);

	CString szFmtDesc;
	if (szName.Right (3).MakeLower().MakeLower() == "png")
		szFmtDesc = "Portable Network Graphic";
	if (szName.Right (3).MakeLower() == "bmp")
		szFmtDesc = "Windows Bitmap";
	if (szName.Right (3).MakeLower() == "wbmp")
		szFmtDesc = "Wireless Bitmap";
	if (szName.Right (3).MakeLower() == "ico")
		szFmtDesc = "Windows Icon";
	if ((szName.Right (3).MakeLower() == "tif")||(szName.Right (3).MakeLower() == "tiff"))
		szFmtDesc = "Tagged Image Format";
	if (szName.Right (3).MakeLower() == "tga")
		szFmtDesc = "Targa Bitmap";
	if (szName.Right (3).MakeLower() == "pcx")
		szFmtDesc = "ZSoft Paintbrush Graphic";
	if (szName.Right (3).MakeLower() == "wmf")
		szFmtDesc = "Windows Metafile";
	if (szName.Right (3).MakeLower() == "emf")
		szFmtDesc = "Enhanced Windows Metafile";
	if ((szName.Right (3).MakeLower() == "jpg")||(szName.Right (3).MakeLower() == "jpeg"))
		szFmtDesc = "Joint Photographic Experts Group Format";
	if ((szName.Right (3).MakeLower() == "jp2")||(szName.Right (3).MakeLower() == "j2k"))
		szFmtDesc = "JPEG 2000 Format";
	if (szName.Right (3).MakeLower() == "pnm")
		szFmtDesc = "Portable Pixmap Format";
	if (szName.Right (3).MakeLower() == "psd")
		szFmtDesc = "Adobe Photoshop Format";
	if (szName.Right (3).MakeLower() == "gif")
		szFmtDesc = "CompuServe Bitmap";

	lv->SetItemText (iItem, 3, szFmtDesc);

	lv->SetItemData (iItem, nIndex);

	// Set item group ID
	ZeroMemory(&lvi, sizeof(lvi));
	lvi.iItem = iItem;
	lvi.iImage = nIco;
	lvi.mask = LVIF_GROUPID;
	lvi.iGroupId = nGroup;

	lv->SetItem(&lvi);
}


void CMWnd::OnEditUndo()
{
	CIconEditor * ed = (CIconEditor*)m_wndSplitter.GetPane (0, 0);
	CIcoImage * undo = &m_Actions[m_Actions.GetCount ()-1];
	for (int i=0; i<m_Imported.GetCount (); i++)
	{
		if ((m_Imported[i].m_FileName == undo->m_FileName) &&
			(m_Imported[i].GetFrame() == undo->GetFrame() ))
		{
			m_Imported[i] = *undo;
			m_Actions.RemoveAt (m_Actions.GetCount ()-1);
			break;
		}
	}
	
	ed->RedrawWindow();
	RefreshView ();
}


void CMWnd::OnUpdateEditUndo(CCmdUI *pCmdUI)
{pCmdUI->Enable ((BOOL)(m_Actions.GetCount () > 0));}

void CMWnd::OnTransparentcolorPickfromimage()
{
	CIconEditor * ed = (CIconEditor*)m_wndSplitter.GetPane (0, 0);

	ed->m_hPicker = ::AfxGetApp ()->LoadCursor (IDC_COLORSELECTION);
	ed->m_bPicker = TRUE;
	ed->SetFocus();
}

void CMWnd::OnTransparentcolorRemove()
{
	CIconEditor * ed = (CIconEditor*)m_wndSplitter.GetPane (0, 0);
	ed->CustomAction (IE_ACTION_REMOVETRANS);
}

void CMWnd::OnTransparentcolorWritergbvalues()
{
	CIconEditor * ed = (CIconEditor*)m_wndSplitter.GetPane (0, 0);
	ed->CustomAction (IE_ACTION_SETTRANS);
}

void CMWnd::OnUpdateTransparentcolorWritergbvalues(CCmdUI *pCmdUI)
{OnUpdateEditTransparentColor(pCmdUI);}
void CMWnd::OnUpdateTransparentcolorPickfromimage(CCmdUI *pCmdUI)
{OnUpdateEditTransparentColor(pCmdUI);}
void CMWnd::OnUpdateTransparentcolorRemove(CCmdUI *pCmdUI)
{OnUpdateEditTransparentColor(pCmdUI);}

///////////////////
//////////////////
CIconView * CMWnd::GetIconView ()
{
	CIconView * vw = (CIconView*)m_wndSplitter.GetPane (1,0);
	return vw;
}

void CMWnd::OnUpdateEditResize(CCmdUI *pCmdUI)
{OnUpdateEditTransparentColor(pCmdUI);}
void CMWnd::OnUpdateEditMirror(CCmdUI *pCmdUI)
{OnUpdateEditTransparentColor(pCmdUI);}
void CMWnd::OnUpdateEditFlip(CCmdUI *pCmdUI)
{OnUpdateEditTransparentColor(pCmdUI);}

void CMWnd::OnUpdateEditTransparentColor(CCmdUI *pCmdUI)
{
	pCmdUI->Enable ((BOOL)(GetIconView())->GetListCtrl ().GetSelectedCount ()>0);
}


void CMWnd::OnGammaIncrease()
{
	(GetIconView()->GetIconEditor())->CustomAction (IE_FILTER_GAMMA, 1);
}

void CMWnd::OnGammaDecrease()
{
	(GetIconView()->GetIconEditor())->CustomAction (IE_FILTER_GAMMA, -1);
}

void CMWnd::OnLightIncrease()
{
	(GetIconView()->GetIconEditor())->CustomAction (IE_FILTER_LIGHT, 1);
}

void CMWnd::OnLightDecrease()
{
	(GetIconView()->GetIconEditor())->CustomAction (IE_FILTER_LIGHT, -1);
}

void CMWnd::OnContrastIncrease()
{
	(GetIconView()->GetIconEditor())->CustomAction (IE_FILTER_CONTRAST, 1);
}

void CMWnd::OnContrastDecrease()
{
	(GetIconView()->GetIconEditor())->CustomAction (IE_FILTER_CONTRAST, -1);
}

void CMWnd::OnFiltersThreshold()
{((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_FILTER_THRESHOLD);}

void CMWnd::OnThresholdInteractive()
{((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_FILTER_INTERACTIVETH);}





void CMWnd::OnBit24bit()
{((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_ACTION_24BPP);}

void CMWnd::OnBit8bit()
{((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_ACTION_8BPP);}

void CMWnd::OnBit4bit()
{((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_ACTION_4BPP);}

void CMWnd::OnBit2bit()
{((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_ACTION_1BPP);}


void CMWnd::OnEditResize()
{
	((CIconEditor*)m_wndSplitter.GetPane (0,0))->Resample ();
}

void CMWnd::OnZoomX4()
{((CIconEditor*)m_wndSplitter.GetPane (0,0))->Zoom (4);}
void CMWnd::OnZoomX3()
{((CIconEditor*)m_wndSplitter.GetPane (0,0))->Zoom (3);}
void CMWnd::OnZoomX2()
{((CIconEditor*)m_wndSplitter.GetPane (0,0))->Zoom (2);}
void CMWnd::OnZoom1()
{((CIconEditor*)m_wndSplitter.GetPane (0,0))->Zoom (1);}

void CMWnd::OnEditMirror()
{
	((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_ACTION_MIRROR);
}

void CMWnd::OnEditFlip()
{
	((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_ACTION_FLIP);
}
void CMWnd::OnEditRotate()
{
	((CIconEditor*)m_wndSplitter.GetPane (0,0))->Rotate ();
}

void CMWnd::OnUpdateZoom(CCmdUI *pCmdUI)
{pCmdUI->Enable ((BOOL)(GetIconView())->GetListCtrl ().GetSelectedCount ()>0);}
void CMWnd::OnUpdateEditRotate(CCmdUI *pCmdUI)
{pCmdUI->Enable ((BOOL)(GetIconView())->GetListCtrl ().GetSelectedCount ()>0);}

void CMWnd::OnUpdateFileExport(CCmdUI *pCmdUI)
{pCmdUI->Enable (GetIconView()->GetListCtrl ().GetItemCount ()>0);}

void CMWnd::OnUpdateFiltersThreshold(CCmdUI *pCmdUI)
{OnUpdateFiltersSharpen (pCmdUI);}
void CMWnd::OnUpdateGammaIncrease(CCmdUI *pCmdUI)
{OnUpdateFiltersSharpen (pCmdUI);}
void CMWnd::OnUpdateLightIncrease(CCmdUI *pCmdUI)
{OnUpdateFiltersSharpen (pCmdUI);}
void CMWnd::OnUpdateContrastIncrease(CCmdUI *pCmdUI)
{OnUpdateFiltersSharpen (pCmdUI);}
void CMWnd::OnUpdateFiltersSoften(CCmdUI *pCmdUI)
{OnUpdateFiltersSharpen (pCmdUI);}
void CMWnd::OnUpdateThresholdInteractive(CCmdUI *pCmdUI)
{OnUpdateFiltersSharpen (pCmdUI);}

void CMWnd::OnFiltersSharpen()
{
	((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_FILTER_SHARPEN);
}

void CMWnd::OnFiltersEdge()
{
	((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_FILTER_EDGE);
}

void CMWnd::OnFiltersNegative()
{
	((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_FILTER_NEGATIVE);
}

void CMWnd::OnFiltersColorize()
{
	((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_FILTER_COLORIZE);
}

void CMWnd::OnFiltersSoften()
{
	((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_FILTER_SOFTEN);
}

void CMWnd::OnUpdateFiltersSharpen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable (
		(GetIconView()->GetListCtrl ().GetSelectedCount ()>0) && 
		(GetIconView()->GetIconEditor ()->GetSelectedImage()!=NULL));
}

void CMWnd::OnUpdateFiltersEdge(CCmdUI *pCmdUI)
{OnUpdateFiltersSharpen (pCmdUI);}
void CMWnd::OnUpdateFiltersNegative(CCmdUI *pCmdUI)
{OnUpdateFiltersSharpen (pCmdUI);}
void CMWnd::OnUpdateFiltersColorize(CCmdUI *pCmdUI)
{OnUpdateFiltersSharpen (pCmdUI);}

void CMWnd::OnClose()
{
	if (m_bBusy)
	{
		m_scPSD.m_bBusy=FALSE;
		m_scPSD.b_Interrupt=TRUE;
		TRACE("INTERUPTED!");
		return;
	}

	if (GetIconView()->GetIconEditor ()->m_bInteractive)
	{
		GetIconView()->GetIconEditor ()->m_bInteractive=FALSE;
		GetIconView()->GetIconEditor ()->m_bClose = TRUE;
		TRACE0("OMG!\n");
		return;
	}

	SaveInt ("toolbar", (int)m_wndToolBar.IsWindowVisible ());
	SaveInt ("statusbar", (int)m_wndStatusBar.IsWindowVisible ());

	SaveInt ("backgroundmode", m_nBackground);
	SaveInt ("backcolor", m_dwBackColor);

	CFrameWnd::OnClose();
}

UINT nBPP=0;
void CMWnd::UpdateBitCount(CCmdUI *pCmdUI)
{
	bool bCheck = FALSE;

	if (GetIconView()->GetIconEditor()->GetSelectedImage() && 
		GetIconView()->GetListCtrl().GetSelectedCount() == 1)
	{
		if (nBPP == 32)
			bCheck = GetIconView()->GetIconEditor()->GetSelectedImage()->AlphaIsValid() && 
						GetIconView()->GetIconEditor()->GetSelectedImage()->GetBpp() == 24;
		else
			bCheck = GetIconView()->GetIconEditor()->GetSelectedImage()->GetBpp() == nBPP;
	}

	pCmdUI->SetCheck(bCheck);
	
	if (nBPP!=32)
		pCmdUI->Enable ((BOOL)(GetIconView())->GetListCtrl ().GetSelectedCount ()>0);
}
void CMWnd::OnUpdateBit32bit(CCmdUI *pCmdUI)
{nBPP=32;UpdateBitCount(pCmdUI);}
void CMWnd::OnUpdateBit24bit(CCmdUI *pCmdUI)
{nBPP=24;UpdateBitCount(pCmdUI);}
void CMWnd::OnUpdateBit8bit(CCmdUI *pCmdUI)
{nBPP=8;UpdateBitCount(pCmdUI);}
void CMWnd::OnUpdateBit4bit(CCmdUI *pCmdUI)
{nBPP=4;UpdateBitCount(pCmdUI);}
void CMWnd::OnUpdateBit2bit(CCmdUI *pCmdUI)
{nBPP=1;UpdateBitCount(pCmdUI);}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// Export
////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMWnd::OnFileExport()
{
	// :O At last, export!
	CxImage **exp;
	CxImage imgFile;
	TCHAR szBuf[10240]="";
	FILE* hFile;
	int c=0;

	if (m_bMultiPage)
	{
		for (int i=0; i<(int)m_Imported.GetCount(); ++i)
		{
			if (m_bDontExportInvalid)
				if (m_Imported[i].GetWidth() != m_Imported[i].GetHeight())
					continue;
			c++;
		}

		if (c<=0)
		{
			MessageBox ("All imported icons have invalid sizes.", "Error", MB_OK|MB_ICONINFORMATION);
			return;
		}

		exp = (CxImage**)calloc (c, sizeof(CxImage));
		c=0;

		for (int i=0; i<(int)m_Imported.GetCount(); ++i)
		{
			if (m_bDontExportInvalid)
			{
				if (m_Imported[i].GetWidth() != m_Imported[i].GetHeight())
					continue;
			}

			exp[c] = &m_Imported[i];
			c++;
		}



		CFileDialog * cf;

		cf = (CFileDialog*)new CFileDialog (
			FALSE, 
			NULL,
			NULL,
			OFN_FILEMUSTEXIST | OFN_EXPLORER,
			CxImage_GetFormatList (),
			NULL);

		cf->m_ofn.nFilterIndex = GetInt ("export_filter", 4);
		cf->m_ofn.lpstrFile = szBuf;
		cf->m_ofn.nMaxFile = sizeof(szBuf);
		cf->m_ofn.lpstrTitle = "Export Files";	

		if (cf->DoModal () != IDOK) {
			delete cf;
			return;
		}

		SaveInt ("export_filter", cf->m_ofn.nFilterIndex);
		
		CString szFile = cf->GetPathName();
		CString szExt = CxImage_GetExtension(cf->GetOFN().nFilterIndex , this->m_hWnd);
		
		if (szExt == "format_critical_error")
		{
			MessageBox ("Encoder is missing, please visit technical support at http://iconmasterxp.com.","Error",MB_OK|MB_ICONSTOP);
			return;
		}
		else if (szExt == "format_not_supported")
			return;

		if (szFile.Right (3) != szExt)
			szFile += ("."+szExt);

		if (c > 1)
		{
			int nType = ::CxImage_FindType (szExt);
			if (nType==CXIMAGE_FORMAT_UNKNOWN)
			{
				MessageBox ("This format is not supported for writing.",
					"Error", MB_OK|MB_ICONSTOP);
				return;
			}
			else if ((nType != CXIMAGE_FORMAT_ICO) &&
				(nType != CXIMAGE_FORMAT_GIF))
			{
				MessageBox ("Only GIF and ICO format encoders support multipage files.","Error", MB_OK|MB_ICONSTOP);
				return;
			}

			if (!(hFile = fopen(szFile,"w+b")))
			{
				MessageBox ("Failed to open file for writing!", "Error", MB_OK|MB_ICONSTOP);
				return;
			}

			imgFile.Encode (hFile, exp, (int)
				c, nType);

			fclose(hFile);
		}
		else
		{
			int nType=::CxImage_FindType (CxImage_GetExtension( cf->GetOFN().nFilterIndex , this->m_hWnd));
			if (nType==CXIMAGE_FORMAT_UNKNOWN)
			{
				MessageBox ("This format is not supported for writing.",
					"Error", MB_OK|MB_ICONSTOP);
				return;
			}

			if (nType==CXIMAGE_FORMAT_JPG || nType==CXIMAGE_FORMAT_JP2)
			{
				exp[0]->AlphaStrip ();
				if (exp[0]->GetBpp() > 24) {
					exp[0]->DecreaseBpp (24, TRUE);
				}
				else if (exp[0]->GetBpp() < 24)
					exp[0]->IncreaseBpp (24);

				exp[0]->SetCodecOption (m_dwOptions, nType);
				exp[0]->SetJpegQuality (100-m_nCompression);
				exp[0]->SetXDPI (72);
				exp[0]->SetYDPI (72);
			}

			exp[0]->Save (szFile, nType);
		}
		
		delete exp;
		delete cf;
	}
	else
	{
		CEncoderDialog dlgEncoders;
		
		if (dlgEncoders.DoModal ()!=IDOK) return;

		CString szExt = ::CxImage_GetExtension (dlgEncoders.m_nEncoder+1, this->m_hWnd);
		SaveInt ("export_individual_encoder", dlgEncoders.m_nEncoder);

		if (szExt == "format_critical_error")
		{
			MessageBox ("Encoder is missing, please visit technical support at http://www.iconmasterxp.com.","Error",MB_OK|MB_ICONSTOP);
			return;
		}
		else if (szExt == "format_not_supported")
			return;

		int nType = ::CxImage_FindType (szExt);
		if (nType == ::CXIMAGE_FORMAT_UNKNOWN)
		{
			MessageBox ("This format is not supported for writing.",
				"Error", MB_OK|MB_ICONSTOP);
			return;
		}

		CFolderDialog dlgFolders("Select destination folder", GetStr("export_folders","c:\\"), this,
			BIF_EDITBOX|BIF_DONTGOBELOWDOMAIN|BIF_NEWDIALOGSTYLE);

		if (dlgFolders.DoModal ()!=IDOK) return;
		SaveStr ("export_folders", dlgFolders.GetFolderPath());

		for (int i=0; i<(int)m_Imported.GetCount(); ++i)
		{
			if (this->m_bDontExportInvalid) 
				if (m_Imported[i].GetWidth() != m_Imported[i].GetHeight()) continue;

			CIcoImage * img = &m_Imported[i];
			CString szFile = img->m_FileName;
			CString szName = szFile.Right(szFile.GetLength() - szFile.ReverseFind('\\')-1);
			CString szPath = dlgFolders.GetFolderPath();
			CString szFinalFile;
			CString szNum;
			CFileFind ff;
			
			if (szPath.GetLength() >= 4) szPath+="\\";
			szName = szName.Left(szName.GetLength()-4);

			szFinalFile = szPath + szName + "." + szExt;

			for(int f=1; ff.FindFile(szFinalFile); ++f)
			{
				szNum.Format ("_%d", f);
				szFinalFile = szPath + szName + szNum + "." + szExt;
			}

			if (szExt=="jpg" || szExt=="jpeg" || szExt=="jp2" || szExt=="j2k")
			{
				img->AlphaStrip ();
				if (img->GetBpp() > 24) {
					img->DecreaseBpp (24, TRUE);
				}
				else if (img->GetBpp() < 24)
					img->IncreaseBpp (24);

				img->SetCodecOption (m_dwOptions, nType);
				img->SetJpegQuality (100-m_nCompression);
				img->SetXDPI (72);
				img->SetYDPI (72);
			}

			img->Save (szFinalFile, nType);
		}
	}
}

void CMWnd::OnFileMulti()
{
	m_bMultiPage=!m_bMultiPage;
}

void CMWnd::OnUpdateFileMulti(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck (m_bMultiPage);
}



void CMWnd::OnFileJpegsettings()
{
	CJpegDialog dlg;

	if (m_dwOptions & CxImageJPG::ENCODE_OPTIMIZE)
		dlg.m_bOptimize = TRUE;
	if (m_dwOptions & CxImageJPG::ENCODE_PROGRESSIVE)
		dlg.m_bProgressive = TRUE;
	dlg.m_nCompression = m_nCompression;

	if (dlg.DoModal()!=IDOK) return;

	m_nCompression = dlg.m_nCompression;
	
	m_dwOptions = 0;
	if (dlg.m_bOptimize)
		m_dwOptions |= CxImageJPG::ENCODE_OPTIMIZE;
	if (dlg.m_bProgressive)
		m_dwOptions |= CxImageJPG::ENCODE_PROGRESSIVE;

	SaveInt ("jpgc", m_nCompression);
	SaveInt ("jpgo", m_dwOptions);
}

void CMWnd::OnBitTips()
{
	CString szFile = CString(((CIconMasterXPApp*)::AfxGetApp())->GetHelpFile()) + ">wnd_context";
	::HtmlHelp (this->m_hWnd, szFile, 
		HH_HELP_CONTEXT, IDH_COLOR_MODES);	
}

void CMWnd::OnEditRevert()
{((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_ACTION_REVERT);}

void CMWnd::OnUpdateEditRevert(CCmdUI *pCmdUI)
{OnUpdateEditUndo(pCmdUI);}

void CMWnd::OnEditReplacecolors()
{((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_ACTION_CREPLACE);}

void CMWnd::OnUpdateEditReplacecolors(CCmdUI *pCmdUI)
{OnUpdateFiltersSharpen(pCmdUI);}

void CMWnd::OnEditDuplicate()
{
	((CIconEditor*)m_wndSplitter.GetPane (0,0))->CustomAction (IE_ACTION_DUPLICATE);
	ChangeIdlePaneText();
}

void CMWnd::OnUpdateEditDuplicate(CCmdUI *pCmdUI)
{OnUpdateFiltersSharpen(pCmdUI);}

void CMWnd::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 548;
	lpMMI->ptMinTrackSize.y = 473;

	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

void CMWnd::OnZoomEnableanti()
{
	GetIconView()->GetIconEditor()->m_ZoomAlias = !GetIconView()->GetIconEditor()->m_ZoomAlias;
	SaveInt ("ZoomAlias", GetIconView()->GetIconEditor()->m_ZoomAlias);
	GetIconView()->GetIconEditor()->RedrawWindow();
}

void CMWnd::OnUpdateZoomEnableanti(CCmdUI *pCmdUI)
{
	OnUpdateFiltersSharpen(pCmdUI);
	pCmdUI->SetCheck (GetIconView()->GetIconEditor()->m_ZoomAlias);
}

LRESULT CMWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message==WM_EXITMENULOOP)
	{
		ChangeIdlePaneText();
	}

	return CFrameWnd::WindowProc(message, wParam, lParam);
}

void CMWnd::ChangeIdlePaneText ()
{
	CString sz;
	if (m_Imported.GetCount()<=0)
		sz = "Click Import button to add files";
	else
		sz.Format ("Total %d items", m_Imported.GetCount());
	//this->m_wndStatusBar.SetPaneText (0, sz); <---- h4x
}
void CMWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFrameWnd::OnShowWindow(bShow, nStatus);

	ChangeIdlePaneText();
}

void CMWnd::OnViewConsole()
{
	m_wndConsole.ShowWindow (SW_SHOW);
}

void CMWnd::OnHelp()
{
	//::/Overview.htm
	CString szFile = CString(((CIconMasterXPApp*)::AfxGetApp())->GetHelpFile()) + "::/Overview.htm>wnd_main";
	::HtmlHelp (this->m_hWnd, szFile, 
		HH_DISPLAY_TOPIC, NULL); 
}

//void CMWnd::OnHelpHowtobuyfullversion()
//{
//	CString szFile = CString(((CIconMasterXPApp*)::AfxGetApp())->GetHelpFile()) + ">wnd_context";
//}

void CMWnd::OnTransparentcolorHelp()
{
	CString szFile = CString(((CIconMasterXPApp*)::AfxGetApp())->GetHelpFile()) + ">wnd_context";
	::HtmlHelp (this->m_hWnd, szFile, 
		HH_HELP_CONTEXT, IDH_MANIPULATING_COLORS);
}

void CMWnd::OnThresholdHelp()
{
	CString szFile = CString(((CIconMasterXPApp*)::AfxGetApp())->GetHelpFile()) + ">wnd_context";
	::HtmlHelp (this->m_hWnd, szFile, 
		HH_HELP_CONTEXT, IDH_THRESHOLD);
}

void CMWnd::OnEditPalette()
{
	CPaletteEd ed;
	CIcoImage * img = GetIconView()->GetIconEditor ()->GetSelectedImage();
	UINT nc=1;
	
	
	if (img->GetNumColors() == 0)
	{
		MessageBox ("Palette for selected image does not exist.", "Error", MB_OK|MB_ICONINFORMATION);
		return;
	}
	else
	{
		RGBQUAD * lprgbColors = img->GetPalette ();

		for (int c=1; c<(int)img->GetNumColors(); ++c)
			if (lprgbColors[c].rgbBlue
				+lprgbColors[c].rgbRed
				+lprgbColors[c].rgbGreen > 0)
				nc++;
	
		ed.m_rgbPal = img->GetPalette ();
		ed.m_nColors = nc;

		if (ed.DoModal () != IDOK) return;
	}
}

void CMWnd::OnUpdateEditPalette(CCmdUI *pCmdUI)
{
	pCmdUI->Enable (
		(GetIconView()->GetListCtrl ().GetSelectedCount ()==1) && 
		(GetIconView()->GetIconEditor ()->GetSelectedImage()!=NULL));
}

void CMWnd::OnBackgroundPattern()
{
	m_nBackground = BACK_PATTERN;
	this->GetIconView()->GetIconEditor()->RedrawWindow();
}

void CMWnd::OnBackgroundColor()
{
	m_nBackground = BACK_COLOR;
	this->GetIconView()->GetIconEditor()->RedrawWindow();
}

void CMWnd::OnUpdateBackgroundPattern(CCmdUI *pCmdUI)
{pCmdUI->SetCheck (m_nBackground == BACK_PATTERN ? TRUE:FALSE);}
void CMWnd::OnUpdateBackgroundColor(CCmdUI *pCmdUI)
{pCmdUI->SetCheck (m_nBackground == BACK_COLOR ? TRUE:FALSE);}

void CMWnd::OnBackgroundEditcolor()
{
	CColorDialog cdlg;

	cdlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
	cdlg.m_cc.rgbResult = m_dwBackColor;

	if (cdlg.DoModal ()!=IDOK) return;

	m_dwBackColor = cdlg.GetColor ();

	this->GetIconView()->GetIconEditor()->RedrawWindow();
}


void CMWnd::OnFileDon()
{
	m_bDontExportInvalid=!m_bDontExportInvalid;
}

void CMWnd::OnUpdateFileDon(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck (m_bDontExportInvalid);
}


void CMWnd::OnDropFiles(HDROP hDropInfo)
{
	UINT uNumFiles;
	TCHAR szNextFile [MAX_PATH];
	CArray<CString, CString> files;

	uNumFiles = DragQueryFile (hDropInfo, -1, NULL, 0);

	for (UINT uFile = 0; uFile < uNumFiles; uFile++)
	{
		if (DragQueryFile (hDropInfo, uFile, szNextFile, MAX_PATH) > 0)
		{
			TRACE1("Dropped: %s\n", szNextFile);
			files.Add(CString(szNextFile));
		}
	}

	DragFinish (hDropInfo);

	this->ImportImages(&files);

	CFrameWnd::OnDropFiles(hDropInfo);
}
