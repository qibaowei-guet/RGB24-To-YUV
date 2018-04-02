
#ifndef _BMP_H
#define _BMP_H

#include "common.h"

#pragma pack(1)
/**< BMP�ļ�ͷ */
typedef  struct  BMPHEADER_S {
        WORD    bfType;            /* ˵���ļ������� */
        DWORD   bfSize;            /* ˵���ļ��Ĵ�С�����ֽ�Ϊ��λ*/
                                   /* ע��˴����ֽ�������*/
        WORD    bfReserved1;       /* ����������Ϊ0 */
        WORD    bfReserved2;       /* ����������Ϊ0 */
        DWORD   bfOffBits;         /* ˵����BMPHEADER_S�ṹ��ʼ��ʵ�ʵ�ͼ������֮����ֽ�ƫ���� */
}BMPHEADER_S;
/**< BMP�ļ���Ϣͷ */
typedef struct BMPINFOHEADER_S {
        DWORD    biSize;            /* ˵���ṹ�������ֽ���*/
        DWORD    biWidth;           /* ������Ϊ��λ˵��ͼ��Ŀ��*/
        DWORD    biHeight;          /* ������Ϊ��λ˵��ͼ��ĸ���*/
        WORD     biPlanes;          /* ˵��λ����������Ϊ1 */
        WORD     biBitCount;        /* ˵��λ��/���أ�1��2��4��8��24 */
        DWORD    biCompression;     /* ˵��ͼ���Ƿ�ѹ����ѹ������BI_RGB��BI_RLE8��BI_RLE4��BI_BITFIELDS */
        DWORD    biSizeImage;       /* ���ֽ�Ϊ��λ˵��ͼ���С��������4��������*/
        DWORD    biXPelsPerMeter;   /* Ŀ���豸��ˮƽ�ֱ��ʣ�����/�� */
        DWORD    biYPelsPerMeter;   /* Ŀ���豸�Ĵ�ֱ�ֱ��ʣ�����/�� */
        DWORD    biClrUsed;         /* ˵��ͼ��ʵ���õ�����ɫ�������Ϊ0����ɫ��Ϊ2��biBitCount�η� */
        DWORD    biClrImportant;    /* ˵����ͼ����ʾ����ҪӰ�����ɫ��������Ŀ�������0����ʾ����Ҫ��*/
}BMPINFOHEADER_S;

/**< ��ɫ����Ϣ */
typedef  struct  RGBQUAD_S {
       BYTE   rgbBlue;       /* ָ����ɫ����*/
       BYTE    rgbGreen;     /* ָ����ɫ����*/
       BYTE    rgbRed;       /* ָ����ɫ����*/
       BYTE   rgbReserved;   /* ������ָ��Ϊ0*/
}RGBQUAD_S;

#pragma pack()

bool ReadBMPHeader(FILE *fpBMP, BMPHEADER_S *psBMPHeader);
bool ReadBMPInfoHeader(FILE *fpBMP, BMPINFOHEADER_S *psBMPInfoHeader);
unsigned long GetBMPPixSize( BMPINFOHEADER_S  sBMPInfoHeader);
bool ReadRGBFromBMP(FILE *fpBMP, BMPHEADER_S sBMPHeader, BMPINFOHEADER_S sBMPInfoHeader , unsigned char *pucRGBRead);

#endif // _BMP_H
