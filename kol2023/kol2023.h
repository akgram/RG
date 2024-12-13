
// kol2023.h : main header file for the kol2023 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ckol2023App:
// See kol2023.cpp for the implementation of this class
//

class Ckol2023App : public CWinApp
{
public:
	Ckol2023App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ckol2023App theApp;
