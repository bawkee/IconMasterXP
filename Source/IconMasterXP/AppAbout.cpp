// AppAbout.cpp : implementation file
//

#include "stdafx.h"
#include "IconMasterXP.h"
#include "HyperLink.h"
#include "AppAbout.h"


// CAppAbout dialog

IMPLEMENT_DYNAMIC(CAppAbout, CDialog)
CAppAbout::CAppAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CAppAbout::IDD, pParent)
{
}

CAppAbout::~CAppAbout()
{
	m_hdcBuf.DeleteDC ();
}

void CAppAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CREDITS, m_Credits);
}


BEGIN_MESSAGE_MAP(CAppAbout, CDialog)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CAppAbout message handlers

int CAppAbout::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	HRSRC res = FindResource(NULL,MAKEINTRESOURCE(IDR_BANNER),"PNG");

	m_Img.LoadResource(FindResource(NULL,MAKEINTRESOURCE(IDR_BANNER),"PNG"),CXIMAGE_FORMAT_PNG);

	HDC hscr;
	hscr = ::GetDC (0);
	RECT rt;

	::GetClientRect  (::GetDesktopWindow (), &rt);
	m_hdcBuf.CreateCompatibleDC (0);
	m_hbmpBuf = CreateCompatibleBitmap (hscr, rt.right,rt.bottom);
	m_hdcBuf.SelectObject (m_hbmpBuf);
	::ReleaseDC(0,hscr);

	return 0;
}

void CAppAbout::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rt;

	rt.left=0;rt.top=0;
	rt.bottom=m_Img.GetHeight();rt.right=m_Img.GetWidth();

	if (!m_Img.IsValid ()) return;

	m_hdcBuf.FillSolidRect (&rt, (COLORREF)::GetSysColor(COLOR_3DFACE));
	m_Img.Draw (m_hdcBuf);

	dc.BitBlt (0, 16, rt.right, rt.bottom, &m_hdcBuf, 0, 0, SRCCOPY);
}

void CAppAbout::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	CString c;

	c="IconMasterXP Version 4.8\r\n";

	// I removed all the shareware-related code and resources from the solution (validation, trial counters, nag screens etc).
	// But I'm gonna leave this piece of 2004 me. I knew that someone is going to attempt to crack it with SoftICE or something
	// similar, in which case he'd first look through all the strings. I remove some the stupid lines but gonna leave this one for 
	// good memory.

	CString szRoflCopter[10];

	// Roflcopter fix
	szRoflCopter[0]=							"ROFL:ROFL:ROFL:LOL:ROFL:ROFL:ROFL       ";
	szRoflCopter[1]=							"			______V______                   ";
	szRoflCopter[2]=							" L     /  ___     _  |                  ";
	szRoflCopter[3]=							"LOL======  /___\\   [_]\\               ";
	szRoflCopter[4]=							" L     \\               \\              ";
	szRoflCopter[5]=							"			\\_______________]              ";
	szRoflCopter[6]=							"				I      I                     ";
	szRoflCopter[7]=							"			------------------/             ";
	szRoflCopter[8]=							"                                        ";
	szRoflCopter[9]=							"   TEH OMG! OMG OMG111 T3H R0FLCOPTER111";


	c+="Copyright ©2003-2011 2-Dots.com. All Rights Reserved.\r\n";
	c+="Please visit http://iconmasterxp.com for updates and news.\r\n\r\n";
	c+="Special thanks goes to:\r\n";
	c+="Davide Pizzolato, Author of CxImage Library\r\n";
	c+="Jeff Prosise, Quantizer ©1996-1997\r\n";
	c+="Armen Hakobyan, Export Dialog Modifications\r\n";
	c+="Alvaro Mendez, AMSEdit Class\r\n";
	c+="Andreas Saurwein, Console Redirect\r\n";
	c+="Michael Dunn, Wonderful MFC Articles\r\n";

	c+="IconMasterXP is using following software:\r\n";
	c+="IJG JPEG library ©1994-1998 Thomas G. Lane.\r\n";
	c+="LibPNG v1.2.7 ©1998-2007 Glenn Randers-Pehrson.\r\n";
	c+="LibTIFF v3.5.7 ©1988-1997 Sam Leffler, ©1991-1997 Silicon Graphics Inc.\r\n";
	c+="LibMNG v1.0.10 ©2000-2002 Gerard Juyn.\r\n";
	c+="LibJ2K ©2001-2002 David Janssens.\r\n";
	c+="LibJBG v1.6 ©2004 Markus Kuhn.\r\n";
	c+="JasPer v1.900.1 ©2001-2007 Image Power, UBC, Michael David Adams.\r\n";
	c+="zlib v1.2.3 ©1995-2005 Jean-loup Gailly and Mark Adler.";

	m_Credits.SetWindowText (c);
}
