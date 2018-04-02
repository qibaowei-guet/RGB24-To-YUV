
#include "sample_rgb24Toyuv.h"
#include "bmp.h"

/**
 * Split Y, U, V planes in YUV420P file.
 * @param url  Location of Input YUV file.
 * @param width    widthidth of Input YUV file.
 * @param height    Height of Input YUV file.
 * @param num  Number of frames to process.
 *
 */
int sample_yuv420_split(const char *url, int width, int height,int num)
{
    int i = 0 ;
	FILE *fp=fopen(url,"rb+");
	FILE *fp1=fopen("output_420_y.y","wb+");
	FILE *fp2=fopen("output_420_u.y","wb+");
	FILE *fp3=fopen("output_420_v.y","wb+");

	unsigned char *pic=(unsigned char *)malloc(width*height*3/2);

	for(i=0;i<num;i++){

		fread(pic,1,width*height*3/2,fp);
		//Y
		fwrite(pic,1,width*height,fp1);
		//U
		fwrite(pic+width*height,1,width*height/4,fp2);
		//V
		fwrite(pic+width*height*5/4,1,width*height/4,fp3);
	}

	free(pic);
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	return 0;
}

unsigned char clip_value(unsigned char x,unsigned char min_val,unsigned char  max_val){
	if(x>max_val){
		return max_val;
	}else if(x<min_val){
		return min_val;
	}else{
		return x;
	}
}

//RGB to YUV420
int RGB24_TO_YUV420(unsigned char *pucRGBBuffer,int width,int height,unsigned char *pucYUVBuffer)
{
    unsigned char y, u, v; /**< һ�����ص��Ӧ��YUV���� */
    unsigned char *pucY, *pucU, *pucV; /**< Y��U��V�����Ӧ��ָ�� */
    unsigned char r, g, b; /**< һ�����ص��Ӧ��RGB���� */
    unsigned char *pucRGB; /**< RGB24��Ӧ��ָ�� */

	int iY = 0 ;
	int iX = 0 ;
    //�洢�ռ��С Y : width*height ; U : width/2 * height/2 ; V : width/2 * height/2
	pucY = pucYUVBuffer;
	pucU = pucYUVBuffer + width*height; /**< U������YUV�����ƫ���� */
	pucV = pucU + (width*height*1/4);   /**< V������YUV�����ƫ���� */

	for (iY = 0; iY < height;iY++){
		pucRGB = pucRGBBuffer + width*iY*3 ;

		for ( iX = 0;iX < width ; iX++){
            /**< ��ȡ���ص��RGB���� */
			r = *(pucRGB++);
			g = *(pucRGB++);
			b = *(pucRGB++);
            /**< ͨ����ʽ��RGBת����ΪYUV */
			y = (unsigned char)( ( 66 * r + 129 * g +  25 * b + 128) >> 8) + 16  ;
			u = (unsigned char)( ( -38 * r -  74 * g + 112 * b + 128) >> 8) + 128 ;
			v = (unsigned char)( ( 112 * r -  94 * g -  18 * b + 128) >> 8) + 128 ;
            /**< Y����ֱ��д��Y���� */
			*(pucY++) = clip_value(y,0,255);

			// ����: ˮƽһ�룬��ֱһ�룬ʵ��֤�������ַ�ʽ������
			if ( iY%2==0 && iX%2 == 0){
                /**< ż����ż����ʱ��U����д��U���飬��һ��4*4��������Ͻ� */
                /*
                 *     0   1   2   3
                 *   ����������������������������������������
                 *0  | U |   | U |   |
                 *   -------------------
                 *1  |   |   |   |   |
                 *   ����������������������������������������
                 */

				*(pucU++) = clip_value(u,0,255);
			}
			else{ /**< else��ʾ�����е���� */
                /**<  ������ż����ʱ��U����д��U���飬��һ��4*4��������½�*/
                 /*
                 *     0   1   2   3
                 *   ����������������������������������������
                 *0  |   |   |   |   |
                 *   -------------------
                 *1  | V |   | V |   |
                 *   ����������������������������������������
                 */
				if ( iX%2 == 0 ){
                    *(pucV++) = clip_value(v,0,255);
				}
			}
		}
	}
	return 1;
}

