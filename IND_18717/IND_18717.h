
// IND_18717.h : main header file for the IND_18717 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CIND18717App:
// See IND_18717.cpp for the implementation of this class
//

class CIND18717App : public CWinApp
{
public:
	CIND18717App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CIND18717App theApp;
