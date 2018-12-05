#ifndef MYSPACE_H
#define MYSPACE_H

#include <opencv2/opencv.hpp>

namespace myspace
{

// #1
cv::Mat scale(cv::Mat _src)
{
    _src +=cv::Scalar::all(1);
    cv::log( _src, _src );
    return _src;
}

// #2
cv::Mat calib8U(cv::Mat _src)
{
    cv::normalize( _src, _src, 0, 1, cv::NORM_MINMAX );
    _src.convertTo(_src, CV_8U, 255, 0);
    return _src;
}

}
#endif // MYSPACE_H
