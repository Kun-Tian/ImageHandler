#include <png.h>
#include"png.h"
CPNGHandler::CPNGHandler()
{

}

CPNGHandler::~CPNGHandler()
{

}
int CPNGHandler::ReadPNGfile(const char* filename, CImageInfo* img)
{/* 用于解码png图片 */
     FILE *pic_fp;
     pic_fp = fopen(filename, "rb");
     if(pic_fp == NULL) /* 文件打开失败 */
     {
         perror("fopen");
        return -1;
     }
     /* 初始化各种结构 */
     png_structp png_ptr;
     png_infop  info_ptr;
     char        buf[PNG_BYTES_TO_CHECK];
     int        temp;

     png_ptr  = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
     info_ptr = png_create_info_struct(png_ptr);

     setjmp(png_jmpbuf(png_ptr)); // 这句很重要

     temp = fread(buf,1,PNG_BYTES_TO_CHECK,pic_fp);
     temp = png_sig_cmp((png_bytep)buf, (png_size_t)0, PNG_BYTES_TO_CHECK);

     /*检测是否为png文件*/
     if (temp!=0)
     {
         fclose(pic_fp);
          return -1;
     }
     rewind(pic_fp);
     /*开始读文件*/
     png_init_io(png_ptr, pic_fp);
     // 读文件
     png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);


     /*获取宽度，高度，位深，颜色类型*/
     int channels      = png_get_channels(png_ptr, info_ptr); /*获取通道数*/
     int color_type    = png_get_color_type(png_ptr, info_ptr); /*颜色类型*/
      int bit_depth = png_get_bit_depth(png_ptr, info_ptr); /* 获取位深 */

     /* row_pointers里边就是rgba数据 */
     png_bytep* row_pointers;
     row_pointers = png_get_rows(png_ptr, info_ptr);
     int width = png_get_image_width(png_ptr, info_ptr);
     int height = png_get_image_height(png_ptr, info_ptr);

     int size = width *channels;
     size+=size%4;//4字节对齐
     size *= height;

      unsigned char* data = new unsigned char[size];

      int pos = 0;
      int stride=channels;
      for(int i = height-1; i >= 0; i--)//png上下颠倒
      {
           for(int j = 0; j <stride*width; j += stride)
           {/* 一个字节一个字节的赋值 */
                data[pos++] = row_pointers[i][j]; // red
                data[pos++] = row_pointers[i][j+1]; // green
                data[pos++] = row_pointers[i][j+2];  // blue
                if(stride==4)
                {
                    data[pos++] = row_pointers[i][j+3]; // alpha
                }
           }
           pos+=(stride*width)%4;
      }
      CImageInfo newImg(width,height,channels,size,data);
      *img=newImg;
     /* 撤销数据占用的内存 */
     png_destroy_read_struct(&png_ptr, &info_ptr, 0);
     fclose(pic_fp);
     return 0;
}
int CPNGHandler::WritePNGfile(const char *filename , CImageInfo &img)
{
     png_byte color_type;

     png_structp png_ptr;
     png_infop info_ptr;

     /* create file */
     FILE *fp = fopen(filename, "wb");
     if (!fp)
     {
        perror("fopen");
        return -1;
     }

     /* initialize stuff */
     png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

     if (!png_ptr)
     {
            printf("[write_png_file] png_create_write_struct failed");
            return -1;
     }
     info_ptr = png_create_info_struct(png_ptr);
     if (!info_ptr)
     {
            printf("[write_png_file] png_create_info_struct failed");
            return -1;
     }
     if (setjmp(png_jmpbuf(png_ptr)))
     {
            printf("[write_png_file] Error during init_io");
            return -1;
     }
     png_init_io(png_ptr, fp);

     /* write header */
     if (setjmp(png_jmpbuf(png_ptr)))
     {
            printf("[write_png_file] Error during writing header");
            return -1;
     }
     /* 判断要写入至文件的图片数据是否有透明度，来选择色彩类型 */
     if(img.GetChannels()==4)
     {
         color_type = PNG_COLOR_TYPE_RGB_ALPHA;
     }
    else if(img.GetChannels()==3)
    {
        color_type = PNG_COLOR_TYPE_RGB;
    }
    else
    {
        return -1;
    }
     png_set_IHDR(png_ptr, info_ptr, img.GetWidth(), img.GetHeight(),
      8, color_type, PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);//位深暂时默认8

     png_write_info(png_ptr, info_ptr);
     /* write bytes */
     if (setjmp(png_jmpbuf(png_ptr)))
     {
            printf("[write_png_file] Error during writing bytes");
            return -1;
     }

     int pos = 0;
     png_bytep * row_pointers = new png_bytep[img.GetHeight()];
     int SizeEachLine=img.GetChannels() * img.GetWidth();
     unsigned char*data=img.GetData();//获取图像数据
     for(int i = img.GetHeight()-1; i >=0; i--)
     {
          row_pointers[i] =new png_byte[SizeEachLine];
          for(int j = 0; j < SizeEachLine; j += img.GetChannels())
          {
           row_pointers[i][j]  = data[pos++]; // red
           row_pointers[i][j+1] = data[pos++]; // green
           row_pointers[i][j+2] = data[pos++];  // blue
           if(img.GetChannels()==4)
                row_pointers[i][j+3] = data[pos++]; // alpha
          }
            pos+=SizeEachLine%4;
     }
     png_write_image(png_ptr, row_pointers);

     /* end write */
     if (setjmp(png_jmpbuf(png_ptr)))
     {
        printf("[write_png_file] Error during end of write");
        return -1;
     }
     png_write_end(png_ptr, NULL);

        /* cleanup heap allocation */
     for (int j=0; j<img.GetHeight(); j++)
        delete []row_pointers[j];
     delete []row_pointers;

    fclose(fp);
    return 0;
}

