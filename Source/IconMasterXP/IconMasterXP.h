// IconMasterXP.h : main header file for the IconMasterXP application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CIconMasterXPApp:
// See IconMasterXP.cpp for the implementation of this class
//

class CIconMasterXPApp : public CWinApp
{
public:
	CIconMasterXPApp();

	CString GetHelpFile();
	void CopyBinaries();

public:
	//CExpire * exp;
	CString m_szAppPath;

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CIconMasterXPApp theApp;