//RGB to YUV422
int RGB24_TO_YUV422(unsigned char *pucRGBBuffer,int width,int height,unsigned char *pucYUVBuffer)
{
    unsigned char y, u, v;
    unsigned char *pucY, *pucU, *pucV;
    unsigned char r, g, b;
    unsigned char *pucRGB;

	int iY = 0 ;
	int iX = 0 ;
	//int pos = 0 ;
    // Y : width*height ; U : width/2 * height/2 ; V : width/2 * height/2
	pucY = pucYUVBuffer;
	pucU = pucYUVBuffer + YUV422MEMORY_U_OFFSET(width*height);
	pucV = pucYUVBuffer + YUV422MEMORY_V_OFFSET(width*height);

	for (iY = 0; iY < height;iY++){
		pucRGB = pucRGBBuffer + width*iY*3 ;

		for ( iX = 0;iX < width ; iX++){
			//pos = width*iX+iY;
			r = *(pucRGB++);
			g = *(pucRGB++);
			b = *(pucRGB++);

			y = (unsigned char)( ( 66 * r + 129 * g +  25 * b + 128) >> 8) + 16  ;
			u = (unsigned char)( ( -38 * r -  74 * g + 112 * b + 128) >> 8) + 128 ;
			v = (unsigned char)( ( 112 * r -  94 * g -  18 * b + 128) >> 8) + 128 ;

			*(pucY++) = clip_value(y,0,255);

			// ����: ÿ��2�Ͳ�һ��U��V
			if ( iX%2 == 0){
				*(pucU++) = clip_value(u,0,255);
				*(pucV++) = clip_value(v,0,255);
			}
		}
	}
	return 1;
}

//RGB to YUV444
int RGB24_TO_YUV444(unsigned char *pucRGBBuffer,int width,int height,unsigned char *pucYUVBuffer)
{
    unsigned char y, u, v;
    unsigned char *pucY, *pucU, *pucV;
    unsigned char r, g, b;
    unsigned char *pucRGB;

	int iY = 0 ;
	int iX = 0 ;
	pucY = pucYUVBuffer;
	pucU = pucYUVBuffer + YUV444MEMORY_U_OFFSET(width*height);
	pucV = pucYUVBuffer + YUV444MEMORY_V_OFFSET(width*height);

	for (iY = 0; iY < height;iY++){
		pucRGB = pucRGBBuffer + width*iY*3 ;

		for ( iX = 0;iX < width ; iX++){
			r = *(pucRGB++);
			g = *(pucRGB++);
			b = *(pucRGB++);

			y = (unsigned char)( ( 66 * r + 129 * g +  25 * b + 128) >> 8) + 16  ;
			u = (unsigned char)( ( -38 * r -  74 * g + 112 * b + 128) >> 8) + 128 ;
			v = (unsigned char)( ( 112 * r -  94 * g -  18 * b + 128) >> 8) + 128 ;

			*(pucY++) = clip_value(y,0,255);
			*(pucU++) = clip_value(u,0,255);
			*(pucV++) = clip_value(v,0,255);
		}
	}
	return 1;
}

