
#ifndef _BMP_H
#define _BMP_H

#include "common.h"

#pragma pack(1)
/**< BMP文件头 */
typedef  struct  BMPHEADER_S {
        WORD    bfType;            /* 说明文件的类型 */
        DWORD   bfSize;            /* 说明文件的大小，用字节为单位*/
                                   /* 注意此处的字节序问题*/
        WORD    bfReserved1;       /* 保留，设置为0 */
        WORD    bfReserved2;       /* 保留，设置为0 */
        DWORD   bfOffBits;         /* 说明从BMPHEADER_S结构开始到实际的图像数据之间的字节偏移量 */
}BMPHEADER_S;
/**< BMP文件信息头 */
typedef struct BMPINFOHEADER_S {
        DWORD    biSize;            /* 说明结构体所需字节数*/
        DWORD    biWidth;           /* 以像素为单位说明图像的宽度*/
        DWORD    biHeight;          /* 以像素为单位说明图像的高速*/
        WORD     biPlanes;          /* 说明位面数，必须为1 */
        WORD     biBitCount;        /* 说明位数/像素，1、2、4、8、24 */
        DWORD    biCompression;     /* 说明图像是否压缩及压缩类型BI_RGB，BI_RLE8，BI_RLE4，BI_BITFIELDS */
        DWORD    biSizeImage;       /* 以字节为单位说明图像大小，必须是4的整数倍*/
        DWORD    biXPelsPerMeter;   /* 目标设备的水平分辨率，像素/米 */
        DWORD    biYPelsPerMeter;   /* 目标设备的垂直分辨率，像素/米 */
        DWORD    biClrUsed;         /* 说明图像实际用到的颜色数，如果为0则颜色数为2的biBitCount次方 */
        DWORD    biClrImportant;    /* 说明对图像显示有重要影响的颜色索引的数目，如果是0，表示都重要。*/
}BMPINFOHEADER_S;

/**< 调色板信息 */
typedef  struct  RGBQUAD_S {
       BYTE   rgbBlue;       /* 指定蓝色分量*/
       BYTE    rgbGreen;     /* 指定绿色分量*/
       BYTE    rgbRed;       /* 指定红色分量*/
       BYTE   rgbReserved;   /* 保留，指定为0*/
}RGBQUAD_S;

#pragma pack()

bool ReadBMPHeader(FILE *fpBMP, BMPHEADER_S *psBMPHeader);
bool ReadBMPInfoHeader(FILE *fpBMP, BMPINFOHEADER_S *psBMPInfoHeader);
unsigned long GetBMPPixSize( BMPINFOHEADER_S  sBMPInfoHeader);
bool ReadRGBFromBMP(FILE *fpBMP, BMPHEADER_S sBMPHeader, BMPINFOHEADER_S sBMPInfoHeader , unsigned char *pucRGBRead);

#endif // _BMP_H
