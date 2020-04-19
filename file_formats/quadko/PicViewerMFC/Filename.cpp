//
//
//

#include "stdafx.h"
#include "Filename.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// Class CFilename::

CFilename::CFilename()
{
	bDrive = FALSE;
	bPath = FALSE;
	bTitle = FALSE;
	bExt = FALSE;

	CPoint NullPoint(0, 0);

	pDrive = NullPoint;
	pPath = NullPoint;
	pTitle = NullPoint;
	pExt = NullPoint;
}

CFilename::CFilename(const char* nFilename)
{
	bDrive = FALSE;
	bPath = FALSE;
	bTitle = FALSE;
	bExt = FALSE;

	CPoint NullPoint(0, 0);

	pDrive = NullPoint;
	pPath = NullPoint;
	pTitle = NullPoint;
	pExt = NullPoint;
	Set(nFilename);
}

CFilename::~CFilename()
{
}


void CFilename::Set(const char* nFilename)
{
	Filename = nFilename;

	bDrive = FALSE;
	bPath = FALSE;
	bTitle = FALSE;
	bExt = FALSE;

	CPoint NullPoint(0, 0);

	pDrive = NullPoint;
	pPath = NullPoint;
	pTitle = NullPoint;
	pExt = NullPoint;

	long max, Pos;
	max = Filename.GetLength();

	// Look for Drive
	if (max > 1)
	{
		if (Filename[1] == ':')
		{
			pDrive.x = 0;
			pDrive.y = 2;
			bDrive = TRUE;
		}
		else if (Filename[0] == '\\' && Filename[1] == '\\')
		{
			pDrive.x = 0;
			pDrive.y = QFind('\\', 2);
			if (pDrive.y == -1)
			{
				pDrive.y = max;
			}
			bDrive = TRUE;
		}
	}


	if (max > 0)
	{
		// Look for filename
		Pos = Filename.ReverseFind('\\');
		if (Pos != -1 && (bDrive ? Pos >= (pDrive.x + pDrive.y) : TRUE))
		{
			pTitle.x = Pos + 1;
			pTitle.y = max - Pos - 1;
			bTitle = TRUE;
		}
		else if (Pos == -1)
		{
			if (bDrive)
			{
				pTitle.x = pDrive.x + pDrive.y;
				pTitle.y = max - pTitle.x;
				bTitle = TRUE;
			}
			// whole string is filename
			else
			{
				pTitle.x = 0;
				pTitle.y = max;
				bTitle = TRUE;
			}
		}

		// Look for file ext. (if no filename, no extention)
		if (bTitle)
		{
			Pos = Filename.ReverseFind('.');

			if (Pos >= pTitle.x)
			{
				pTitle.y = Pos - pTitle.x;

				pExt.x = Pos + 1;
				pExt.y = max - Pos - 1;
				bExt = TRUE;
			}
		}

		// Get Path from other information
		if (bDrive)
		{
			pPath.x = pDrive.x + pDrive.y;
		}
		else
		{
			pPath.x = 0;
		}
		if (bTitle)
		{
			pPath.y = pTitle.x - pPath.x;
		}
		else
		{
			pPath.y = max - pPath.x;
		}

		if (pPath.y > 0)
		{
			bPath = TRUE;
		}
		else
		{
			pPath = NullPoint;
		}
	}
}

void CFilename::Get(CString& String, int Parts)
{
	String.Empty();

	if (Parts == All)
	{
		String = Filename;
	}
	else
	{
		if ((Parts & Drive) && bDrive)
		{
			String += Filename.Mid(pDrive.x, pDrive.y);
		}

		if ((Parts & Path) && bPath)
		{
			String += Filename.Mid(pPath.x, pPath.y);
		}

		if ((Parts & Title) && bTitle)
		{
			String += Filename.Mid(pTitle.x, pTitle.y);
		}

		if ((Parts & Dot) && bExt)
		{
			String += '.';
		}

		if ((Parts & Ext) && bExt)
		{
			String += Filename.Mid(pExt.x, pExt.y);
		}
	}
}

CString CFilename::Get(int Parts)
{
	CString RetVal;
	Get(RetVal, Parts);
	return RetVal;
}

long CFilename::QFind(char Char, long StartFrom)
{
	long RetVal = -1;
	long max = Filename.GetLength();
	long cnt = StartFrom;

	while (cnt < max && RetVal == -1)
	{
		if (Filename.GetAt(cnt) == Char)
		{
			RetVal = cnt;
		}
		cnt++;
	}

	return RetVal;
}


bool CFilename::Exists()
{
	bool RetVal = false;

	CFileStatus Status;

	if (CFile::GetStatus(Filename, Status))
	{
		RetVal = true;
	}

	return RetVal;
}

CString CFilename::GetFilename(const char* Filename, int Parts)
{
	CFilename FileHelper;
	FileHelper.Set(CString(Filename));
	return FileHelper.Get(Parts);
}

CString AfxFilename(const char* Filename, int Parts)
{
	return CFilename::GetFilename(Filename, Parts);
}