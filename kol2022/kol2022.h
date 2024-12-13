
// kol2022.h : main header file for the kol2022 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ckol2022App:
// See kol2022.cpp for the implementation of this class
//

class Ckol2022App : public CWinApp
{
public:
	Ckol2022App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ckol2022App theApp;
