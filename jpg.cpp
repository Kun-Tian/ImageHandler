#include"include.h"
extern "C" {
#include "jpeglib.h"
}
#include"jpg.h"

CJPGHandler::CJPGHandler()
{

}
CJPGHandler::~CJPGHandler()
{

}

int CJPGHandler::ReadJPGfile(const char *filename, CImageInfo *img )
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    FILE *f = fopen(filename,"rb");
    if (f==NULL)
    {
        printf("Open file error!\n");
        return -1;
    }
    jpeg_stdio_src(&cinfo, f);
    jpeg_read_header(&cinfo, TRUE);

    int size=cinfo.image_width*cinfo.num_components;
    size+=size%4;//4字节对齐
    size*=cinfo.image_height;
    unsigned char* data = new unsigned char [size];

    jpeg_start_decompress(&cinfo);
    JSAMPROW row_pointer[1];
    while (cinfo.output_scanline < cinfo.output_height)
    {
        int RealSizeEachLine=(cinfo.image_width*cinfo.num_components)+(cinfo.image_width*cinfo.num_components)%4;//字节对齐后的实际每行大小
       row_pointer[0] = (JSAMPROW)&data[(cinfo.output_height - cinfo.output_scanline-1)*RealSizeEachLine];
       jpeg_read_scanlines(&cinfo,row_pointer ,1);
    }
    jpeg_finish_decompress(&cinfo);
    CImageInfo newimg(cinfo.image_width,cinfo.image_height,cinfo.num_components,size,data);
    *img=newimg;
    jpeg_destroy_decompress(&cinfo);

    fclose(f);
    return 0;

}
int CJPGHandler::WriteJPGfile(const char* filename, CImageInfo &img)
{
    struct jpeg_compress_struct jcs;
    // 声明错误处理器，并赋值给jcs.err域
   struct jpeg_error_mgr jem;
   jcs.err = jpeg_std_error(&jem);
   jpeg_create_compress(&jcs);
    FILE* f=fopen(filename,"wb");
   if (f==NULL)
   {
       return -1;
   }

    jpeg_stdio_dest(&jcs, f);
   jcs.image_width = img.GetWidth();    // 为图的宽和高，单位为像素
   jcs.image_height = img.GetHeight();
   jcs.input_components =img.GetChannels();   // 1,表示灰度图， 如果是彩色位图，则为3
    if(jcs.input_components ==3)
   {
        jcs.in_color_space=JCS_RGB;
   }
   else if(jcs.input_components ==4)
   {
       jcs.in_color_space=JCS_EXT_RGBA;
   }
  else
  {
      return -1;
  }
   jpeg_set_defaults(&jcs);
    jpeg_set_quality (&jcs, 80, true);
   jpeg_start_compress(&jcs, TRUE);
   JSAMPROW row_pointer[1];   // 一行位图
   int row_stride;      // 每一行的字节数
    row_stride = jcs.image_width*jcs.input_components ; // 如果不是索引图,此处需要乘以3
   // 对每一行进行压缩
   unsigned char *data=img.GetData();
   while (jcs.next_scanline < jcs.image_height) {
        row_pointer[0] = (JSAMPROW)&data[(jcs.image_height-jcs.next_scanline-1)* row_stride];
        jpeg_write_scanlines(&jcs, row_pointer, 1);
   }
   jpeg_finish_compress(&jcs);
jpeg_destroy_compress(&jcs);
return 0;
}
