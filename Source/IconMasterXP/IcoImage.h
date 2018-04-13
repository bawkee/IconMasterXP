#pragma once

class CIcoImage :
	public CxImage
{
public:
	CIcoImage(void);
	~CIcoImage(void);

	CIcoImage &CIcoImage::operator = (CIcoImage &x)
	{
		CxImage::operator =(x);
		m_FileName = x.m_FileName;
		dwID = x.dwID;
		//m_nBpp = x.m_nBpp;
		m_rtPosition = x.m_rtPosition;

		return *this;
	}

public:
	CString m_FileName;
	CRect m_rtPosition;
	DWORD dwID;
	DWORD m_dwFlags;
};
