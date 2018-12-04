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
    bool loadStatus;
    cv::Mat srcFile;
    cv::Size2i sizeSrc, sizeDft;
    cv::Mat dftFile;
    vector<cv::Mat> ReIm;
    vector<cv::Mat> AmpPha;
    const cv::Rect2i srcRect=(0, 0, sizeSrc.width, sizeSrc.height);

    const string AMP ="the amplitude of ";
    const string PHA ="the phase of ";
    const string AMPNORM ="the amplitude after cen and norm of ";
    const string PHANORM ="the phase after cen and norm of ";
    const string AMPRC ="the recreated image using amp of ";
    const string PHARC ="the recreated image using pha of ";

    // functions for initializing(default constration)
    inline void loadImg(const string _filename);     // #1
    inline void getSize(void);                          // #2

    // functions for DFT and IDFT
    inline void expadSize(void);                     // #3
    inline void convtF(void);                           // #4
    inline void copyExpad(void);                    // #5
    inline void centralize(void);                       // #6
    inline void execDft(void);                          // #7
    inline void getReIm(void);                         // #8
    inline void getAmpPha(void);                    // #9

    inline cv::Mat specScale(cv::Mat _src);
    inline cv::Mat specNorm(cv::Mat _src);

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

    void saveRcUseAmp(void);
    void saveRcUsePha(void);

    void closeAllwindows(char tmp);

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
inline void Spec::centralize(void)
{
    for(int i=0; i<dftFile.width; i++)
        for(int j=0; j<dftFile.height; j++)
        {
            if( (i + j)%2 != 0)
                dftFile.at<uchar>(i, j) = dftFile.at<uchar>(i, j);
        }
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
    cv::cartToPolar(ReIm[0], ReIm[1], AmpPha[0], AmpPha[1]);
}

// only use for amplitude 1+log(amp)
inline cv::Mat Spec::specScale(cv::Mat _src)
{
    cv::log( _src, _src );
    _src +=cv::Scalar::all(1);
    return _src;
}

inline cv::Mat Spec::specNorm(cv::Mat _src)
{
    cv::normalize( _src, _src, 0, 1, cv::NORM_MINMAX );
    _src.convertTo(_src, CV_8UC1, 255, 0);
    return _src;
}

}  // namespace spec end
#endif // SPEC_H
