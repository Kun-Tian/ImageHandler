#ifndef JPGHANDLER_H_INCLUDED
#define JPGHANDLER_H_INCLUDED

#include"ImageInfo.h"
class CJPGHandler
{
    public:

        static int WriteJPGfile(const char* filename,CImageInfo &img);
         static int ReadJPGfile(const char* filenam,CImageInfo* img);
    private:
          CJPGHandler();
        virtual ~CJPGHandler();
};
#endif // JPGHANDLER_H_INCLUDED
