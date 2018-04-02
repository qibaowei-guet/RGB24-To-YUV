
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
    unsigned char y, u, v; /**< 一个像素点对应的YUV分量 */
    unsigned char *pucY, *pucU, *pucV; /**< Y、U、V数组对应的指针 */
    unsigned char r, g, b; /**< 一个像素点对应的RGB分类 */
    unsigned char *pucRGB; /**< RGB24对应的指针 */

	int iY = 0 ;
	int iX = 0 ;
    //存储空间大小 Y : width*height ; U : width/2 * height/2 ; V : width/2 * height/2
	pucY = pucYUVBuffer;
	pucU = pucYUVBuffer + width*height; /**< U数组在YUV数组的偏移量 */
	pucV = pucU + (width*height*1/4);   /**< V数组在YUV数组的偏移量 */

	for (iY = 0; iY < height;iY++){
		pucRGB = pucRGBBuffer + width*iY*3 ;

		for ( iX = 0;iX < width ; iX++){
            /**< 读取像素点的RGB分量 */
			r = *(pucRGB++);
			g = *(pucRGB++);
			b = *(pucRGB++);
            /**< 通过公式将RGB转换成为YUV */
			y = (unsigned char)( ( 66 * r + 129 * g +  25 * b + 128) >> 8) + 16  ;
			u = (unsigned char)( ( -38 * r -  74 * g + 112 * b + 128) >> 8) + 128 ;
			v = (unsigned char)( ( 112 * r -  94 * g -  18 * b + 128) >> 8) + 128 ;
            /**< Y分量直接写入Y数组 */
			*(pucY++) = clip_value(y,0,255);

			// 采样: 水平一半，垂直一半，实验证明这两种方式都可以
			if ( iY%2==0 && iX%2 == 0){
                /**< 偶数行偶数列时将U分量写入U数组，即一个4*4方块的左上角 */
                /*
                 *     0   1   2   3
                 *   ————————————————————
                 *0  | U |   | U |   |
                 *   -------------------
                 *1  |   |   |   |   |
                 *   ————————————————————
                 */

				*(pucU++) = clip_value(u,0,255);
			}
			else{ /**< else表示奇数行的情况 */
                /**<  奇数行偶数列时将U分量写入U数组，即一个4*4方块的左下角*/
                 /*
                 *     0   1   2   3
                 *   ————————————————————
                 *0  |   |   |   |   |
                 *   -------------------
                 *1  | V |   | V |   |
                 *   ————————————————————
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

			// 采样: 偶数采集U、奇数采集V
			if ( iX%2 == 0){
				*(pucU++) = clip_value(u,0,255);				
			}else{
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

// 可以用函数指针的方式来决定调用哪一个储存
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
     * step 1 : 读取BMP文件头信息
     */
    ret = ReadBMPHeader(fpBMP, &sBMPheader);
    if( ret == FALSE ){
        printf("[%s:%d]:ReadBMPHeader error,is not a bmp file!\n",__FILE__, __LINE__);
        return FALSE ;
    }

    // 读取info信息成功后保存在结构体中，并得到像素点个数
    ReadBMPInfoHeader(fpBMP, &sBMPInfoheader);
    BMPPixSize =  GetBMPPixSize(sBMPInfoheader);
    sprintf(yuvSize,"%dx%d.yuv",sBMPInfoheader.biWidth,sBMPInfoheader.biHeight);

    switch(eYUV){
    case YUV444:
            yuvMemorysize = YUV444MEMORY_SIZE(BMPPixSize);
            strcpy(yuvFilename,"out_yuv444_");
            fp_RGB24ToYUV = RGB24_TO_YUV444 ; //回调函数
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
     * step 2 : 分配RGB和YUV内存空间，获取BMP文件的RGB数据,存放在内存中
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
     * step 3 : RGB转换成为YUV格式，写入YUV文件
     */
    ret = fp_RGB24ToYUV(pucRGBRead,sBMPInfoheader.biWidth,sBMPInfoheader.biHeight,pusYUV);
    if( ret == FALSE ){
        printf("[%s:%d]:RGB2YUV411_10BIT_CPLUSPLUS data error !\n",__func__, __LINE__);
        return FALSE ;
    }
    fwrite(pusYUV,1,yuvMemorysize,fpYUV);

    /*
     * step 4 : 释放内存，关闭文件
     */
    free(pusYUV);
    free(pucRGBRead);
    fclose(fpYUV);
    fclose(fpBMP);
    ret = TRUE ;
    return ret ;
}
