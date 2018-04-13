// stdafx.cpp : source file that includes just the standard includes
// IconMasterXP.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


void InsertAlphaIcon (CString szName, CImageList * iml, int sx, int sy)
{
	CString szBuf, szImg;

	szBuf=GetAppPath();

	szImg.Format ("%s\\res\\ico\\%s.ico", szBuf, szName);
	iml->Add ((HICON)LoadImage (::AfxGetApp()->m_hInstance, 
		szImg, IMAGE_ICON, sx, sy, LR_CREATEDIBSECTION|LR_LOADFROMFILE));
}

void InsertAlphaIcon (CString szName, CImageList * iml)
{
	InsertAlphaIcon(szName, iml, 32, 32);
}

void InsertAlphaIconFromRes (CString szName, CImageList * iml, int sx, int sy)
{
	iml->Add ((HICON)LoadImage (::AfxGetApp()->m_hInstance, 
		szName, IMAGE_ICON, sx, sy, LR_CREATEDIBSECTION));
}

void InsertAlphaIconFromRes (CString szName, CImageList * iml)
{
	InsertAlphaIconFromRes (szName, iml, 32, 32);
}


///////////////////////////////
// Global settings methods
///////////////////////////////

TCHAR _settingsAppName[256] = _T("main");

CString GetSettingsFile()
{
	TCHAR szPath[MAX_PATH];
	
	if(SUCCEEDED(SHGetFolderPath(NULL, 
								 CSIDL_APPDATA|CSIDL_FLAG_CREATE, 
								 NULL, 
								 0, 
								 szPath))) 
	{
		PathAppend(szPath, _T("\\IconMasterXP"));
		CreateDirectory(szPath, NULL);
		PathAppend(szPath, _T("\\settings.ini"));
		return CString(szPath);
	}

	return _T("settings.ini");
}

void SaveInt (CString szName, int nVal)
{
	CString szNum;	
	szNum.Format ("%d", nVal);
	::WritePrivateProfileString (_settingsAppName, szName, szNum, GetSettingsFile());
}

int GetInt (CString szName, int nDefault)
{
	return (signed)::GetPrivateProfileInt (_settingsAppName, szName, nDefault, GetSettingsFile());
}

void GetInt (CString szName, int * nVal, int nDefault)
{
	*nVal = GetInt(szName, nDefault);
}

void SaveStr (CString szName, CString szVal)
{
	::WritePrivateProfileString (_settingsAppName, szName, szVal, GetSettingsFile());
}

CString GetStr (CString szName, CString szDefault)
{
	CString szVal;	
	::GetPrivateProfileString (_settingsAppName, szName, szDefault, szVal.GetBuffer(256), 256, GetSettingsFile());
	szVal.ReleaseBuffer();
	return szVal;
}

void GetStr (CString szName, CString * szVal, CString szDefault)
{
	*szVal = GetStr(szName, szDefault);
}

void GetStr (CString szName, char * szVal, CString szDefault)
{
	TCHAR szBuf[1024];	
	::GetPrivateProfileString (_settingsAppName, szName, szDefault, szBuf, sizeof(szBuf), GetSettingsFile());
	szVal = szBuf;
}


/////////////////////////


int CxImage_FindType(CString& ext)
{
	int type = 0;
	CString szBuf = ext.MakeLower ();

	if (szBuf == "bmp")					type = CXIMAGE_FORMAT_BMP;
#if CXIMAGE_SUPPORT_JPG
	else if (szBuf=="jpg"||szBuf=="jpeg")	type = CXIMAGE_FORMAT_JPG;
#endif
#if CXIMAGE_SUPPORT_GIF
	else if (szBuf == "gif")				type = CXIMAGE_FORMAT_GIF;
#endif
#if CXIMAGE_SUPPORT_PNG
	else if (szBuf == "png")				type = CXIMAGE_FORMAT_PNG;
#endif
#if CXIMAGE_SUPPORT_MNG
	else if (szBuf=="mng"||szBuf=="jng")	type = CXIMAGE_FORMAT_MNG;
#endif
#if CXIMAGE_SUPPORT_ICO
	else if (szBuf == "ico")				type = CXIMAGE_FORMAT_ICO;
#endif
#if CXIMAGE_SUPPORT_TIF
	else if (szBuf=="tiff"||szBuf=="tif")	type = CXIMAGE_FORMAT_TIF;
#endif
#if CXIMAGE_SUPPORT_TGA
	else if (szBuf=="tga")				type = CXIMAGE_FORMAT_TGA;
#endif
#if CXIMAGE_SUPPORT_PCX
	else if (szBuf=="pcx")				type = CXIMAGE_FORMAT_PCX;
#endif
#if CXIMAGE_SUPPORT_WBMP
	else if (szBuf=="wbmp")				type = CXIMAGE_FORMAT_WBMP;
#endif
#if CXIMAGE_SUPPORT_WMF
	else if (szBuf=="wmf"||szBuf=="emf")	type = CXIMAGE_FORMAT_WMF;
#endif
#if CXIMAGE_SUPPORT_J2K
	else if (szBuf=="j2k"||szBuf=="jp2")	type = CXIMAGE_FORMAT_J2K;
#endif
#if CXIMAGE_SUPPORT_JBG
	else if (szBuf=="jbg")				type = CXIMAGE_FORMAT_JBG;
#endif
#if CXIMAGE_SUPPORT_JP2
	else if (szBuf=="jp2"||szBuf=="j2k")	type = CXIMAGE_FORMAT_JP2;
#endif
#if CXIMAGE_SUPPORT_JPC
	else if (szBuf=="jpc"||szBuf=="j2c")	type = CXIMAGE_FORMAT_JPC;
#endif
#if CXIMAGE_SUPPORT_PGX
	else if (szBuf=="pgx")				type = CXIMAGE_FORMAT_PGX;
#endif
#if CXIMAGE_SUPPORT_RAS
	else if (szBuf=="ras")				type = CXIMAGE_FORMAT_RAS;
#endif
#if CXIMAGE_SUPPORT_PNM
	else if (szBuf=="pnm"||szBuf=="pgm"||szBuf=="ppm") type = CXIMAGE_FORMAT_PNM;
#endif

	else type = CXIMAGE_FORMAT_UNKNOWN;

	return type;
}

