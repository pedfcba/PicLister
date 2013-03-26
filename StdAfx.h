// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//


#undef WINVER //取消原有版本定义,重新定义版本
#define WINVER 0x5000 //为了使AnimateWindow函数可用



#if !defined(AFX_STDAFX_H__7F782C22_2EF8_4F03_85E4_88A66752ABD8__INCLUDED_)
#define AFX_STDAFX_H__7F782C22_2EF8_4F03_85E4_88A66752ABD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls

#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__7F782C22_2EF8_4F03_85E4_88A66752ABD8__INCLUDED_)
