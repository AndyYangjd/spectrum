#include "spec.h"

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
    expanSize();
}

void Spec::empty(void)
{
    if(loadStatus == false)
        cout << "Load " << fileAdd << " fail ." << endl
             << "Your must choose a photo in "<< path << endl;
    else if(loadStatus == true)
        cout << "Load " << fileAdd << " right." << endl
             << "The " << fileName << " is in " << path << endl;
    else
        cout << "empty judgement error";
}

cv::Size2i Spec::getSizeSrc(void)
{
    return sizeSrc;
}

void Spec::showSizeSrc(void)
{
    cout << "The " << fileName  <<" Size is:  " << sizeSrc << endl;
}

cv::Size2i Spec::getSizeDft(void)
{
    return sizeDft;
}

void Spec::showSizeDft(void)
{
    cout << "The " <<fileName << " DFT Size is:  " << sizeDft << endl;
}

cv::Mat Spec::getAmp(const enum normStatus flag)
{
    if( flag == normNo )
    {
        return amp;
    }
    else if( flag == normYes )
    {
        ampNorm =specScale(amp);
        ampNorm =specNorm(ampNorm);
        return ampNorm;
    }
    else
        cout <<  fileName << " getAmp normStatus error" << endl;
}

void Spec::showAmp(const enum normStatus flag)
{
    if( flag == normNo )
    {
        cv::imwrite( AMP+fileName, amp );
        imshow( AMP+fileName, amp );
        cv::waitKey(0);
    }
    else if( flag == normYes )
    {
        ampNorm =specScale(amp);
        ampNorm =specNorm(amp);

        cv::imwrite( AMPNORM+fileName, ampNorm );
        imshow( AMPNORM+fileName, ampNorm );
        cv::waitKey(0)
    }
    else
        cout << fileName << " showAmp normStatus error" << endl;
}

cv::Mat Spec::getPha(const enum normStatus flag)
{
    if( flag == normNo )
    {
        return pha;
    }
    else if( flag == normYes )
    {
        phaNorm =specScale(pha);
        phaNorm =specNorm(pha);
        return phaNorm;
    }
    else
        cout << fileName << " getPha normStatus error" << endl;
}

void Spec::showPha(const enum normStatus flag)
{
    if( flag == normNo )
    {
        cv::imwrite( PHA+fileName, pha );
        imshow( PHA+fileName, pha );
        cv::waitKey(0);
    }
    else if( flag == normYes )
    {
        phaNorm =specScale(pha);
        phaNorm =specNorm(pha);

        cv::imwrite( PHANORM+fileName, phaNorm );
        imshow( PHANORM+fileName, phaNorm );
        cv::waitKey(0)
    }
    else
        cout << fileName << " showPha normStatus error" << endl;
}
