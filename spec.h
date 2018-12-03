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

    const bool CENYES =true;
    const bool CENNO   =false;

} // namespace spec end

namespace spec
{

class Spec
{
private:
    string fileName;                                  //file name
    string path ="/home/andy/Desktop/";  // file path
    string fileAdd;                                     // file address
    bool loadStatus;                                 // status for read image right or wrong
    cv::Size2i sizeSrc, sizeDft;                // the size for src and DFT
    cv::Mat srcFile, srcCenFile;               // the file for src and Centralized
    cv::Mat dftFile,  dftCenFile;                // the DFT file for src and Centralized
    vector<cv::Mat> planes, planesCen;
    cv::Mat re, im, rePart, imPart;
    cv::Mat amp, pha, ampNorm, phaNorm;
    cv::Mat reCen, imCen, rePartCen, imPartCen;
    cv::Mat ampCen, phaCen, ampNormCen, phaNormCen;

    const string AMP ="the amplitude of ";
    const string PHA ="the phase of ";
    const string AMPNORM ="the amplitude after cen and norm of ";
    const string PHANORM ="the phase after cen and norm of ";

    inline void loadImg(const string _filename);
    inline void getSize(void);
    inline void cenSpec(void);
    inline void convtF(void);
    inline void expanSize(void);
    inline void copyExpan(void);
    inline void getDft(void);
    inline void getReIm(void);
    inline void getAmpPha(void);
    // scale the measure, use log(1 + amp/pha)
    inline cv::Mat specScale(cv::Mat _src);
    inline cv::Mat specNorm(cv::Mat _src);

//    inline void getFileName(const string & _fileAdd);

public:
    Spec();
    Spec(const string tmp);
    ~Spec() {;}

    void empty(void);

    cv::Size2i getSizeSrc(void);
    void showSizeSrc(void);
    cv::Size2i getSizeDft(void);
    void showSizeDft(void);

    cv::Mat getAmp  (bool flag=false);     // flag judegement the Centralize or not
    cv::Mat getPha   (bool flag=false);

    void showAmp    (bool flag=false);
    void showPha     (bool flag=false);

    void closeAllwindows(char tmp);

};

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

inline void Spec::getSize(void)
{
    sizeSrc.width = srcFile.rows;
    sizeSrc.height = srcFile.cols;
}

// convert the srcFile centralize to srcCenFile
inline void Spec::cenSpec(void)
{
    srcCenFile = srcFile.clone();
    for(int i=0; i<sizeSrc.width; i++)
        for(int j=0; j<sizeSrc.height; j++)
        {
            if( (i + j)%2 != 0)
                srcCenFile.at<uchar>(i, j) = -srcCenFile.at<uchar>(i, j);
        }
}

inline void Spec::convtF(void)
{
    srcFile.convertTo(srcFile, CV_32F, 1, 0);
    srcCenFile.convertTo (srcCenFile, CV_32F, 1, 0);
}

inline void Spec::expanSize(void)
{
    sizeDft.width =cv::getOptimalDFTSize(sizeSrc.width-1);
    sizeDft.height =cv::getOptimalDFTSize(sizeSrc.height-1);
}

inline void Spec::copyExpan(void)
{
    cv::copyMakeBorder(srcFile, dftFile,
                                0, sizeDft.width - sizeSrc.width,
                                0, sizeDft.height - sizeSrc.height,
                               cv::BORDER_CONSTANT, cv::Scalar::all(0) );
    cv::copyMakeBorder(srcCenFile, dftCenFile,
                                0, sizeDft.width - sizeSrc.width,
                                0, sizeDft.height - sizeSrc.height,
                               cv::BORDER_CONSTANT, cv::Scalar::all(0) );
}

inline void Spec::getDft(void)
{
    cv::dft(dftFile, dftFile, cv::DFT_COMPLEX_OUTPUT, srcFile.rows );
    cv::dft(dftCenFile, dftCenFile, cv::DFT_COMPLEX_OUTPUT, srcCenFile.rows );
}

inline void Spec::getReIm(void)
{
    cv::split(dftFile, planes);
    if( planes.size() == 2)
    {
        re = *( planes.begin() );
        rePart = re( cv::Rect(0, 0, sizeSrc.height-1, sizeSrc.width-1) );
        im = *( planes.end()-1 );
        imPart = im( cv::Rect(0, 0, sizeSrc.height-1, sizeSrc.width-1) );
    }
    else
        cout << "Split error." << endl;

    cv::split(dftCenFile, planesCen);
    if( planesCen.size() == 2)
    {
        reCen = *( planesCen.begin() );
        rePartCen = reCen( cv::Rect(0, 0, sizeSrc.height-1, sizeSrc.width-1) );
        imCen = *( planesCen.end()-1 );
        imPartCen = imCen( cv::Rect(0, 0, sizeSrc.height-1, sizeSrc.width-1) );
    }
    else
        cout << "SplitCen error." << endl;
}

inline void Spec::getAmpPha(void)
{
    cv::cartToPolar(rePart, imPart, amp, pha);
    cv::cartToPolar(rePartCen, imPartCen, ampCen, phaCen);
}

inline cv::Mat Spec::specScale(cv::Mat _src)
{
    _src +=cv::Scalar::all(1);
    cv::log( _src, _src );
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
