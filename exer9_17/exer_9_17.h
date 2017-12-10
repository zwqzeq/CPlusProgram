// exer_9_17.h : main header file for the EXER_9_17 application
//

#if !defined(AFX_EXER_9_17_H__6A037A51_3535_44D8_886A_0DB976B9885C__INCLUDED_)
#define AFX_EXER_9_17_H__6A037A51_3535_44D8_886A_0DB976B9885C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExer_9_17App:
// See exer_9_17.cpp for the implementation of this class
//

class CExer_9_17App : public CWinApp
{
public:
	CExer_9_17App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExer_9_17App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExer_9_17App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXER_9_17_H__6A037A51_3535_44D8_886A_0DB976B9885C__INCLUDED_)
