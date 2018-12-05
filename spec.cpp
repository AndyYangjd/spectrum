#include "spec.h"

namespace myspace
{

Spec::Spec():
    Display()
{
    std::cout << "The Spec Class now can't support default construction." << std::endl;
    fileName ="/0";
}

// #1
Spec::Spec(const std::string tmp)
{
    fileName = tmp;

    loadImg(fileName);
    getSize();

    expadSize();
    convtF();
    copyExpad();
    dftFile =centralize(dftFile);
    execDft();
    getReIm();
    getAmpPha();
}

// #2
cv::Size2i Spec::getSizeSrc(void)
{
    return sizeSrc;
}

// #3
void Spec::showSizeSrc(void)
{
    std::cout << "The " << fileName  <<" Size is: " << sizeSrc << std::endl;
}

// #4
cv::Size2i Spec::getSizeDft(void)
{
    return sizeDft;
}

// #5
void Spec::showSizeDft(void)
{
    std::cout << "The " <<fileName << " DFT Size is: " << sizeDft << std::endl;
}

// #6
cv::Mat Spec::getAmp(void)
{
    return amp;
}

// #7
cv::Mat Spec::getPha(void)
{
    return pha;
}

// #8
void Spec::saveAmp(void)
{
    cv::Mat tmp;
    tmp =amp( cv::Rect(0, 0, sizeSrc.width, sizeSrc.height) );
    tmp =scale(tmp);
    tmp =calib8U(tmp);
    cv::imwrite( AMP+fileName, tmp );
}

// #9
void Spec::savePha(void)
{
    cv::Mat tmp;
    tmp =pha( cv::Rect(0, 0, sizeSrc.width, sizeSrc.height) );
    tmp =scale(tmp);
    tmp =calib8U(tmp);
    cv::imwrite( PHA+fileName, tmp );
}

// #10
cv::Mat Spec::getSrcFile(void)
{
    return srcFile;
}

// #11
void Spec::saveSrcFile(void)
{
    cv::imwrite( SRC+fileName, srcFile );
}

} // namespace myspace end
