#ifndef PNG_H_INCLUDED
#define PNG_H_INCLUDED


#include"ImageInfo.h"


#define PNG_BYTES_TO_CHECK 4
//#define HAVE_ALPHA 1
//#define NO_ALPHA 0

class CPNGHandler
{
      public:
        static int WritePNGfile(const char* filename,CImageInfo& img);
         static int ReadPNGfile(const char* filename,CImageInfo* img);
    private:
        CPNGHandler();
        virtual ~CPNGHandler();

};
#endif // PNG_H_INCLUDED
