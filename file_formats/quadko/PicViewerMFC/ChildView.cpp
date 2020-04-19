// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "PicViewer.h"
#include "ChildView.h"
#include "Filename.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
	StretchMode = 0;
	ViewPalette = true;

}

CChildView::~CChildView()
{
}

void CChildView::Reset()
{
	Image.Reset();
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_VIEW_SIZENORMAL, OnViewSizenormal)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SIZENORMAL, OnUpdateViewSizenormal)
	ON_COMMAND(ID_VIEW_SIZESTRETCH, OnViewSizestretch)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SIZESTRETCH, OnUpdateViewSizestretch)
	ON_COMMAND(ID_VIEW_SIZEX2, OnViewSizex2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SIZEX2, OnUpdateViewSizex2)
	ON_COMMAND(ID_VIEW_SIZEX3, OnViewSizex3)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SIZEX3, OnUpdateViewSizex3)
	ON_COMMAND(ID_VIEW_SIZEX4, OnViewSizex4)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SIZEX4, OnUpdateViewSizex4)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_PALETTE, OnViewPalette)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PALETTE, OnUpdateViewPalette)
	//}}AFX_MSG_MAP

	ON_MESSAGE((WM_USER + 2), OnInitialUpdate)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

BOOL CChildView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	BOOL RetVal = FALSE;

	if (CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext))
	{
		BitmapDC.CreateCompatibleDC(NULL);
		PostMessage((WM_USER + 2), 0, 0);

		RetVal = TRUE;
	}

	return RetVal;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	long X = 3, Y = 20, XInc = 25, YInc = 16, XInc2 = 10, X2 = 0;
	CString String;
	CString TempString;
	long cnt = 0, max = 0;
	long Square = 5;

	CRect Rect;
	GetClientRect(&Rect);

	// Clear background
	dc.FillSolidRect(0, 0, Rect.right, Rect.bottom, 0);

	if (ViewPalette)
	{
		Rect.bottom -= 30;
	}

	// Paste up picture
	X = 0;
	Y = 0;

	if (Image.IsBitmapValid())
	{
		BitmapDC.SelectObject(Image.GetBitmap());

		if (StretchMode == 0)
		{
			// center
			X = max(0, (Rect.right - Image.GetWidth()) / 2);
			Y = Rect.bottom - Image.GetHeight();

			Y = max(0, Y / 2);

			dc.BitBlt(X, Y, Image.GetWidth(), Image.GetHeight(), &BitmapDC, 0, 0, SRCCOPY);
		}
		else if (StretchMode == 1)
		{
			// center
			X = max(0, (Rect.right - Image.GetWidth() * StretchMagnitude) / 2);

			Y = Rect.bottom - Image.GetHeight() * StretchMagnitude;

			Y = max(0, Y / 2);

			dc.StretchBlt(X, Y, Image.GetWidth() * StretchMagnitude, Image.GetHeight() * StretchMagnitude, &BitmapDC, 0, 0, Image.GetWidth(), Image.GetHeight(), SRCCOPY);
		}
		else if (StretchMode == 2)
		{
			dc.StretchBlt(X, Y, Rect.Width(), Rect.Height() - Y, &BitmapDC, 0, 0, Image.GetWidth(), Image.GetHeight(), SRCCOPY);
		}
	}

	// Draw Palette

	if (ViewPalette)
	{

		COLORREF CurColor;
		long cnt, max;
		long XDelta;
		max = 256;
		long OrixX;

		X = 0;
		Y = Rect.bottom + 3;
		XDelta = (Square + 1) * 64 + 2;
		OrixX = max(3, (Rect.right - (64 * (Square + 1) + 1) * 2) / 2);

		dc.FillSolidRect(0, Rect.bottom, Rect.right, 30, RGB(255, 255, 255));

		dc.FillSolidRect(OrixX + X - 1, Y - 1, 64 * (Square + 1) + 1, (Square + 1) * 4 + 1, 0);
		dc.FillSolidRect(OrixX + X - 1 + XDelta, Y - 1, 64 * (Square + 1) + 2, (Square + 1) * 4 + 1, 0);

		// Setup for first inc
		Y -= Square + 1;

		for (cnt = 0; cnt < max; cnt++)
		{
			if (cnt % 64 == 0)
			{
				X = 0;
				Y += Square + 1;
			}

			CurColor = Image.GetColor(cnt);
			dc.FillSolidRect(OrixX + X, Y, Square, Square, CurColor);
			dc.FillSolidRect(OrixX + X + XDelta, Y, Square + 1, Square, CurColor);
			X += Square + 1;
		}
	}
}