// �����ú���ָ��ķ�ʽ������������һ������
bool RGB24_SaveYUVFile(YUV_E eYUV , const char *bmpUrl)
{
    bool ret = FALSE ;

    BMPHEADER_S sBMPheader;
    BMPINFOHEADER_S sBMPInfoheader;
    unsigned int BMPPixSize = 0 ;
    unsigned long yuvMemorysize = 0 ;

    unsigned char *pucRGBRead ;
    unsigned char *pusYUV;

    char yuvFilename[30] = {0};
    char yuvSize[15] = {0};
    FP_RGB24ToYUVFormat fp_RGB24ToYUV ;

    FILE* fpBMP = fopen(bmpUrl,"rb");
    FILE* fpYUV;

    if ( NULL == fpBMP ){
        printf("[%s:%d]: RGB24_SaveYUVFile check bmpUrl error\n",__FILE__, __LINE__);
        return ret ;
    }

    /*
     * step 1 : ��ȡBMP�ļ�ͷ��Ϣ
     */
    ret = ReadBMPHeader(fpBMP, &sBMPheader);
    if( ret == FALSE ){
        printf("[%s:%d]:ReadBMPHeader error,is not a bmp file!\n",__FILE__, __LINE__);
        return FALSE ;
    }

    // ��ȡinfo��Ϣ�ɹ��󱣴��ڽṹ���У����õ����ص����
    ReadBMPInfoHeader(fpBMP, &sBMPInfoheader);
    BMPPixSize =  GetBMPPixSize(sBMPInfoheader);
    sprintf(yuvSize,"%dx%d.yuv",sBMPInfoheader.biWidth,sBMPInfoheader.biHeight);

    switch(eYUV){
    case YUV444:
            yuvMemorysize = YUV444MEMORY_SIZE(BMPPixSize);
            strcpy(yuvFilename,"out_yuv444_");
            fp_RGB24ToYUV = RGB24_TO_YUV444 ; //�ص�����
            break;
    case YUV422:
            yuvMemorysize = YUV422MEMORY_SIZE(BMPPixSize);
            strcpy(yuvFilename,"out_yuv422_");
            fp_RGB24ToYUV = RGB24_TO_YUV422 ;
            break;
    case YUV420:
            yuvMemorysize = YUV420MEMORY_SIZE(BMPPixSize);
            strcpy(yuvFilename,"out_yuv420_");
            fp_RGB24ToYUV = RGB24_TO_YUV420 ;
            break;
    default:
        break;
    }
    strcat(yuvFilename,yuvSize);

    fpYUV = fopen(yuvFilename,"wb");
    if ( NULL == fpYUV ){
        printf("[%s:%d]: open yuvFilenameerror\n",__FILE__, __LINE__);
        return ret ;
    }

     /*
     * step 2 : ����RGB��YUV�ڴ�ռ䣬��ȡBMP�ļ���RGB����,������ڴ���
     */
    pucRGBRead = (unsigned char*)malloc(BMPPixSize*3);
    pusYUV     = (unsigned char*)malloc(yuvMemorysize);

    if  (  (NULL == pucRGBRead) || (NULL == pusYUV)){
        printf("[%s:%d]:malloc pusYUV error !\n",__func__, __LINE__);
        return FALSE ;
    }
    memset(pucRGBRead,0,BMPPixSize*3);
    memset(pusYUV,0,yuvMemorysize);

    ret = ReadRGBFromBMP(fpBMP,  sBMPheader,  sBMPInfoheader , pucRGBRead);
    if( ret == FALSE ){
        printf("[%s:%d]:ReadRGBFromBMP data error !\n",__func__, __LINE__);
        return FALSE ;
    }

    /*
     * step 3 : RGBת����ΪYUV��ʽ��д��YUV�ļ�
     */
    ret = fp_RGB24ToYUV(pucRGBRead,sBMPInfoheader.biWidth,sBMPInfoheader.biHeight,pusYUV);
    if( ret == FALSE ){
        printf("[%s:%d]:RGB2YUV411_10BIT_CPLUSPLUS data error !\n",__func__, __LINE__);
        return FALSE ;
    }
    fwrite(pusYUV,1,yuvMemorysize,fpYUV);

    /*
     * step 4 : �ͷ��ڴ棬�ر��ļ�
     */
    free(pusYUV);
    free(pucRGBRead);
    fclose(fpYUV);
    fclose(fpBMP);
    ret = TRUE ;
    return ret ;
}
