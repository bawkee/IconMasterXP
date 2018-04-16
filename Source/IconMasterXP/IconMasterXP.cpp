// IconMasterXP.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "IconMasterXP.h"
#include "MWnd.h"
#include "AppAbout.h"

#include "Doc.h"
#include "IconEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIconMasterXPApp

BEGIN_MESSAGE_MAP(CIconMasterXPApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CIconMasterXPApp construction

CIconMasterXPApp::CIconMasterXPApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIconMasterXPApp object

CIconMasterXPApp theApp;

// CIconMasterXPApp initialization

BOOL CIconMasterXPApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX ic;
	
	m_szAppPath = GetAppPath();

	//First free the string allocated by MFC at CWinApp startup.
	//The string is allocated before InitInstance is called.
	free((void*)m_pszHelpFilePath);
	//Change the name of the help file.
	//The CWinApp destructor will free the memory.
	m_pszHelpFilePath=_tcsdup(GetHelpFile());
	
	ic.dwSize = sizeof(INITCOMMONCONTROLSEX);
	ic.dwICC = ICC_LISTVIEW_CLASSES;

	InitCommonControls();
	InitCommonControlsEx(&ic);

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("IconMasterXP"));
	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDoc),
		RUNTIME_CLASS(CMWnd),       // main SDI frame window
		RUNTIME_CLASS(CIconEditor));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The one and only window has been initialized, so show and update it
	m_pMainWnd->SetWindowPos (NULL,0,0,::GetInt ("r",600),::GetInt("b",400), SWP_NOMOVE);
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	CopyBinaries ();

	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}

// App command to run the dialog
void CIconMasterXPApp::OnAppAbout()
{
	CAppAbout aboutDlg;
	aboutDlg.DoModal();
}


// CIconMasterXPApp message handlers


int CIconMasterXPApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}

CString CIconMasterXPApp::GetHelpFile()
{
	// Note that help file is being copied by MSBuild automatically from the Documents folder, it's set in the project vcxproj file.
	CString szFile;
	szFile.Format("%s\\%s", m_szAppPath, "IconMasterXP.chm");
	return szFile;
}

// This will attempt to copy external command line tools to Windows directory (PATH). This was 2004, I knew it shouldn't be done
// but hey why not at least try it.
void CIconMasterXPApp::CopyBinaries()
{
	CString szWin;
	::GetWindowsDirectory (szWin.GetBuffer(512), 512); 
	szWin.ReleaseBuffer();
	szWin.Append ("\\psd2png.exe");
	if (!::CopyFile ("psd2png.exe", szWin, TRUE))
	{
		TRACE1 ("Copy to %s failed, file may already exist or access denied.", szWin);
	}
}

// Hmm, at least I decided not to do this after all. I think this was commented from the start, it was never used.
/*
void CIconMasterXPApp::ChangeEnvVariables()
{
	
	HKEY hKey; 
	char szBuf[5120]="";
	DWORD nBufSize=(DWORD)sizeof(szBuf);
	CString szValName = "PATH";
	DWORD dwReturnValue = 0;

	long res = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
		"System\\CurrentControlSet\\Control\\Session Manager\\Environment", 0, 
		KEY_ALL_ACCESS, &hKey);

	if (res == 0) {
		
		TRACE0("Registry key opened sucessfully!\n");

		::RegQueryValueEx (hKey, szValName, NULL, NULL, (LPBYTE)szBuf, &nBufSize);
		CString szVal(szBuf);

		if (szVal.GetLength()>5)
		{
			if (GetStr("env_path", "").GetLength () <= 1)
				SaveStr("env_path", szVal);

			CString szNewVal;

			szNewVal.Format ("%s;%s;", szVal, m_szAppPath);
			szVal.ReleaseBuffer();

			TRACE1("NEW_PATH:%s\n", szNewVal);

			if (szVal.Find(m_szAppPath)<=0)
				RegSetValueEx(hKey, szValName, 0, REG_SZ, (const unsigned char *)szNewVal.GetBuffer(5120), 5120);
			else
				TRACE0("There already is same path.");
			
			szNewVal.ReleaseBuffer();
		}

		
		//RegSetValueEx(hregkey, evName, 0, REG_SZ, (const unsigned char *)evValue, strlen(evValue));
		
	
		// propagate changes so that environment variables takes immediate effect!
		SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM) "Environment", SMTO_ABORTIFHUNG, 5000, NULL);
	}
  	else
		TRACE0("Error: Cannot Open registry key!\n");
	RegCloseKey(hKey);
	
}
*/