#include "sample_rgb24Toyuv.h"

int main(int argc , char **argv)
{
    YUV_E eYUV = YUV420 ;
    bool ret = RGB24_SaveYUVFile(eYUV , argv[1]);
    return 0;
}
