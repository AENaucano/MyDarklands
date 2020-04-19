//////////////////////////////////////////////////////////////////////
// CPicReader
// Read Darklands .pic format pictures
// Written by Joel McIntyre 
// www.joelmcintyre.com www.eliel.com
// copyright 2002
// Use as you please, barring denying my copyright!

#ifndef _DARKLANDS_PICREADER_H_
#define _DARKLANDS_PICREADER_H_

#include "Buf.h"

// RGB Color data structure
typedef struct
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
} TByteRGB;

// Decode Table: holds lists of decoded pixel streams
typedef struct
{
	unsigned char PixelData;
	unsigned short Next;
} TDecodeTable;

// Reads Darklands *.pic image files into a buffer, and allows 
// access to the data directly or via mfc CBitmaps. Removing MFC
// should not be too hard, I think, but will be a little work.
// This class uses CFile, CBitmap, CDC, and CString for the
// helpful extras, but it can be readily stripped down to the core
// image data in memory -> decoded to pixel bytes in memory
// Maybe I will present such a version in the future, too...
// On the whole, modify and use this as you please

class CPicReader  
{
public:
	CPicReader();
	virtual ~CPicReader();
	void Reset();

// Public Interface
public:
	bool Load(const char *Filename); // Load .pic from a file
	bool Load(void *Buf, int BufLen); // Load .pic from a memory buffer (same format as file)

	bool IsValid();

	// Image size funcs
	int GetWidth();
	int GetHeight();
	CSize GetSize();

	// Single Pixel Funcs
	COLORREF GetPixel(int X, int Y); // Get RGB Pixel value (can draw it immediately)
	unsigned char GetPixelByte(int X, int Y); // Get VGA palette index byte (needs color lookup to draw)

	// Full Pixel Buffer funcs
	int GetPixelData(char *Buf, int BufLen); // Get all pixels as RGB values, needs Width*Height*3 buf size, returns memory used
	int GetPixelByteData(char *Buf, int BufLen);// Get all pixels as VGA byte values, needs Width*Height buf size, returns memory used

	// Bitmap Funcs
	bool IsBitmapValid(); // Is a Windows CBitmap Available?
	bool CreateBitmap(int BitCount=-1, CDC *MemoryDC=NULL); // Create a Windows CBitmap from image data
	CBitmap *GetBitmap(); // Get the Windows CBitmap

	// Color Funcs
	COLORREF GetColor(unsigned int Index); // Get color given VGA byte value/palette index (equivalent)
	void SetColor(unsigned int Index, COLORREF NewColor); // Set palette color at specified index (manually trigger recreate bitmap if necessary)

	// File Palette Funcs
	bool HasPalette() {return PaletteExists;} // File had a palette?
	int GetPaletteStart() {return PaletteStart;} // First index of file palette
	int GetPaletteEnd() {return PaletteEnd;} // Last index of file palette

// Helper Funcs
protected:
	bool Load(CFile &File);

	void InitPalette();

	// New Style
	void SetPaletteM0(void *Data,int Len);
	void SetImageX0(void *Data,int Len);

	// File Decoding funcs
	void DecodeImage(void *FileData,int Len);
	unsigned char GetNextPixel(int &StackTop, unsigned short &CurWordValue, unsigned char &BitMaskCount, unsigned short &BitMask,unsigned short *Stack, TDecodeTable *DecodeTable, unsigned short *Data,unsigned char &DataBitCount,unsigned short &PrevIDCode,unsigned char &PrevPixel,unsigned short &CurIndex,unsigned short &DecodeTableIndex, unsigned char &FormatFlag);
	void SetupDecodeTable(TDecodeTable *DecodeTable, unsigned short &BitMask, unsigned short &DecodeTableIndex, unsigned char &BitMaskCount);

// Data
protected:
	bool Valid;

	// Memory Buffers
	CBuf ImageData;
	CBuf FileData;

	// Image data
	int Width;
	int Height;

	// Palette Data
	bool PaletteExists;
	int PaletteStart,PaletteEnd;
	COLORREF Palette[256];

	// Bitmap Data
	bool ValidBitmap;
	CBitmap Bitmap;

};

#endif // #ifndef _DARKLANDS_PICREADER_H_
