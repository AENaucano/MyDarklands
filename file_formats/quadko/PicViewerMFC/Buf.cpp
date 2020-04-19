//
//
//

#include "stdafx.h"
#include "Buf.h"

// Class CBuf::
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


CBuf::CBuf()
{
	Buf = NULL;
	BufAlloc = 0;
	BufLen = 0;
	ReadPos = 0;
	GrowType = BUF_GROWDOUBLE;
}

CBuf::~CBuf()
{
	Reset();

}

CBuf& CBuf::operator =(const CBuf& NewBuf)
//CBuf &CBuf::operator =(CBuf &NewBuf)
{
	Reset();

	SetLen(NewBuf.BufLen);

	if (BufLen > 0)
	{
		memcpy(Buf, NewBuf.Buf, BufLen);
	}

	return *this;
}

BOOL CBuf::Reset()
{
	if (Buf != NULL)
	{
		delete[] Buf;
		Buf = NULL;
		BufAlloc = 0;
		BufLen = 0;
	}
	ReadPos = 0;
	GrowType = BUF_GROWDOUBLE;

	return TRUE;
}

void CBuf::SetGrowType(long growtype)
{
	GrowType = growtype;
}

BOOL CBuf::SetBufLen(long NewLen)
{
	BOOL RetVal = TRUE;

	try
	{
		if (NewLen <= 0)
		{
			BufLen = 0;

			if (Buf != NULL)
			{
				delete[] Buf;
				Buf = NULL;
			}
		}
		else if (NewLen <= BufAlloc)
		{
			BufLen = NewLen;
		}
		else
		{
			if (Buf != NULL)
			{
				delete[] Buf;
			}

			BufAlloc = NewLen;
			BufLen = NewLen;
			Buf = new char[BufAlloc];
		}
	}



	catch (...)

	{
		RetVal = FALSE;
		Buf = NULL;
		BufAlloc = 0;
		BufLen = 0;
	}




	return RetVal;
}

BOOL CBuf::GrowBufLen(long NewLen, long GrowBy)
{
	BOOL RetVal = TRUE;



	try

	{
		if (NewLen <= 0)
		{
			BufLen = 0;

			if (Buf != NULL)
			{
				delete[] Buf;
				Buf = NULL;
			}
		}
		else if (NewLen <= BufAlloc)
		{
			BufLen = NewLen;
		}
		else
		{
			if (Buf != NULL)
			{
				void* NewBuf;

				if (GrowType == BUF_GROWFIXED)
				{
					if (BufAlloc + GrowBy > NewLen)
					{
						GrowBy = BufAlloc + GrowBy;
					}
					else
					{
						GrowBy = NewLen;
					}
				}
				else if (GrowType == BUF_GROWDOUBLE)
				{
					GrowBy = BufAlloc;
					if (GrowBy <= 0) GrowBy = NewLen; //this is likely only the first call.
					else
						while (GrowBy < NewLen) //while it is not big enough!
						{
							GrowBy = 2 * GrowBy; //double the size!
						}
				}
				NewBuf = new char[GrowBy];

				memcpy(NewBuf, Buf, BufLen);

				delete[] Buf;
				Buf = NewBuf;

				BufAlloc = GrowBy;
				BufLen = NewLen;
			}
			else
			{
				BufAlloc = NewLen;
				BufLen = NewLen;
				Buf = new char[BufAlloc];
			}

		}
	}



	catch (...)

	{
		RetVal = FALSE;
		Buf = NULL;
		BufAlloc = 0;
		BufLen = 0;
	}




	return RetVal;
}

CBuf::operator void* ()
{
	return Buf;
}

CBuf::operator const void* ()
{
	return Buf;
}

CBuf::operator char* ()
{
	return (char*)Buf;
}

BOOL CBuf::SetLen(long NewLen)
{
	BOOL RetVal = TRUE;



	try

	{
		if (NewLen <= BufAlloc)
		{
			BufLen = NewLen;
		}
		else
		{
			RetVal = SetAlloc(NewLen);
			BufLen = BufAlloc; //BufAlloc is 0 if there was an error.  Otherwise NewLen
		}
	}



	catch (...)

	{
		RetVal = FALSE;
		Buf = NULL;
		BufAlloc = 0;
		BufLen = 0;
	}




	return RetVal;
}

BOOL CBuf::SetAlloc(long NewAlloc)
{
	BOOL RetVal = TRUE;



	try

	{
		if (NewAlloc > BufAlloc)
		{
			long OldLen = BufLen;
			Reset();

			BufLen = OldLen;
			BufAlloc = NewAlloc;
			Buf = new char[BufAlloc];
		}
	}



	catch (...)

	{
		RetVal = FALSE;
		Buf = NULL;
		BufAlloc = 0;
		BufLen = 0;
	}




	return RetVal;
}

