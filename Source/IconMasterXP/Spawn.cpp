//
// (c) 2002 Andreas Saurwein - saurwein@uniwares.com
//
// Use as you like, dont claim ownership of this code until
// you extended it sufficiently. Mention my name when you like to.
//
// Spawn.cpp: implementation of the CSpawn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Spawn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define BUFSIZE 80

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpawn::CSpawn()
{
	Init();
}

CSpawn::CSpawn(CString& exe, CSpawnConsumer* sc)
{
	Init();
	Execute(exe, sc, TRUE);
}


CSpawn::~CSpawn()
{
	TestAndCleanProcess();
	if (m_pReadThread)
	{
		TRACE0("Killing ReadPipe Thread\n");
		TerminateThread(m_pReadThread->m_hThread, 0);
		delete m_pReadThread;
		m_pReadThread = NULL;
	}
}

void CSpawn::Init() 
{ 
	m_dwProcessId = DWORD(-1);
	m_pReadThread = NULL;

	m_bRedirected = false;
	// Set up members of the PROCESS_INFORMATION structure. 
	
	ZeroMemory( &m_piProcInfo, sizeof(PROCESS_INFORMATION) );
	
	// Set up members of the STARTUPINFO structure. 
	
	ZeroMemory( &m_siStartInfo, sizeof(STARTUPINFO) );
	m_siStartInfo.cb = sizeof(STARTUPINFO); 
}	
	
bool CSpawn::Execute(CSpawnConsumer* sc)
{
	ASSERT(!m_szExecutable.IsEmpty());

	m_Consumer = sc;

	if (m_pReadThread)
	{
		VERIFY(CloseHandle(m_hChildStdinRd));
		VERIFY(CloseHandle(m_hChildStdoutWr));
		VERIFY(CloseHandle(m_hChildStdinWr));
		VERIFY(CloseHandle(m_hChildStdoutRd));
		TRACE0("Killing ReadPipe Thread\n");
		TerminateThread(m_pReadThread->m_hThread, 0);
		delete m_pReadThread;
		m_pReadThread = NULL;
	}
	
	// Now create the child process. 
	
	Redirect();
	ASSERT(m_pReadThread == NULL);
	m_pReadThread = AfxBeginThread((AFX_THREADPROC)ReadPipeThreadProc, (LPVOID)this, THREAD_PRIORITY_BELOW_NORMAL);
	if (!m_pReadThread)
	{
		throw(_T("Cannot start read-redirect thread!\n"));
	}

	// Now create the child process. 
	if (! CreateChildProcess()) 
		throw(_T("Create process failed")); 

	// After process creation, restore the saved STDIN and STDOUT.  
	if (!SetStdHandle(STD_INPUT_HANDLE, m_hSaveStdin))
		throw(_T("Re-redirecting Stdin failed\n"));

	if (!SetStdHandle(STD_OUTPUT_HANDLE, m_hSaveStdout))
		throw(_T("Re-redirecting Stdout failed\n"));

	WaitForSingleObject(m_pReadThread->m_hThread, 1000);
	return true;
} 

bool CSpawn::CreateChildProcess() 
{
	// Set up members of STARTUPINFO structure.  
	m_siStartInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	m_siStartInfo.wShowWindow = SW_HIDE;
	m_siStartInfo.hStdInput = m_hChildStdinRd;
	m_siStartInfo.hStdOutput = m_hChildStdoutWr;
	m_siStartInfo.hStdError = m_hChildStdoutWr;
	
	TCHAR shellCmd[4096];
	if (!GetEnvironmentVariable(_T("ComSpec"), shellCmd, 4096))
		return FALSE;

#ifdef _UNICODE
	_tcscat(shellCmd, _T(" /U"));
#else	
	_tcscat(shellCmd, _T(" /A"));
#endif 
	_tcscat(shellCmd, _T(" /C "));
	_tcscat(shellCmd, m_szExecutable);

	TRACE(_T("Trying: %s\r\n"), shellCmd);
	// Create the child process.  
	BOOL bRet = CreateProcess(NULL, 
		shellCmd, 	   // applicatin name
		NULL, 		  // process security attributes 
		NULL, 		  // primary thread security attributes 
		TRUE, 		  // handles are inherited 
		CREATE_NEW_CONSOLE, // creation flags 
		NULL, 		  // use parent's environment 
		NULL, 		  // use parent's current directory 
		&m_siStartInfo,  // STARTUPINFO pointer 
		&m_piProcInfo);  // receives PROCESS_INFORMATION 
	if (bRet)
	{
		m_dwProcessId = m_piProcInfo.dwProcessId;
	}
	else
	{
		m_dwProcessId = GetLastError();
		DebugBreak();
	}
	return bRet ? true : false;
}

