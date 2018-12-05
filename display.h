#ifndef DISPLAY_H
#define DISPLAY_H
#include <opencv2/opencv.hpp>

namespace myspace
{

class Display
{
public:
    Display();        // #1
    ~Display() {;}

protected:
    cv::Mat scale(cv::Mat _src);           // #2
    cv::Mat calib8U(cv::Mat _src);       // #3
    cv::Mat centralize(cv::Mat _src);   // #4
};

}
#endif // DISPLAY_H
