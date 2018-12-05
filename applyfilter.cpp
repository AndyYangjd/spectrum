#include "applyfilter.h"

namespace myspace
{

ApplyFilter::ApplyFilter(cv::Mat _src, cv::Mat _filter, cv::Size2i size)
{
    src =_src.clone();
    filter  =_filter.clone();

    cv::mulSpectrums(src, filter, src, 0, false);
    cv::idft(src, src, cv::DFT_SCALE, size.height);
    getRe(src);
    output = centralize(output);
    output =output( cv::Rect(0, 0, size.width, size.height) );
    output =calib8U(output);
}

ApplyFilter::ApplyFilter(cv::Mat _amp1, cv::Mat _pha1, cv::Mat _amp2, cv::Mat _pha2, cv::Size2i size)
{
    src   =crtReIm(_amp1, _pha1);
    filter =crtReIm(_amp2, _pha2);

    cv::mulSpectrums(src, filter, src, cv::DFT_COMPLEX_OUTPUT);
    cv::idft(src, src, cv::DFT_SCALE, size.height);
    getRe(src);
    output = centralize(output);
    output =output( cv::Rect(0, 0, size.width, size.height) );
    output =calib8U(output);
}

void ApplyFilter::showOutput(void)
{
    cv::namedWindow("Output");
    cv::imshow("Output", output);
    cv::waitKey(0);
}

void ApplyFilter::saveOutput(void)
{
    cv::imwrite("filter output.png", output);
}

}
