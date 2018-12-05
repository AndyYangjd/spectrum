#ifndef SPEC_H
#define SPEC_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <iostream>

namespace spec
{
    using namespace std;
    class Spec;
} // namespace spec end

namespace spec
{

class Spec
{
private:
    string fileName;
    string path ="/home/andy/Desktop/";
    string fileAdd;
    bool   loadStatus;
    cv::Mat srcFile;
    cv::Size2i sizeSrc, sizeDft;
    cv::Mat dftFile;
    vector<cv::Mat> ReIm;
    cv::Mat amp, pha;

    const string AMP ="the amp of ";
    const string PHA ="the pha of ";
    const string SRC ="the gray of ";

    // functions for initializing(default constration)
    inline void loadImg(const string _filename);     // #1
    inline void getSize(void);                                  // #2

    // functions for DFT and IDFT
    inline void expadSize(void);                     // #3
    inline void convtF(void);                           // #4
    inline void copyExpad(void);                    // #5
    inline cv::Mat centralize(cv::Mat _src);     // #6
    inline void execDft(void);                          // #7
    inline void getReIm(void);                         // #8
    inline void getAmpPha(void);                    // #9

    inline cv::Mat scale(cv::Mat _src);         // #10
    inline cv::Mat calib8U(cv::Mat _src);      // #11

public:
    Spec();
    Spec(const string tmp);                   // #1
    ~Spec() {;}

    void empty(void);                            // #2

    cv::Size2i getSizeSrc(void);            // #3
    void showSizeSrc(void);                 // #4
    cv::Size2i getSizeDft(void);            // #5
    void showSizeDft(void);                 // #6

    cv::Mat getAmp  (void);                   // #7
    cv::Mat getPha   (void);                   // #8

    void saveAmp    (void);                    // #9
    void savePha     (void);                    // #10

    cv::Mat getSrcFile(void);                      // #11
    void saveSrcFile(void);                    // #12

};

// #1
inline void Spec::loadImg(const string  _filename)
{
    fileName = _filename;
    fileAdd = path+fileName;
    cout << "The file address is: " << fileAdd << endl;
    srcFile =cv::imread(fileAdd, 0);
    if( srcFile.empty() )
    {
        cout << "Load " << fileAdd << " fail." << endl;
        loadStatus = false;
    }
    else {
        cout << "Load " << fileAdd << " right." << endl;
        loadStatus = true;
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
    srcFile.convertTo(dftFile, CV_32F, 1, 0);
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
inline cv::Mat Spec::centralize(cv::Mat _src)
{
    for(int i=0; i<_src.rows; i++)
        for(int j=0; j<_src.cols; j++)
        {
            if( (i + j)%2 != 0)
                _src.at<uchar>(i, j) = - _src.at<uchar>(i, j);
        }
    return _src;
}

// #7
inline void Spec::execDft(void)
{
    cv::dft(dftFile, dftFile, cv::DFT_COMPLEX_OUTPUT, sizeSrc.height);
}

// #8
inline void Spec::getReIm(void)
{
    cv::split(dftFile, ReIm);
}

// #9
inline void Spec::getAmpPha(void)
{
    cv::cartToPolar(ReIm[0], ReIm[1], amp, pha);
}

//  #10 Scale the image using log(amp+1)
inline cv::Mat Spec::scale(cv::Mat _src)
{
    _src +=cv::Scalar::all(1);
    cv::log( _src, _src );
    return _src;
}

// #11
inline cv::Mat Spec::calib8U(cv::Mat _src)
{
    cv::normalize( _src, _src, 0, 1, cv::NORM_MINMAX );
    _src.convertTo(_src, CV_8U, 255, 0);
    return _src;
}

}  // namespace spec end
#endif // SPEC_H
