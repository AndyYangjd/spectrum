#ifndef SPEC_H
#define SPEC_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "display.h"

namespace myspace
{

class Spec : public myspace::Display
{
private:
    std::string fileName;
    std::string path ="/home/andy/Desktop/";
    std::string fileAdd;
    cv::Mat srcFile;
    cv::Size2i sizeSrc, sizeDft;
    cv::Mat dftFile;
    std::vector<cv::Mat> ReIm;
    cv::Mat amp, pha;

    const std::string AMP ="the amp of ";
    const std::string PHA ="the pha of ";
    const std::string SRC ="the gray of ";

    // functions for initializing(default constration)
    inline void loadImg(const std::string _filename);     // #1
    inline void getSize(void);                                  // #2

    // functions for DFT and IDFT
    inline void expadSize(void);                     // #3
    inline void convtF(void);                           // #4
    inline void copyExpad(void);                    // #5

    inline void execDft(void);                          // #6
    inline void getReIm(void);                         // #7
    inline void getAmpPha(void);                    // #8

public:
    Spec();
    Spec(const std::string tmp);                   // #1
    ~Spec() {;}

    cv::Size2i getSizeSrc(void);            // #2
    void showSizeSrc(void);                 // #3
    cv::Size2i getSizeDft(void);            // #4
    void showSizeDft(void);                 // #5

    cv::Mat getAmp  (void);                   // #6
    cv::Mat getPha   (void);                   // #7

    void saveAmp    (void);                    // #8
    void savePha     (void);                    // #9

    cv::Mat getSrcFile(void);                  // #10
    void saveSrcFile(void);                    // #11
};

}  // namespace myspace end


namespace myspace
{

// #1
inline void Spec::loadImg(const std::string  _filename)
{
    fileName = _filename;
    fileAdd = path+fileName;
    srcFile =cv::imread(fileAdd, 0);
    if( srcFile.empty() )
    {
        std::cout << "Load the input image Error." << std::endl;
    }
}

// #2
inline void Spec::getSize(void)
{
    sizeSrc.width = srcFile.cols;
    sizeSrc.height = srcFile.rows;
}

// #3
inline void Spec::expadSize(void)
{
    sizeDft.width =cv::getOptimalDFTSize(sizeSrc.width-1);
    sizeDft.height =cv::getOptimalDFTSize(sizeSrc.height-1);
}

// #4
inline void Spec::convtF(void)
{
    srcFile.convertTo(dftFile, CV_32F, 1, -mean(srcFile)[0]);
}

// #5
inline void Spec::copyExpad(void)
{
    cv::copyMakeBorder(dftFile, dftFile,
                       0, sizeDft.height - sizeSrc.height,
                       0, sizeDft.width - sizeSrc.width,
                       cv::BORDER_CONSTANT, cv::Scalar::all(0) );
}

// #6
inline void Spec::execDft(void)
{
    cv::dft(dftFile, dftFile, cv::DFT_COMPLEX_OUTPUT, sizeSrc.height);
}

// #7
inline void Spec::getReIm(void)
{
    cv::split(dftFile, ReIm);
}

// #8
inline void Spec::getAmpPha(void)
{
    cv::cartToPolar(ReIm[0], ReIm[1], amp, pha);
}

}  // namespace spec end

#endif // SPEC_H
