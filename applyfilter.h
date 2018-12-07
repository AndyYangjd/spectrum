#ifndef APPLYFILTER_H
#define APPLYFILTER_H

#include <opencv2/opencv.hpp>
#include "display.h"
#include <iostream>

namespace myspace
{

class ApplyFilter  : public myspace::Display
{
private:
    cv::Mat src, filter;
    cv::Mat amp, pha;
    cv::Mat output;

    inline void crtReIm(void);
    inline void getRe(void);

public:
    ApplyFilter(cv::Mat _src, cv::Mat _filter, cv::Size2i _size);
    ApplyFilter(cv::Mat _amp1, cv::Mat _pha,
                cv::Mat _amp2, cv::Mat _pha2,
                cv::Size2i _size);
    ~ApplyFilter() {;}
    void showOutput(void);
    void saveOutput(void);
};

}


namespace myspace
{

inline void ApplyFilter::crtReIm(void)
{
    cv::Mat re,im;
    cv::polarToCart(amp, pha, re, im);
    std::vector<cv::Mat> planes;
    planes.push_back( re.clone() );
    planes.push_back( im.clone() );
    cv::merge(planes, src);
}

inline void ApplyFilter::getRe(void)
{
    cv::Mat planes[2];
    cv::split(src, planes);
    output = planes[0].clone();
}

}
#endif // APPLYFILTER_H
