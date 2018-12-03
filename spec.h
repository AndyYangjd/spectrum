#ifndef SPEC_H
#define SPEC_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Spec
{
private:
    string fileName;
    string path ="/home/andy/Desktop/";
    string fileAdd;
    bool loadStatus;
    cv::Size2i sizeSrc, sizeDft;
    cv::Mat srcFile, dftFile;
    vector<cv::Mat> planes;
    cv::Mat re, im, rePart, imPart;
    cv::Mat amp, pha;
    cv::Mat ampNorm, phaNorm;

    const string AMP ="the amp of ";
    const string PHA ="the pha of ";
    const string AMPNORM ="the ampnorm of ";
    const string PHANORM ="the phanorm of ";

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

    bool NORMYES(void);
    bool NORMNO(void);

    cv::Mat getAmp(bool flag=false);
    void showAmp(bool flag=false);
    cv::Mat getPha(bool flag=false);
    void showPha(bool flag=false);

};

inline void Spec::loadImg(const string  _filename)
{
    fileName = _filename;
    fileAdd = path+fileName;
    cout << "The file address is:  " << fileAdd << endl;
    srcFile =cv::imread(fileAdd);
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

inline void Spec::cenSpec(void)
{
    for(int i=0; i<srcFile.rows; i++)
        for(int j=0; j<srcFile.cols; j++)
        {
            if( (i + j)%2 != 0)
                srcFile.at<uchar>(i, j) = -srcFile.at<uchar>(i, j);
        }
}

inline void Spec::convtF(void)
{
    srcFile.convertTo(srcFile, CV_32F, 1, 0);
}

inline void Spec::expanSize(void)
{
    sizeDft.width =cv::getOptimalDFTSize(sizeSrc.width);
    sizeDft.height =cv::getOptimalDFTSize(sizeSrc.height);
}

inline void Spec::copyExpan(void)
{
    cv::copyMakeBorder(srcFile, dftFile,
                                0, sizeDft.width - sizeSrc.width,
                                0, sizeDft.height - sizeSrc.height,
                               cv::BORDER_CONSTANT, cv::Scalar::all(0) );
}

inline void Spec::getDft(void)
{
    cv::dft(dftFile, dftFile, cv::DFT_COMPLEX_OUTPUT, srcFile.rows );
}

inline void Spec::getReIm(void)
{
    cv::split(dftFile, planes);
    if( planes.size() == 2)
    {
        re = *( planes.begin() );
        rePart = re( cv::Rect(0, 0, sizeSrc.height, size.width) );
        im = *( planes.end() );
        imPart = im( cv::Rect(0, 0, sizeSrc.height, size.width) );
    }
    else
        cout << "Split error." << endl;
}

inline void Spec::getAmpPha(void)
{
    cv::cartToPolar(rePart, imPart, amp, pha);
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

/*
inline void Spec::getFileName(const string & _fileAdd)
{
    vector<string> files;
    string path = "/home/andy/Desktop/";
    DIR* pDir;               // file dir stream
    struct dirent* ptr;

    if( !( pDir =opendir(path.c_str() )) )     // assign the pDir to path
        return;
    while( (ptr =readdir(pDir)) !=0 )


    dir =opendir( PATH.c_str() );      // get the dir handle
    while( ptr=readdir(dir) !=NULL )
    {
        if( ptr->d_name[0]=="." )
            continue;
        files.push_back( ptr->d_name );
    }
    for( int i=0; i< files.size(); ++i )
    {

    }
}
*/
#endif // SPEC_H
