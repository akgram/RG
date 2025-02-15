
// Kol2018.h : main header file for the Kol2018 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKol2018App:
// See Kol2018.cpp for the implementation of this class
//

class CKol2018App : public CWinApp
{
public:
	CKol2018App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKol2018App theApp;
