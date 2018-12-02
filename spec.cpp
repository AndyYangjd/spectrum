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

cv::Mat getAmp(void);
void showAmp(void);
cv::Mat getPha(void);
void showPha(void);
