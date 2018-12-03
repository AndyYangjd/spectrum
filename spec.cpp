#include "spec.h"

Spec::Spec(const string tmp = "NULL")
{
    fileAdd = tmp;
    loadImg(fileAdd);
    getSize();
    expanSize();
}

void Spec::empty(void)
{
    if(loadStatus == false)
        cout << "Load " << fileAdd << " fail." << endl;
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
    cout << "The image's Size is:  " << sizeSrc << endl;
}

cv::Size2i Spec::getSizeDft(void)
{
    return sizeDft;
}

void Spec::showSizeDft(void)
{
    cout << "The DFT Size is:  " << sizeDft << endl;
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
        cout << "getAmp normStatus error" << endl;
}

void Spec::showAmp(const enum normStatus flag)
{
    if( flag == normNo )
    {
        cv::imwrite("the amp of src.png", amp);
        imshow("the amp of src", amp);
        cv::waitKey(0);
    }
    else if( flag == normYes )
    {
        ampNorm =specScale(amp);
        ampNorm =specNorm(amp);

        cv::imwrite("the ampNorm of src.png", ampNorm);
        imshow("the ampNorm of src", ampNorm);
        cv::waitKey(0)
    }
    else
        cout << "showAmp normStatus error" << endl;
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
        cout << "getPha normStatus error" << endl;
}

void Spec::showPha(const enum normStatus flag)
{
    if( flag == normNo )
    {
        cv::imwrite("the pha of src.png", pha);
        imshow("the pha of src", pha);
        cv::waitKey(0);
    }
    else if( flag == normYes )
    {
        phaNorm =specScale(pha);
        phaNorm =specNorm(pha);

        cv::imwrite("the phaNorm of src.png", phaNorm);
        imshow("the phaNorm of src", phaNorm);
        cv::waitKey(0)
    }
    else
        cout << "showPha normStatus error" << endl;
}
