#include "spec.h"
namespace spec
{

Spec::Spec()
{
    cout << "The Spec Class now can't support default construction." << endl;
    fileName ="/0";
}

// #1
Spec::Spec(const string tmp)
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
void Spec::empty(void)
{
    if(loadStatus == false)
        cout << "Load " << fileAdd << " fail ." << endl
             << "Your must choose a photo in "<< path << endl;
    else if(loadStatus == true)
        cout << "Load " << fileAdd << " right." << endl;
    else
        cout << "empty judgement error";
}

// #3
cv::Size2i Spec::getSizeSrc(void)
{
    return sizeSrc;
}

// #4
void Spec::showSizeSrc(void)
{
    cout << "The " << fileName  <<" Size is: " << sizeSrc << endl;
}

// #5
cv::Size2i Spec::getSizeDft(void)
{
    return sizeDft;
}

// #6
void Spec::showSizeDft(void)
{
    cout << "The " <<fileName << " DFT Size is: " << sizeDft << endl;
}

// #7
cv::Mat Spec::getAmp(void)
{
    return amp;
}

// #8
cv::Mat Spec::getPha(void)
{
    return pha;
}

// #9
void Spec::saveAmp(void)
{
    cv::Mat tmp;
    tmp =amp( cv::Rect(0, 0, sizeSrc.width, sizeSrc.height) );
    tmp =scale(tmp);
    tmp =calib8U(tmp);
    cv::imwrite( AMP+fileName, tmp );
}

// #10
void Spec::savePha(void)
{
    cv::Mat tmp;
    tmp =pha( cv::Rect(0, 0, sizeSrc.width, sizeSrc.height) );
    tmp =scale(tmp);
    tmp =calib8U(tmp);
    cv::imwrite( PHAcl+fileName, tmp );
}

// #11
cv::Mat Spec::getSrcFile(void)
{
    return srcFile;
}

// #12
void Spec::saveSrcFile(void)
{
    cv::imwrite( SRC+fileName, srcFile );
}
} // namespace spec end
