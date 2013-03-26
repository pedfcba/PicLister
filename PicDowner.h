// PicDowner.h : main header file for the PICDOWNER application
//

#if !defined(AFX_PICDOWNER_H__9A2520D9_05FE_4B99_A3E2_D52B894683FF__INCLUDED_)
#define AFX_PICDOWNER_H__9A2520D9_05FE_4B99_A3E2_D52B894683FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPicDownerApp:
// See PicDowner.cpp for the implementation of this class
//

class CPicDownerApp : public CWinApp
{
public:
	CPicDownerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicDownerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPicDownerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICDOWNER_H__9A2520D9_05FE_4B99_A3E2_D52B894683FF__INCLUDED_)
