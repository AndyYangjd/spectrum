#include "display.h"

namespace myspace
{

// #1
Display::Display()
{
}

// #2
cv::Mat Display::scale(cv::Mat _src_)
{
    _src_.convertTo(_src_, CV_8U, 1, 1);
    cv::log( _src_, _src_ );
    return _src_;
}

// #3
cv::Mat Display::calib8U(cv::Mat _src)
{
    cv::normalize( _src, _src, 0, 1, cv::NORM_MINMAX );
    _src.convertTo(_src, CV_8U, 255, 0);
    return _src;
}

// #4
cv::Mat Display::centralize(cv::Mat _src)
{
    for(int i=0; i<_src.rows; i++)
            for(int j=0; j<_src.cols; j++)
            {
                if( (i + j)%2 != 0)
                    _src.at<float>(i, j) = - _src.at<float>(i, j);
            }
    return _src;
}
}  // namespace myspace end