BOOL CBuf::GrowTo(long NewLen)
{
	BOOL RetVal = TRUE;




	try

	{
		if (NewLen < BufAlloc)
		{
			BufLen = NewLen;
		}
		else
		{
			if (Buf == NULL)
			{
				SetLen(NewLen);
			}
			else
			{
				void* NewBuf;

				NewBuf = new char[NewLen];

				memcpy(NewBuf, Buf, BufLen);

				delete[] Buf;
				Buf = NewBuf;

				BufAlloc = NewLen;
				BufLen = NewLen;
			}
		}
	}



	catch (...)

	{
		RetVal = FALSE;
		Buf = NULL;
		BufAlloc = 0;
		BufLen = 0;
	}




	return RetVal;
}

BOOL CBuf::GrowBy(long NewDelta)
{
	return GrowTo(BufLen + NewDelta);
}

BOOL CBuf::GrowAllocTo(long NewAlloc)
{
	BOOL RetVal = TRUE;




	try

	{
		if (NewAlloc <= BufAlloc)
		{
			// Do Nothing
		}
		else
		{
			if (Buf == NULL)
			{
				SetAlloc(NewAlloc);
				BufLen = 0;
			}
			else
			{
				void* NewBuf;

				NewBuf = new char[NewAlloc];

				memcpy(NewBuf, Buf, BufLen);

				delete[] Buf;
				Buf = NewBuf;

				BufAlloc = NewAlloc;
				// BufLen remains unchanged
			}
		}
	}



	catch (...)

	{
		RetVal = FALSE;
		Buf = NULL;
		BufAlloc = 0;
		BufLen = 0;
	}




	return RetVal;
}

BOOL CBuf::GrowAllocBy(long NewDelta)
{
	return GrowAllocTo(BufAlloc + NewDelta);
}

bool CBuf::Swap(CBuf& NewBuf)
{
	void* TBuf;
	long TBufAlloc, TBufLen;

	TBuf = NewBuf.Buf;
	TBufAlloc = NewBuf.BufAlloc;
	TBufLen = NewBuf.BufLen;

	NewBuf.Buf = Buf;
	NewBuf.BufLen = BufLen;
	NewBuf.BufAlloc = BufAlloc;

	Buf = TBuf;
	BufLen = TBufLen;
	BufAlloc = TBufAlloc;

	return true;
}

long CBuf::Read(void* NewBuf, long Len)
{
	if (ReadPos + Len > BufLen)
	{
		Len = BufLen - ReadPos;
	}
	if (Len < 0)
	{
		Len = 0;
	}

	if (Len != 0)
	{
		memcpy((char*)NewBuf, ((char*)Buf) + ReadPos, Len);
	}

	ReadPos += Len;

	return Len;
}

long CBuf::Write(const void* NewBuf, long Len)
{
	long TempPos = BufLen;
	GrowBy(Len);
	memcpy(((char*)Buf) + TempPos, NewBuf, Len);

	return Len;
}

long CBuf::Seek(long Pos, long From) // -1 0 1: from end, from current, from begin
{
	long RetVal = 0;

	if (From == 0)
	{
		ReadPos += Pos;
	}
	else if (From < 0) // -1 --
	{
		ReadPos = BufLen - Pos;
	}
	else //if (From>0) // 1 ++
	{
		ReadPos = Pos;
	}

	if (ReadPos < 0) ReadPos = 0;
	if (ReadPos > BufLen) ReadPos = BufLen;

	RetVal = ReadPos;
	return RetVal;
}


bool CBuf::LoadFromFile(CString Filename)
{
	bool RetVal = false;
	CFile File;

	if (File.Open(Filename, CFile::modeRead))
	{
		RetVal = LoadFromFile(File);
	}

	return RetVal;
}

bool CBuf::SaveToFile(CString Filename)
{
	bool RetVal = false;
	CFile File;

	if (File.Open(Filename, CFile::modeWrite | CFile::modeCreate))
	{
		RetVal = SaveToFile(File);
	}

	return RetVal;
}

bool CBuf::LoadFromFile(CFile& File)
{
	bool RetVal = false;
	long Len;

	Len = File.GetLength() - File.Seek(0, CFile::current);
	SetLen(Len);

	Len = File.Read(Buf, Len);
	SetLen(Len);

	RetVal = true;

	return RetVal;
}

bool CBuf::SaveToFile(CFile& File)
{
	bool RetVal = false;

	File.Write(Buf, GetLen());
	RetVal = true;

	return RetVal;
}