#include"ImageInfo.h"
#include"include.h"
 CImageInfo::CImageInfo()
 {
     m_data=NULL;
     m_nChannels=0;
     m_width=0;
     m_height=0;
     m_size=0;
 }
 CImageInfo::~CImageInfo()
 {
     if(m_data)
     {
          delete []m_data;
     }

 }
 CImageInfo::CImageInfo(int width,int height,int Channels,int size,unsigned char* data)
 {
        m_width=width;
        m_height=height;
        m_nChannels=Channels;
        m_data=data;
        m_size=size;
 }
 CImageInfo::CImageInfo(const CImageInfo& img)
 {
     *this=img;
 }
int CImageInfo::ConvergeOrder()
{//将数据从BGR BGRA 转化位RGB RGBA
    for(int i=0;i<m_height;i++)
    {
        for(int j=0;j<m_width;j++)
        {
              unsigned char * pos=m_data+i*m_width*m_nChannels+m_nChannels*j;
             unsigned char temp=pos[0];
             pos[0]= pos[2];
             pos[2]=temp;
        }
    }
    return 0;
}
 CImageInfo&  CImageInfo::operator = (const CImageInfo& img)
 {
        if (this == &img) // 如果自己给自己赋值则直接返回
        {
            return *this;
        }
        m_width=img.m_width;
        m_height=img.m_height;
        m_nChannels=img.m_nChannels;
        m_size=img.m_size;
        unsigned char *temp=new unsigned char[m_size]; //复制指针指向的内容
        memcpy(temp,img.m_data,m_size*sizeof(unsigned char));
        if(m_data)
        {
            delete []m_data;//删除原指针指向内容(将删除操作放在后面，避免X=X特殊情况下，内容的丢失)
        }
        m_data=temp;//建立新指向
 }
