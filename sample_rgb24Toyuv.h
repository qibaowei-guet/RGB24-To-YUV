
#ifndef _SAMPLE_H
#define _SAMPLE_H

#include "common.h"

// PIX_SIZE ��ʾ����ͼƬ�����ش�С������һ�ŷֱ���Ϊ320*240��ͼƬ������(PIX_SIZE)=320*240
// ����ĺ��ʾ 3��YUV��ʽ ��ռ�õ��ڴ�ռ��С
#define YUV444MEMORY_SIZE(PIX_SIZE) ( (PIX_SIZE)*3 )
#define YUV422MEMORY_SIZE(PIX_SIZE) ( (PIX_SIZE)*2 )
#define YUV420MEMORY_SIZE(PIX_SIZE) ( (PIX_SIZE)*3/2 )

/**< ����ĺ��ǻ���planar��ʽ�� */
// yuv420�е�U������ʼ��ƫ����
#define YUV420MEMORY_U_OFFSET(PIX_SIZE) ( (PIX_SIZE) )
// yuv420�е�V������ʼ��ƫ����
#define YUV420MEMORY_V_OFFSET(PIX_SIZE) ( YUV420MEMORY_U_OFFSET(PIX_SIZE) + (PIX_SIZE)*1/4 )

// yuv422�е�U������ʼ��ƫ����
#define YUV422MEMORY_U_OFFSET(PIX_SIZE) ( (PIX_SIZE) )
// yuv422�е�V������ʼ��ƫ����
#define YUV422MEMORY_V_OFFSET(PIX_SIZE) ( YUV422MEMORY_U_OFFSET(PIX_SIZE) + (PIX_SIZE)*1/2 )

// yuv444�е�U������ʼ��ƫ����
#define YUV444MEMORY_U_OFFSET(PIX_SIZE) ( (PIX_SIZE) )
// yuv444�е�V������ʼ��ƫ����
#define YUV444MEMORY_V_OFFSET(PIX_SIZE) ( YUV444MEMORY_U_OFFSET(PIX_SIZE) + (PIX_SIZE) )


typedef enum YUV_E{
    YUV444 = 0 ,
    YUV422 ,
    YUV420
}YUV_E;

/**< RGB24ת��YUV��ʽ�ĺ���ָ�� */
typedef int (*FP_RGB24ToYUVFormat)(unsigned char *pucRGBBuffer,int width,int height,unsigned char *pucYUVBuffer);

int sample_yuv420_split(const char *url, int w, int h,int num);
int RGB24_TO_YUV444(unsigned char *pucRGBBuffer,int width,int height,unsigned char *pucYUVBuffer);
int RGB24_TO_YUV420(unsigned char *pucRGBBuffer,int width,int height,unsigned char *pucYUVBuffer);
int RGB24_TO_YUV422(unsigned char *pucRGBBuffer,int width,int height,unsigned char *pucYUVBuffer);

bool RGB24_SaveYUVFile(YUV_E eYUV , const char *bmpUrl);

#endif // _SAMPLE_H