void CChildView::OnFileOpen()
{
	CFileDialog Dialog(true, "", "", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, "PIC Files|*.pic|All files|*.*||");
	CString InitialDir = AfxGetApp()->GetProfileString("Directories", "Default", "");
	Dialog.m_ofn.lpstrInitialDir = InitialDir;

	if (Dialog.DoModal() == IDOK)
	{
		Open(Dialog.GetPathName());
	}

}

bool CChildView::Open(const char* Filename)
{
	bool RetVal = false;

	CFilename FullFilename;
	Reset();

	Image.Load(Filename);
	Image.CreateBitmap();

	FullFilename.Set(Filename);
	CChildView::Filename = Filename;


	// Set window title
	CString String;

	String.LoadString(AFX_IDS_APP_TITLE);
	String += " - ";
	String += FullFilename.Get(FN_Name);

	AfxGetMainWnd()->SetWindowText(String);
	AfxGetApp()->WriteProfileString("Directories", "Default", FullFilename.Get(FN_DrivePath));

	// Set status bar palette indicator
	if (Image.HasPalette())
	{
		((CStatusBar*)((CFrameWnd*)AfxGetMainWnd())->GetMessageBar())->SetPaneText(1, "Palette is Present");
	}
	else
	{
		((CStatusBar*)((CFrameWnd*)AfxGetMainWnd())->GetMessageBar())->SetPaneText(1, "No Palette in File");
	}


	Invalidate();
	RetVal = true;

	return RetVal;
}


void CChildView::OnViewSizenormal()
{
	StretchMode = 0;
	StretchMagnitude = 1;
	Invalidate();
}

void CChildView::OnUpdateViewSizenormal(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(StretchMode == 0);
}

void CChildView::OnViewSizestretch()
{
	StretchMode = 2;
	StretchMagnitude = 1;
	Invalidate();
}

void CChildView::OnUpdateViewSizestretch(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(StretchMode == 2);
}

void CChildView::OnViewSizex2()
{
	StretchMode = 1;
	StretchMagnitude = 2;
	Invalidate();
}

void CChildView::OnUpdateViewSizex2(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(StretchMode == 1 && StretchMagnitude == 2);
}

void CChildView::OnViewSizex3()
{
	StretchMode = 1;
	StretchMagnitude = 3;
	Invalidate();
}

void CChildView::OnUpdateViewSizex3(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(StretchMode == 1 && StretchMagnitude == 3);
}

void CChildView::OnViewSizex4()
{
	StretchMode = 1;
	StretchMagnitude = 4;
	Invalidate();
}

void CChildView::OnUpdateViewSizex4(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(StretchMode == 1 && StretchMagnitude == 4);
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

void CChildView::OnViewPalette()
{
	ViewPalette = !ViewPalette;
	Invalidate();

}

void CChildView::OnUpdateViewPalette(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(ViewPalette);
}


LRESULT CChildView::OnInitialUpdate(WPARAM, LPARAM)
{
	CWinApp* App = AfxGetApp();
	if (App)
	{
		CString CommandLine = App->m_lpCmdLine;

		// remove offending characters
		CommandLine.Replace("\"", "");

		if (!CommandLine.IsEmpty())
		{
			Open(CommandLine);
		}
	}

	return 0;
}