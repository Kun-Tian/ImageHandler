#include"bmp.h"

#include"ImageHandler.h"
#include "include.h"

CBMPHandler::CBMPHandler()
{
}
CBMPHandler::~CBMPHandler()
{
}
int CBMPHandler::WriteBMPfile(const char* filename, CImageInfo &img)
{
     FILE*     pWritingFile=NULL;
      pWritingFile = fopen(filename, "wb");
     if( pWritingFile == NULL )
     {
           perror("fopen");
           return -1;
     }
     //计算图像字节数
     unsigned int PixelDataLength=img.GetSize();

    BITMAPFILEHEADER FileHeader;    //接受位图文件头
    BITMAPINFOHEADER InfoHeader;    //接受位图信息头
    FileHeader.bfType=BITMAP_ID;                                                  //ID设置为位图的id号
     FileHeader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);      //实际图像数据的位置在文件头和信息头之后
     FileHeader.bfReserved1=0;                                                    //必须设置为0
     FileHeader.bfReserved2=0;                                                    //必须设置为0
     FileHeader.bfSize=PixelDataLength+FileHeader.bfOffBits;                      //BMP图像文件大小

    InfoHeader.biXPelsPerMeter = 0;                                              //水平分辨率，这里暂时设为0就是
    InfoHeader.biYPelsPerMeter = 0;                                              //垂直分辨率，这里暂时设为0就是
    InfoHeader.biClrUsed = 0;                                                    //图像使用的颜色，这里暂时设为0就是
    InfoHeader.biClrImportant = 0;                                                //重要的颜色数，这里暂时设为0就是                        //垂直分辨率，这里暂时设为0就是
    InfoHeader.biPlanes=1;                //必须设置为1
    InfoHeader.biCompression=0;                                              //设置为BI_RGB时,表示图像并没有彩色表
    InfoHeader.biBitCount=img.GetChannels()*8;                                                    //图像的位数
    InfoHeader.biSize=sizeof(BITMAPINFOHEADER);                                  //结构体的大小
    InfoHeader.biHeight=img.GetHeight();
    InfoHeader.biWidth=img.GetWidth();
    InfoHeader.biSizeImage=PixelDataLength;

    CImageInfo tmp=img;
    tmp.ConvergeOrder();//转化为 bgr（A）
    fwrite(&FileHeader, sizeof(BITMAPFILEHEADER), 1, pWritingFile);
    fwrite(&InfoHeader, sizeof(BITMAPINFOHEADER), 1, pWritingFile);
    fwrite(tmp.GetData(), InfoHeader.biSizeImage, 1, pWritingFile);
     // 释放内存和关闭文件
     fclose(pWritingFile);
     return 0;
}
int CBMPHandler::ReadBMPfile(const char* filename,CImageInfo *img)
{

     FILE* pWritingFile = fopen(filename, "rb");
     if( pWritingFile == NULL )
     {
           perror("fopen");
           return -1;
     }

     BITMAPFILEHEADER FileHeader;    //接受位图文件头
    BITMAPINFOHEADER InfoHeader;    //接受位图信息头

    fread(&FileHeader, sizeof(BITMAPFILEHEADER), 1, pWritingFile);
   fread(&InfoHeader, sizeof(BITMAPINFOHEADER), 1, pWritingFile);
   char buf[1024];
   fread(buf,FileHeader.bfOffBits-sizeof(BITMAPFILEHEADER)-sizeof(BITMAPINFOHEADER),1,pWritingFile);
   //获取图像宽度，高度，大小
   int width=InfoHeader.biWidth;
    int height=InfoHeader.biHeight;
    int PixelDataLength=FileHeader.bfSize-FileHeader.bfOffBits;
    int Channels=InfoHeader.biBitCount/8;

     unsigned char* data=new unsigned char[PixelDataLength];


    fread(data, PixelDataLength, 1, pWritingFile);
        CImageInfo imgTmp(width,height,Channels,PixelDataLength,data);
      imgTmp.ConvergeOrder();//转化为 R G B（A）
        *img=imgTmp;
   fclose(pWritingFile);
   return 0;

}

