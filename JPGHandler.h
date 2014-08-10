#ifndef JPGHANDLER_H_INCLUDED
#define JPGHANDLER_H_INCLUDED


class CJPGHandler
{
        CBMPHandler();
        virtual ~CBMPHandler();
        static int WriteJPGfile(const char* filename,ImageInfo img);
         static int ReadJPGfile(const char* filenam,ImageInfo* img);
};
#endif // JPGHANDLER_H_INCLUDED
