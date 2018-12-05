#include "applyfilter.h"

namespace myspace
{

ApplyFilter::ApplyFilter(cv::Mat _src, cv::Mat _filter, cv::Size2i size)
{
    src =_src.clone();
    filter  =_filter.clone();

    cv::mulSpectrums(src, filter, src, 0, false);
    cv::idft(src, src, cv::DFT_SCALE, size.height);
    src =scale(src);
    src =src( cv::Rect(0, 0, size.width, size.height) );
    src
}

ApplyFilter::ApplyFilter(cv::Mat _amp1, cv::Mat _pha1, cv::Mat _amp2, cv::Mat _pha2, cv::Size2i size)
{
    src   =crtReIm(_amp1, _pha1);
    filter =crtReIm(_amp2, _pha2);
    src =scale(src);
    cv::mulSpectrums(src, filter, src, 0, false);
    cv::idft(src, src, cv::DFT_SCALE, size.height);
    src =src( cv::Rect(0, 0, size.width, size.height) );
}

}
