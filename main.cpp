#include"include.h"
#include"ImageHandler.h"





int main()
{

    CImageInfo Info;
   // CImageHandler::ReadImageFromFile("hello.png",&Info);
    // CImageHandler::ReadImageFromFile("hello.jpg",&Info);
     CImageHandler::ReadImageFromFile("hello.bmp",&Info);
        CImageHandler::WriteImageToFile("test.jpg",Info,JPEG_TYPE);
    CImageHandler::WriteImageToFile("test.bmp",Info,BITMAP_TYPE);
        CImageHandler::WriteImageToFile("test.png",Info,PNG_TYPE);

    return 0;
}
