#include"ImageHandler.h"
#include"include.h"
#include"bmp.h"
#include"jpg.h"
#include"png.h"

CImageHandler::CImageHandler()
{

}
CImageHandler::~CImageHandler()
{
}

 enum_filetype CImageHandler::GetFileType(const char* filename)
 {
        enum_filetype ret=UNKNOWN_TYPE;
        FILE *pFile=fopen(filename,"rb");
        if (pFile==NULL)
        {
            printf("Open file error %s!\n",filename);
            return ret;
        }
       int nFlag;
        fread(&nFlag,4,1,pFile);
        if(nFlag==TIFF_ID)
        {
            ret=TIFF_TYPE;
        }
        else if(nFlag==PNG_ID)
        {
             ret=PNG_TYPE;
        }
        else if(nFlag==GIF_ID)
        {
             ret=GIF_TYPE;
        }
        else if((nFlag&0XFFFFFF)==JPEG_ID)
        {
             ret=JPEG_TYPE;
        }
        else if((nFlag&0xFFFF)==BITMAP_ID)
        {
             ret=BITMAP_TYPE;
        }
        else
        {
             ret=UNKNOWN_TYPE;
        }
        fclose(pFile);
        return ret;
 }
int CImageHandler::ReadImageFromFile(const char* filename,CImageInfo* imageinfo)
{
        enum_filetype Imgtype=GetFileType(filename);
        switch(Imgtype)
        {
            case BITMAP_TYPE:
               return CBMPHandler::ReadBMPfile(filename,imageinfo);
            case JPEG_TYPE:
                return CJPGHandler::ReadJPGfile(filename,imageinfo);
            case PNG_TYPE:
                return CPNGHandler::ReadPNGfile(filename,imageinfo);
            default:
                return -1;
        }
}
int CImageHandler::WriteImageToFile(const char* filename,CImageInfo& ImageInfo,enum_filetype type)
{
        switch(type)
        {
            case BITMAP_TYPE:
                CBMPHandler::WriteBMPfile(filename,ImageInfo);
                return 0;
            case JPEG_TYPE:
                CJPGHandler::WriteJPGfile(filename,ImageInfo);
                return 0;
       case PNG_TYPE:
                CPNGHandler::WritePNGfile(filename,ImageInfo);
                return 0;
            default:
            break;
        }
        return -1;
}
