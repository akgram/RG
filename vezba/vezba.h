
// vezba.h : main header file for the vezba application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CvezbaApp:
// See vezba.cpp for the implementation of this class
//

class CvezbaApp : public CWinApp
{
public:
	CvezbaApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CvezbaApp theApp;
