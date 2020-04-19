//
//
//

#ifndef _FILENAME_H_
#define _FILENAME_H_

#define FN_Drive 1 
#define FN_Path 2 
#define FN_DrivePath 3
#define FN_Title 4
#define FN_DriveTitle 5
#define FN_PathTitle 6
#define FN_DrivePathTitle 7
#define FN_Ext 8
#define FN_DriveExt 9
#define FN_PathExt 10
#define FN_DrivePathExt 11
#define FN_DriveTitleExt 13
#define FN_PathTitleExt 14
#define FN_Dot 16
#define FN_DotExt 24
#define FN_dExt 24
#define FN_Exten 24
#define FN_TitleDotExt 28
#define FN_TitleExt 28
#define FN_Name 28
#define FN_FileName 28
#define FN_PathName 30
#define FN_DrivePathTitleExt 31
#define FN_DrivePathTitleDotExt 31
#define FN_All 31
#define FN_Full 31

class CFilename
{
public:
	CFilename();
	CFilename(const char *nFilename);
	~CFilename();

	void Set(const char *nFilename);
	CString Get(int Parts);
	void Get(CString &String,int Parts);

	bool Exists();

public:
	static CString GetFilename(const char *Filename, int Parts);

public:
	enum {Drive =1, 
		  Path =2, 
		  DrivePath =3,
		  Title =4,
		  DriveTitle =5,
		  PathTitle =6,
		  DrivePathTitle =7,
		  Ext =8,
		  DriveExt =9,
		  PathExt =10,
		  DrivePathExt =11,
		  DriveTitleExt =13,
		  PathTitleExt =14,
		  Dot =16,
		  DotExt =24,
		  dExt =24,
		  Exten =24,
		  TitleDotExt =28,
		  TitleExt =28,
		  Name =28,
		  FileName =28,
		  PathName =30,
		  DrivePathTitleExt =31,
		  DrivePathTitleDotExt =31,
		  All =31,
		  Full =31};


protected:
	long QFind(char Char, long StartFrom=0);

protected:
	CString Filename;
	
	CPoint pDrive,pPath,pTitle,pExt;
	BOOL bDrive,bPath,bTitle,bExt;
};

CString AfxFilename(const char *Filename, int Parts);

#endif