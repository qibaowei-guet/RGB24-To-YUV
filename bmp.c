
#include "bmp.h"

/** \brief
 *
 * \param  [in] fpBMP      : bmp文件指针
 * \param  [out]psBMPHeader: 读取后保存的bmp文件头信息
 * \return FALSE:不是BMP文件，TRUE:是BMP文件
 *
 */
bool ReadBMPHeader(FILE *fpBMP, BMPHEADER_S *psBMPHeader)
{
    bool  ret    = FALSE ;
    fseek(fpBMP, 0, SEEK_SET);  //fp指向文件头
    fread(psBMPHeader, sizeof(BMPHEADER_S), 1, fpBMP);
    if ( psBMPHeader->bfType == 0x4d42 ){
        printf("yes\n");
        ret = TRUE;
    }
    return ret;
}

/** \brief
 *
 * \param  [in] fpBMP      : bmp文件指针
 * \param  [out]psBMPHeader: 读取后保存的bmp文件头信息
 * \return FALSE:不是BMP文件，TRUE:是BMP文件
 *
 */
bool ReadBMPInfoHeader(FILE *fpBMP, BMPINFOHEADER_S *psBMPInfoHeader)
{
    bool  ret    = TRUE ;
    fseek(fpBMP, 0, SEEK_SET);  //fp指向文件头
    fseek(fpBMP, sizeof(BMPHEADER_S), 0);  //fp指向信息头
    fread(psBMPInfoHeader, sizeof(BMPINFOHEADER_S), 1, fpBMP);
    return ret;
}

/** \brief
 *
 * \param  [in]sBMPInfoHeader: BMP文件信息头
 * \return bmp图片文件中像素点个数
 *
 */
unsigned long GetBMPPixSize( BMPINFOHEADER_S  sBMPInfoHeader)
{
    return sBMPInfoHeader.biHeight*sBMPInfoHeader.biWidth;
}

/** \brief
 *
 * \param [in]fpBMP : bmp文件指针
 * \param [in]sBMPHeader: bmp文件头
 * \param [in]sBMPInfoHeader: bmp文件信息头
 * \param [out]pucRGBRead : 得到的RGB数组
 * \return FALSE:获取RGB数据出错，TRUE:获取RGB数据成功
 *
 */
bool ReadRGBFromBMP(FILE *fpBMP, BMPHEADER_S sBMPHeader, BMPINFOHEADER_S sBMPInfoHeader , unsigned char *pucRGBRead)
{
    bool ret = FALSE ;
    int iY = 0 ;
    int BMPLineSize  = sBMPInfoHeader.biWidth*3;
    int offsetRGB    = BMPLineSize;
    unsigned char *pucRGB = pucRGBRead;
    if ( (NULL == fpBMP) || (NULL == pucRGB) ){
        printf("[%s:%d]: fpBMP 、pucRGBRead error\n",__func__, __LINE__);
        return ret ;
    }

    // 注意这里读取的RGB数据，是Y轴镜像的，所以在读取的时候需要将其正向化。
    // 从文件尾一行一行的读取
    for ( iY = 0 ; iY < sBMPInfoHeader.biHeight ; iY++ ) {
        fseek(fpBMP, -offsetRGB, SEEK_END); // 参数2是偏移量大小,负数表示负向偏移，表示定位到离文件尾部offsetRGB
        fread(pucRGB,BMPLineSize,1,fpBMP);
        pucRGB    += BMPLineSize;
        offsetRGB += BMPLineSize;
    }
    ret = TRUE;
    return ret;
}
