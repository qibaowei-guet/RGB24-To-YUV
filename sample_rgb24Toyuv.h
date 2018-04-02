
#ifndef _SAMPLE_H
#define _SAMPLE_H

#include "common.h"

// PIX_SIZE 表示的是图片的像素大小，例如一张分辨率为320*240的图片，它的(PIX_SIZE)=320*240
// 下面的宏表示 3种YUV格式 所占用的内存空间大小
#define YUV444MEMORY_SIZE(PIX_SIZE) ( (PIX_SIZE)*3 )
#define YUV422MEMORY_SIZE(PIX_SIZE) ( (PIX_SIZE)*2 )
#define YUV420MEMORY_SIZE(PIX_SIZE) ( (PIX_SIZE)*3/2 )

/**< 下面的宏是基于planar格式的 */
// yuv420中的U分量起始的偏移量
#define YUV420MEMORY_U_OFFSET(PIX_SIZE) ( (PIX_SIZE) )
// yuv420中的V分量起始的偏移量
#define YUV420MEMORY_V_OFFSET(PIX_SIZE) ( YUV420MEMORY_U_OFFSET(PIX_SIZE) + (PIX_SIZE)*1/4 )

// yuv422中的U分量起始的偏移量
#define YUV422MEMORY_U_OFFSET(PIX_SIZE) ( (PIX_SIZE) )
// yuv422中的V分量起始的偏移量
#define YUV422MEMORY_V_OFFSET(PIX_SIZE) ( YUV422MEMORY_U_OFFSET(PIX_SIZE) + (PIX_SIZE)*1/2 )

// yuv444中的U分量起始的偏移量
#define YUV444MEMORY_U_OFFSET(PIX_SIZE) ( (PIX_SIZE) )
// yuv444中的V分量起始的偏移量
#define YUV444MEMORY_V_OFFSET(PIX_SIZE) ( YUV444MEMORY_U_OFFSET(PIX_SIZE) + (PIX_SIZE) )


typedef enum YUV_E{
    YUV444 = 0 ,
    YUV422 ,
    YUV420
}YUV_E;

/**< RGB24转换YUV格式的函数指针 */
typedef int (*FP_RGB24ToYUVFormat)(unsigned char *pucRGBBuffer,int width,int height,unsigned char *pucYUVBuffer);

int sample_yuv420_split(const char *url, int w, int h,int num);
int RGB24_TO_YUV444(unsigned char *pucRGBBuffer,int width,int height,unsigned char *pucYUVBuffer);
int RGB24_TO_YUV420(unsigned char *pucRGBBuffer,int width,int height,unsigned char *pucYUVBuffer);
int RGB24_TO_YUV422(unsigned char *pucRGBBuffer,int width,int height,unsigned char *pucYUVBuffer);

bool RGB24_SaveYUVFile(YUV_E eYUV , const char *bmpUrl);

#endif // _SAMPLE_H
