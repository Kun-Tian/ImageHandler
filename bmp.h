#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED




#include"ImageInfo.h"
typedef struct tagRGBQUAD {
  char    rgbBlue;
  char   rgbGreen;
  char    rgbRed;
  char    rgbReserved;
} RGBQUAD;
typedef struct tagBITMAPINFOHEADER { /* bmih */
int biSize;
long biWidth;
long biHeight;
short biPlanes;
short biBitCount;
int biCompression;
int biSizeImage;
long biXPelsPerMeter;
long biYPelsPerMeter;
int biClrUsed;
int biClrImportant;
} __attribute__ ((packed))BITMAPINFOHEADER;//取消类型对齐

typedef struct tagBITMAPFILEHEADER { /* bmfh */
short bfType;
int bfSize;
short bfReserved1;
short bfReserved2;
int bfOffBits;
} __attribute__ ((packed))BITMAPFILEHEADER;//取消类型对齐

typedef struct tagBITMAPINFO { /* bmi */
BITMAPINFOHEADER bmiHeader;
RGBQUAD bmiColors[1];
} BITMAPINFO;

class CBMPHandler
{
    public:
        static int WriteBMPfile(const char* filename,CImageInfo& img);
         static int ReadBMPfile(const char* filenam,CImageInfo* img);
    private:
        CBMPHandler();
        virtual ~CBMPHandler();
};

#endif // BMP_H_INCLUDED
