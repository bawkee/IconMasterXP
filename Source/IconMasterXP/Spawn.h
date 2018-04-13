//
// (c) 2002 Andreas Saurwein - saurwein@uniwares.com
//
// Use as you like, dont claim ownership of this code until
// you extended it sufficiently. Mention my name when you like to.
// Spawn.h: interface for the CSpawn class.
//
//////////////////////////////////////////////////////////////////////

// Bojan: this is being used for the console redirect, for external tools.

#if !defined(_SPAWN_H_INCLUDED_)
#define _SPAWN_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef NO_STL
#include <string>

#if defined(_UNICODE) || defined(UNICODE)
using std::wstring;
typedef wstring	tstring;
#else
using std::string;
typedef string	tstring;
#endif
#endif // NO_STL

class CSpawnConsumer
{
public:
	CSpawnConsumer() {};
	virtual ~CSpawnConsumer() {};
private:
	//virtual Consume(tstring& output) = 0;
	virtual void Consume(TCHAR*	output, DWORD dwChars) = 0;
	friend class CSpawn;
};

class CSpawn  
{
public:
	CSpawn();
	CSpawn(CString& exe, CSpawnConsumer* sc);

	virtual ~CSpawn();
 
	bool Execute(CSpawnConsumer* sc);
	bool Execute(CString& exe, CSpawnConsumer* sc, BOOL bConsume)	{ 
		m_szExecutable = exe;
		m_bConsume = bConsume;
		return Execute(sc);
	}
	bool IsExecuting() { return TestProcess(); }
	void SendInput(LPCTSTR pIn)	{ WriteToPipe(pIn); }
	void SendInput(CString& In) { WriteToPipe(LPCTSTR(In));	}
#ifndef NO_STL
	void SendInput(tstring& In) { WriteToPipe(In.c_str());	}
#endif
	
protected:
	bool CreateChildProcess(); 
	void WriteToPipe(LPCTSTR line); 
	void ReadFromPipe(); 
	void ErrMsg(LPTSTR, bool); 
	void TestAndCleanProcess();
	bool TestProcess();
	
	void Redirect();
 
private:
	void	Init();
	static UINT ReadPipeThreadProc(LPVOID pParam);
	
	PROCESS_INFORMATION m_piProcInfo; 
	STARTUPINFO			m_siStartInfo; 
	
	HANDLE	m_hChildStdinRd, 
			m_hChildStdinWr, 
			m_hChildStdinWrDup, 
			m_hChildStdoutRd, 
			m_hChildStdoutWr, 
			m_hChildStdoutRdDup, 
			m_hInputFile, 
			m_hSaveStdin, 
			m_hSaveStdout; 

	bool	m_bRedirected;
	bool	m_bConsume;

	CString	m_szExecutable;
	CWinThread*	m_pReadThread;
	DWORD	m_dwProcessId;
	
	CSpawnConsumer* m_Consumer;

};

#endif // !defined(_SPAWN_H_INCLUDED_)
