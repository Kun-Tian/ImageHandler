#ifndef IMAGEINFO_H_INCLUDED
#define IMAGEINFO_H_INCLUDED



typedef enum colororder
{
    RGB_ORDER,
    RGBA_ORDER,
    BGR_ORDER,
    BGRA_ORDER
}enum_color_order;

class CImageInfo
{

public:
    CImageInfo();
     virtual ~CImageInfo();
    CImageInfo(int width,int height,int Channels,int size,unsigned char* data);
    CImageInfo(const CImageInfo& img);
    CImageInfo& operator = (const CImageInfo& img); //赋值符重载
    int GetWidth(){return m_width;}
    int GetHeight(){return m_height; }
    unsigned int GetSize(){return m_size;}
    int GetChannels(){return m_nChannels;}
    unsigned char* GetData(){return m_data;}
    int ConvergeOrder();
private:

    int m_width;
    int m_height;
    int m_nChannels;   /* 通道数 */
    int m_bitDepth;
    unsigned int m_size;//数据大小
    //enum_color_order m_order;//R G B 的顺序
    unsigned char* m_data;//像素数据  统一按R G B (A)的顺序存储
};


#endif // IMAGEINFO_H_INCLUDED
