#ifndef IMAGEHANDLER_H_INCLUDED
#define IMAGEHANDLER_H_INCLUDED
#include"ImageInfo.h"

#define BITMAP_ID 0x4D42
#define JPEG_ID 0xFFD8FF
#define TIFF_ID 0x002a4949
#define PNG_ID 0x474e5089
#define GIF_ID  0x38464947


typedef enum filetype
{
    JPEG_TYPE,
    BITMAP_TYPE,
    TIFF_TYPE,
    PNG_TYPE,
    GIF_TYPE,
    UNKNOWN_TYPE
}enum_filetype;

class CImageHandler
{
   public:
        static int ReadImageFromFile(const char* filename,CImageInfo* imageinfo);
        static enum_filetype GetFileType(const char* filename);
        static int WriteImageToFile(const char* filename,CImageInfo &ImageInfo,enum_filetype type);
        static int ConvergeOrder( CImageInfo* imageinfo);
    private:
    CImageHandler();
        virtual ~CImageHandler();

};
#endif // IMAGEHANDLER_H_INCLUDED
