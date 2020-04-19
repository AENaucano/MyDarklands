// PicViewer.h : main header file for the PicVIEWER application
//

#if !defined(AFX_PicVIEWER_H__C32D81F1_0C6E_48D2_87E5_128AFDBC62BC__INCLUDED_)
#define AFX_PicVIEWER_H__C32D81F1_0C6E_48D2_87E5_128AFDBC62BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPicViewerApp:
// See PicViewer.cpp for the implementation of this class
//

class CPicViewerApp : public CWinApp
{
public:
	CPicViewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicViewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CPicViewerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PicVIEWER_H__C32D81F1_0C6E_48D2_87E5_128AFDBC62BC__INCLUDED_)