void CSpawn::WriteToPipe(LPCTSTR line) 
{
	DWORD dwWritten;
	
	WriteFile(m_hChildStdinWr, line, (DWORD)_tcslen(line)*sizeof(TCHAR), &dwWritten, NULL);
}

UINT CSpawn::ReadPipeThreadProc(LPVOID pParam)
{
	DWORD dwRead;
	TCHAR chBuf[BUFSIZE+1]; 
	CSpawn* pThis = (CSpawn*)pParam;
	
	TRACE0("ReadPipe Thread begin run\n");
	for (;;)	
	{ 
		if (!ReadFile(pThis->m_hChildStdoutRd, chBuf, BUFSIZE, &dwRead, NULL) || dwRead == 0) 
		{
			TRACE0("ReadFile returned\n");
			if (::GetLastError() == ERROR_BROKEN_PIPE)
				break;
			else
				ASSERT(FALSE);
		}
		chBuf[dwRead/sizeof(TCHAR)] = _T('\0');
		
		if (pThis->m_bConsume)
			pThis->m_Consumer->Consume(chBuf, dwRead);
		else
			pThis->m_Consumer->Consume("", dwRead);

		// bail out if the process terminated already but only if the pipe is empty
		DWORD dwByteLeft = NULL;
		if(!PeekNamedPipe(pThis->m_hChildStdoutRd, chBuf, BUFSIZE, NULL, &dwByteLeft, NULL) || dwByteLeft == NULL)
			if(!pThis->TestProcess())
				break;
	} 
	VERIFY(CloseHandle(pThis->m_hChildStdinRd));
	VERIFY(CloseHandle(pThis->m_hChildStdoutWr));
	VERIFY(CloseHandle(pThis->m_hChildStdinWr));
	VERIFY(CloseHandle(pThis->m_hChildStdoutRd));
	pThis->m_pReadThread = NULL;
	pThis->m_dwProcessId = DWORD(-1);
	TRACE0("ReadPipe Thread exiting\n");
	return 1;
}

void CSpawn::TestAndCleanProcess()
{
	if (m_dwProcessId != DWORD(-1))
	{
		DWORD dwExitCode;
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_dwProcessId);

		// if the process handle is INVALID_HANDLEVALUE or
		// the process handle is valid but ExitCode is set
		if (!hProcess || (hProcess && GetExitCodeProcess(hProcess, &dwExitCode)))
		{
			if (m_pReadThread)
			{
				VERIFY(CloseHandle(m_hChildStdinRd));
				VERIFY(CloseHandle(m_hChildStdoutWr));
				VERIFY(CloseHandle(m_hChildStdinWr));
				VERIFY(CloseHandle(m_hChildStdoutRd));

				TRACE0("Killing ReadPipe Thread\n");
				TerminateThread(m_pReadThread->m_hThread, 0);
				delete m_pReadThread;
				m_pReadThread = NULL;
				m_dwProcessId = DWORD(-1);
			}
		}
		else
			VERIFY(CloseHandle(hProcess));
	}
}

bool CSpawn::TestProcess()
{
	if (m_dwProcessId != DWORD(-1))
	{
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_dwProcessId);
		if (hProcess)
		{
			DWORD dwExitCode;
			BOOL bRet = GetExitCodeProcess(hProcess, &dwExitCode);	// fails when the process is active
			VERIFY(CloseHandle(hProcess));
			return bRet == FALSE;
		}
	}
	return FALSE;
}


