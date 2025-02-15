
// KOL.h : main header file for the KOL application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKOLApp:
// See KOL.cpp for the implementation of this class
//

class CKOLApp : public CWinApp
{
public:
	CKOLApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKOLApp theApp;
