#include "spec.h"
namespace spec
{

Spec::Spec()
{
    cout << "The Spec Class now can't support default construction." << endl;
    fileName ="/0";
}

Spec::Spec(const string tmp)
{
    fileName = tmp;
    loadImg(fileName);
    getSize();
    cenSpec();
    convtF();
    expanSize();
    copyExpan();
    getDft();
    getReIm();
    getAmpPha();
}

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

cv::Size2i Spec::getSizeSrc(void)
{
    return sizeSrc;
}

void Spec::showSizeSrc(void)
{
    cout << "The " << fileName  <<" Size is: " << sizeSrc << endl;
}

cv::Size2i Spec::getSizeDft(void)
{
    return sizeDft;
}

void Spec::showSizeDft(void)
{
    cout << "The " <<fileName << " DFT Size is: " << sizeDft << endl;
}

cv::Mat Spec::getAmp(bool flag)
{
    cv::Mat m_err =srcFile-srcFile;
    if( flag == false )
    {
        return amp;
    }
    else if( flag == true )
    {
        return ampCen;
    }
    else
    {
        cout <<  fileName << " getAmp CENSTATUS error" << endl;
        return m_err;
    }
}

cv::Mat Spec::getPha(bool flag)
{
    cv::Mat m_err=srcFile-srcFile;
    if( flag == false )
    {
        return pha;
    }
    else if( flag == true )
    {
        return phaCen;
    }
    else
    {
        cout <<  fileName << " getPha CENSTATUS error" << endl;
        return m_err;
    }
}

void Spec::saveAmp(bool flag)
{
    if( flag == false )
    {
        ampNorm =specScale(amp);
        ampNorm =specNorm(ampNorm);

        cv::imwrite( AMP+fileName, ampNorm );
    }
    else if( flag == true )
    {
        ampNormCen =specScale(ampCen);
        ampNormCen =specNorm(ampNormCen);

        cv::imwrite( AMPNORM+fileName, ampNormCen );
    }
}

void Spec::savePha(bool flag)
{
    if( flag == false )
    {
        phaNorm =specNorm(pha);

        cv::imwrite( PHA+fileName, phaNorm );
    }
    else if( flag == true )
    {
        phaNormCen =specNorm(phaCen);

        cv::imwrite( PHANORM+fileName, phaNormCen );
    }
}

void Spec::closeAllwindows(char tmp)
{
    if( tmp == 'y' )
        cv::destroyAllWindows();
    else
        cout << "Not close all windows." << endl;
}

void Spec::saveRcUseAmp(void)
{

}

void Spec::saveRcUsePha(void)
{
    cv::Mat tmpAmp( sizeDft.width, sizeDft.height, CV_32F, cv::Scalar::all(1) );
    cv::polarToCart(tmpAmp, phaRc,re, im);
    re = planes[0];
    im = planes[1];
    if( planes.size() ==2 )
    {
        cv::merge(planes, dftFile);
        cv::idft(dftFile, dftFile, cv::DFT_SCALE, sizeDft.width);
        // dftFile type is CV32F_C2
        cv::split(dftFile, planes);
        srcRc =planes[0]( cv::Rect(0, 0, sizeSrc.height-1, sizeSrc.width-1) );
        srcRc =specNorm(srcRc);
        cv::imwrite(PHARC+fileName, srcRc);
    }
    else
        cout << "saveRcUsePha merge fail" << endl;
}

} // namespace spec end