CString CxImage_GetFormatList ()
{
	CString szF="";

	szF += "Portable Network Graphics (*.png)|*.png|";
	szF += "Windows Bitmaps (*.bmp)|*.bmp|";
	szF += "Wireless Bitmaps (*.wbmp)|*.wbmp|";
	szF += "Windows Icons (*.ico)|*.ico|";
	szF += "Tagged Image Format (*.tif; *.tiff)|*.tif;*.tiff|";
	szF += "Targa Bitmaps (*.tga)|*.tga|";
	szF += "ZSoft Paintbrush Graphics (*.pcx)|*.pcx|";
	szF += "Windows Metafile (*.wmf)|*.wmf|";
	szF += "Enhanced Windows Metafile (*.emf)|*.emf|";
	szF += "Joint Photographic Experts Group Format (*.jpg; *.jpeg)|*.jpg;*.jpeg|";
	szF += "JPEG 2000 Format (*.jp2; *.j2k)|*.jp2;*.j2k|";
	szF += "Portable Pixmap Format (*.pnm)|*.pnm|";
	szF += "Adobe Photoshop Format (*.psd)|*.psd|";
	szF += "All Supported Files|*.png;*.bmp;*.wbmp;*.ico;*.tif;*.tiff;*.tga;*.pcx;*.wmf;*.emf;*.jpg;*.jpeg;*.jp2;*.j2k;*.pnm;*.psd|";
	szF += "All Files (*.*)|*.*|";
	szF += "|";

	return szF;
}

CString CxImage_GetExtension (int n, HWND hwnd)
{
	CString sze="";
	
	switch (n)
	{
		case 1:sze =	"png";break;
		case 2:sze =	"bmp";break;
		case 3:sze =	"wbmp";break;
		case 4:sze =	"ico";break;
		case 5:sze =	"tif";break;
		case 6:sze =	"tga";break;
		case 7:sze =	"pcx";break;
		case 8:sze =	"wmf";break;
		case 9:sze =	"emf";break;
		case 10:sze =  "jpg";break;
		case 11:sze =  "j2k";break;
		case 12:sze =  "pnm";break;
		case 13:sze =	"psd";break;
		default:sze =	"*.*";break;
	}

#if !CXIMAGE_SUPPORT_PNG
	if (sze=="png") {MessageBox (hwnd,"This format is not supported in this version of IconMasterXP","Error",MB_OK|MB_ICONSTOP);sze="format_not_supported";}
#endif
#if !CXIMAGE_SUPPORT_WBMP
	if (sze=="wbmp") {MessageBox (hwnd,"This format is not supported in this version of IconMasterXP","Error",MB_OK|MB_ICONSTOP);sze="format_not_supported";}
#endif
#if !CXIMAGE_SUPPORT_ICO //teh omg! :O
	if (sze=="ico") sze="format_critical_error";
#endif
#if !CXIMAGE_SUPPORT_TIF
	if (sze=="tif") {MessageBox (hwnd,"This format is not supported in this version of IconMasterXP","Error",MB_OK|MB_ICONSTOP);sze="format_not_supported";}
#endif
#if !CXIMAGE_SUPPORT_TGA
	if (sze=="tga") {MessageBox (hwnd,"This format is not supported in this version of IconMasterXP","Error",MB_OK|MB_ICONSTOP);sze="format_not_supported";}
#endif
#if !CXIMAGE_SUPPORT_PCX
	if (sze=="pcx") {MessageBox (hwnd,"This format is not supported in this version of IconMasterXP","Error",MB_OK|MB_ICONSTOP);sze="format_not_supported";}
#endif
#if !CXIMAGE_SUPPORT_WMF
	if (sze=="wmf") {MessageBox (hwnd,"This format is not supported in this version of IconMasterXP","Error",MB_OK|MB_ICONSTOP);sze="format_not_supported";}
#endif
#if !CXIMAGE_SUPPORT_JPG
	if (sze=="jpg") {MessageBox (hwnd,"This format is not supported in this version of IconMasterXP","Error",MB_OK|MB_ICONSTOP);sze="format_not_supported";}
#endif
#if !CXIMAGE_SUPPORT_J2K
	if (sze=="j2k") {MessageBox (hwnd,"This format is not supported in this version of IconMasterXP","Error",MB_OK|MB_ICONSTOP);sze="format_not_supported";}
#endif
#if !CXIMAGE_SUPPORT_PNM
	if (sze=="pnm") {MessageBox (hwnd,"This format is not supported in this version of IconMasterXP","Error",MB_OK|MB_ICONSTOP);sze="format_not_supported";}
#endif

	return sze;
}

CString GetAppPath()
{
	CString buf;
	
	DWORD nLen = GetModuleFileName(NULL, buf.GetBufferSetLength(256+1), 256);

	buf.ReleaseBuffer(nLen);

	if (buf.GetLength() > 0)
		buf = buf.Mid(0, buf.ReverseFind('\\'));

	return buf;
}