void CSpawn::ReadFromPipe() 
{
}

void CSpawn::Redirect()
{
	if(m_bRedirected)
	{
		if (! SetStdHandle(STD_INPUT_HANDLE, m_hSaveStdin)) 
			throw("Re-redirecting Stdin failed\n"); 
		
		if (! SetStdHandle(STD_OUTPUT_HANDLE, m_hSaveStdout)) 
			throw("Re-redirecting Stdout failed\n"); 
	}
	else
	{
		HANDLE hChildStdoutRdTmp, hChildStdinWrTmp;
		SECURITY_ATTRIBUTES saAttr;
		BOOL bSuccess;
		
		// Set the bInheritHandle flag so pipe handles are inherited.
		saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
		saAttr.bInheritHandle = TRUE;
		saAttr.lpSecurityDescriptor = NULL;
		
		// The steps for redirecting child process's STDOUT: 
		//	 1. Save current STDOUT, to be restored later. 
		//	 2. Create anonymous pipe to be STDOUT for child process. 
		//	 3. Set STDOUT of the parent process to be write handle to 
		//		the pipe, so it is inherited by the child process. 
		//	 4. Create a noninheritable duplicate of the read handle and
		//		close the inheritable read handle.  
		
		// Save the handle to the current STDOUT.  
		HANDLE hSaveStdout = GetStdHandle(STD_OUTPUT_HANDLE);  
		
		// Create a pipe for the child process's STDOUT.  
		if (!CreatePipe(&hChildStdoutRdTmp, &m_hChildStdoutWr, &saAttr, 0))
		{
			throw(_T("Stdout pipe creation failed\n"));
		}
		
		// Set a write handle to the pipe to be STDOUT.  
		if (!SetStdHandle(STD_OUTPUT_HANDLE, m_hChildStdoutWr))
		{
			throw(_T("Redirecting STDOUT failed\n"));
		}
		
		// Create noninheritable read handle and close the inheritable read handle. 
		bSuccess = DuplicateHandle(GetCurrentProcess(), hChildStdoutRdTmp, 
			GetCurrentProcess(), &m_hChildStdoutRd, 
			0, FALSE, 
			DUPLICATE_SAME_ACCESS);
		if (!bSuccess)
		{
			throw(_T("DuplicateHandle failed\n"));
		}
		VERIFY(CloseHandle(hChildStdoutRdTmp));
		
		// The steps for redirecting child process's STDIN: 
		//	 1.  Save current STDIN, to be restored later. 
		//	 2.  Create anonymous pipe to be STDIN for child process. 
		//	 3.  Set STDIN of the parent to be the read handle to the 
		//		 pipe, so it is inherited by the child process. 
		//	 4.  Create a noninheritable duplicate of the write handle, 
		//		 and close the inheritable write handle.  
		
		// Save the handle to the current STDIN. 
		m_hSaveStdin = GetStdHandle(STD_INPUT_HANDLE);  
		
		// Create a pipe for the child process's STDIN.  
		if (!CreatePipe(&m_hChildStdinRd, &hChildStdinWrTmp, &saAttr, 0))
		{
			throw(_T("Stdin pipe creation failed\n"));
		}
		// Set a read handle to the pipe to be STDIN.  
		if (!SetStdHandle(STD_INPUT_HANDLE, m_hChildStdinRd)) 
		{
			throw(_T("Redirecting Stdin failed\n"));
		}
		// Duplicate the write handle to the pipe so it is not inherited.  
		bSuccess = DuplicateHandle(GetCurrentProcess(), hChildStdinWrTmp, 
			GetCurrentProcess(), &m_hChildStdinWr, 
			0, FALSE, 				  // not inherited	   
			DUPLICATE_SAME_ACCESS); 
		if (!bSuccess) 
		{
			throw(_T("DuplicateHandle failed\n"));
		}
		VERIFY(CloseHandle(hChildStdinWrTmp));  
	}
}
