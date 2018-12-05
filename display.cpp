#include "display.h"

namespace myspace
{

// #1
Display::Display()
{
}

// #2
cv::Mat Display::scale(cv::Mat _src)
{
    _src +=cv::Scalar::all(1);
    cv::log( _src, _src );
    return _src;
}

// #3
cv::Mat Display::calib8U(cv::Mat _src)
{
    cv::normalize( _src, _src, 0, 1, cv::NORM_MINMAX );
    _src.convertTo(_src, CV_8U, 255, 0);
    return _src;
}

}  // namespace myspace end
