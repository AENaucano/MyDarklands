// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__2170C03B_2174_4863_9982_014E4CE39070__INCLUDED_)
#define AFX_CHILDVIEW_H__2170C03B_2174_4863_9982_014E4CE39070__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "Buf.h"
#include "PicReader.h"

/////////////////////////////////////////////////////////////////////////////
// CChildView window

typedef struct
{
	short Tag;
	unsigned short Size;
	long FileOffset;
	long DataOffset; // FileOffset +4 in this case, but good practice to have separate
} TDirectoryItem;

class CChildView : public CWnd
{
	// int
public:
	CChildView();
	void Reset();
	bool Open(const char* Filename);

	CPicReader Image;

	long StretchMode;
	long StretchMagnitude = 1;
	CDC BitmapDC;
	CString Filename;

	bool ViewPalette;

	/*


	CBuf FileData;
	CBuf ImageData;

	short Tag;
	long DataLen;
	long Width,Height;

	void ParseFileData();

	TDirectoryItem Dir[5];
	long NumDirItems;

	TDirectoryItem *GetItem(short Tag);

	TByteRGB *Palette;
	long PaletteStart;
	long PaletteEnd;

	COLORREF VGAColors[256];

	COLORREF GetColor(TByteRGB &Data);
	COLORREF GetColor(unsigned long Index);

	void CreateBitmapFromX0();
	CBitmap Bitmap;
	long Bits;



	void AssemblyHacking();
	*/


	//long M0Diffs;
	//long CompareM0ToDefault();



// Attributes
public:

	// Operations
public:

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CChildView)
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg LRESULT OnInitialUpdate(WPARAM, LPARAM);
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnFileOpen();
	afx_msg void OnViewSizenormal();
	afx_msg void OnUpdateViewSizenormal(CCmdUI* pCmdUI);
	afx_msg void OnViewSizestretch();
	afx_msg void OnUpdateViewSizestretch(CCmdUI* pCmdUI);
	afx_msg void OnViewSizex2();
	afx_msg void OnUpdateViewSizex2(CCmdUI* pCmdUI);
	afx_msg void OnViewSizex3();
	afx_msg void OnUpdateViewSizex3(CCmdUI* pCmdUI);
	afx_msg void OnViewSizex4();
	afx_msg void OnUpdateViewSizex4(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnViewPalette();
	afx_msg void OnUpdateViewPalette(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__2170C03B_2174_4863_9982_014E4CE39070__INCLUDED_)
