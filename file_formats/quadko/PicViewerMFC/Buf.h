//
//
//

#ifndef _BUF_H_
#define _BUF_H_


#define BUF_GROWDOUBLE	1
#define BUF_GROWFIXED	0

class CBuf
{
public:
	operator char *();
	operator void *();
	operator const void *();
	void *GetBuf() {return Buf;}
	void *GetBuf(long Offset) {return &(((char*)Buf)[Offset]);}
	void *GetBufReadPos() {return &(((char*)Buf)[ReadPos]);}

	BOOL SetBufLen(long NewLen);
	BOOL GrowBufLen(long NewLen,long GrowBy=0);
	long GetLen() {return BufLen;}

	long GetAlloc() {return BufAlloc;}
	BOOL SetLen(long NewLen);
	BOOL SetAlloc(long NewAlloc);
	BOOL GrowTo(long NewLen);
	BOOL GrowBy(long NewDelta);
	BOOL GrowAllocTo(long NewAlloc);
	BOOL GrowAllocBy(long NewDelta);

	void SetGrowType (long growtype);
	
	BOOL Reset();

	void ResetRead() {ReadPos=0;}
	long Read(void *NewBuf,long Len);
	long Write(const void *NewBuf,long Len);
	long Seek(long Pos, long From=0); // -1 0 1: from end, from current, from begin
	long GetReadPos() {return ReadPos;}

	bool LoadFromFile(CString Filename);
	bool SaveToFile(CString Filename);
	bool LoadFromFile(CFile &File);
	bool SaveToFile(CFile &File);

	CBuf();
	~CBuf();

	CBuf &operator =(const CBuf &NewBuf);
	//CBuf &operator =(CBuf &NewBuf);

	bool Swap(CBuf &NewBuf);

protected:

	void *Buf;
	long BufAlloc,BufLen;
	long ReadPos;
	long GrowType;
};

#endif