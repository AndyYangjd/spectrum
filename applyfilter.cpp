#include "applyfilter.h"

namespace myspace
{

ApplyFilter::ApplyFilter(cv::Mat _src, cv::Mat _filter, cv::Size2i _size)
{
    src =_src.clone();
    filter  =_filter.clone();

    cv::mulSpectrums(src, filter, src, 0, false);
     // Because of M*N is two big for float and will normlize later, so flag set to 0
    cv::idft(src, src, 0, _size.height);
    getRe();
    output = centralize(output);
    output =output( cv::Rect(0, 0, _size.width, _size.height) );
    output =calib8U(output);
}

ApplyFilter::ApplyFilter(cv::Mat _amp1, cv::Mat _pha1, cv::Mat _amp2, cv::Mat _pha2, cv::Size2i _size)
{
    cv::multiply(_amp1, _amp2, amp);
    cv::add(_pha1, _pha2, pha);
    crtReIm();
    cv::idft(src, src, 0, _size.height);
    getRe();
    output = centralize(output);
    output =output( cv::Rect(0, 0, _size.width, _size.height) );
    output =calib8U(output);
}

void ApplyFilter::showOutput(void)
{
    cv::imshow("output", output);
    cv::waitKey(0);
}

void ApplyFilter::saveOutput(void)
{
    cv::imwrite("filter output.png", output);
}

}
