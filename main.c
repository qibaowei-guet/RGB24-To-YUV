#include "sample_rgb24Toyuv.h"

int main(int argc , char **argv)
{
    bool ret = -1;
    YUV_E eYUV  ;

    if ( argc != 3 ){
        printf("\nUsage:%s <xxx.bmp> <index>\n",argv[0]);
        printf("index:\n");
        printf("\t 0) RGB24 To YUV444.\n");
        printf("\t 1) RGB24 To YUV422.\n");
        printf("\t 2) RGB24 To YUV420.\n");
        printf("Example: %s xxx.bmp 2 \n",argv[0]);
        return ret ;
    }

    switch(atoi(argv[2]))
    {
    case 0 :
        eYUV = YUV444 ;
        break;
    case 1 :
        eYUV = YUV422 ;
        break;
    case 2 :
        eYUV = YUV420 ;
        break;
    default:
        eYUV = YUV420 ;
        break;
    }

    ret = RGB24_SaveYUVFile(eYUV , argv[1]);
    return ret;
}
