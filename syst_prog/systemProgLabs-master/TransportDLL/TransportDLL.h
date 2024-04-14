// TransportDLL.h : main header file for the TransportDLL DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTransportDLLApp
// See TransportDLL.cpp for the implementation of this class
//

class CTransportDLLApp : public CWinApp
{
public:
	CTransportDLLApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
