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
    cv::Mat output;

    inline cv::Mat crtReIm(cv::Mat _amp, cv::Mat _pha);
    inline void getRe(cv::Mat & _src);

public:
    ApplyFilter(cv::Mat _src, cv::Mat _filter, cv::Size2i size);
    ApplyFilter(cv::Mat _amp1, cv::Mat _pha,
                cv::Mat _amp2, cv::Mat _pha2,
                cv::Size2i size);
    ~ApplyFilter() {;}
    void showOutput(void);
    void saveOutput(void);
};

}


namespace myspace
{

inline cv::Mat ApplyFilter::crtReIm(cv::Mat _amp, cv::Mat _pha)
{
    cv::Mat re,im;
    cv::polarToCart(_amp, _pha, re, im);
    cv::Mat planes[2] ={re, im};
    cv::Mat rc;
    cv::merge(planes, 2, rc);
    return rc;
}

inline void ApplyFilter::getRe(cv::Mat & _src)
{
    using namespace std;
    cv::Mat planes[2];
    cv::split(_src, planes);
    output = planes[0].clone();
}

}
#endif // APPLYFILTER_H
