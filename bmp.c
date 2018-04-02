
#include "bmp.h"

/** \brief
 *
 * \param  [in] fpBMP      : bmp�ļ�ָ��
 * \param  [out]psBMPHeader: ��ȡ�󱣴��bmp�ļ�ͷ��Ϣ
 * \return FALSE:����BMP�ļ���TRUE:��BMP�ļ�
 *
 */
bool ReadBMPHeader(FILE *fpBMP, BMPHEADER_S *psBMPHeader)
{
    bool  ret    = FALSE ;
    fseek(fpBMP, 0, SEEK_SET);  //fpָ���ļ�ͷ
    fread(psBMPHeader, sizeof(BMPHEADER_S), 1, fpBMP);
    if ( psBMPHeader->bfType == 0x4d42 ){
        printf("yes\n");
        ret = TRUE;
    }
    return ret;
}

/** \brief
 *
 * \param  [in] fpBMP      : bmp�ļ�ָ��
 * \param  [out]psBMPHeader: ��ȡ�󱣴��bmp�ļ�ͷ��Ϣ
 * \return FALSE:����BMP�ļ���TRUE:��BMP�ļ�
 *
 */
bool ReadBMPInfoHeader(FILE *fpBMP, BMPINFOHEADER_S *psBMPInfoHeader)
{
    bool  ret    = TRUE ;
    fseek(fpBMP, 0, SEEK_SET);  //fpָ���ļ�ͷ
    fseek(fpBMP, sizeof(BMPHEADER_S), 0);  //fpָ����Ϣͷ
    fread(psBMPInfoHeader, sizeof(BMPINFOHEADER_S), 1, fpBMP);
    return ret;
}

/** \brief
 *
 * \param  [in]sBMPInfoHeader: BMP�ļ���Ϣͷ
 * \return bmpͼƬ�ļ������ص����
 *
 */
unsigned long GetBMPPixSize( BMPINFOHEADER_S  sBMPInfoHeader)
{
    return sBMPInfoHeader.biHeight*sBMPInfoHeader.biWidth;
}

/** \brief
 *
 * \param [in]fpBMP : bmp�ļ�ָ��
 * \param [in]sBMPHeader: bmp�ļ�ͷ
 * \param [in]sBMPInfoHeader: bmp�ļ���Ϣͷ
 * \param [out]pucRGBRead : �õ���RGB����
 * \return FALSE:��ȡRGB���ݳ���TRUE:��ȡRGB���ݳɹ�
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
        printf("[%s:%d]: fpBMP ��pucRGBRead error\n",__func__, __LINE__);
        return ret ;
    }

    // ע�������ȡ��RGB���ݣ���Y�᾵��ģ������ڶ�ȡ��ʱ����Ҫ�������򻯡�
    // ���ļ�βһ��һ�еĶ�ȡ
    for ( iY = 0 ; iY < sBMPInfoHeader.biHeight ; iY++ ) {
        fseek(fpBMP, -offsetRGB, SEEK_END); // ����2��ƫ������С,������ʾ����ƫ�ƣ���ʾ��λ�����ļ�β��offsetRGB
        fread(pucRGB,BMPLineSize,1,fpBMP);
        pucRGB    += BMPLineSize;
        offsetRGB += BMPLineSize;
    }
    ret = TRUE;
    return ret;
}
