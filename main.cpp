#include "spec.h"
#include "myspace.h"

int main(int argc, char** argv)
{
    using namespace std;
    using namespace myspace;

    if( argc ==1 )
    {
        cout << "Please input photo name in dir /home/andy/ Desktop at command line." << endl
             << "For example: " << argv[0] << " lena.png" << endl;
        return false;
    }
    else
    {
        cout << "There are " << argc-1 << " image need to handle." << endl
             << "Enjory yourself" << endl;
    }

    Spec img1(argv[1]);
    cv::Mat imgPha =img1.getPha();
    cv::Size2i size=img1.getSizeDft();
    cv::Mat tmpAmp(size, CV_32FC1, cv::Scalar::all(1));
    cv::Mat re, im;
    cv::polarToCart(tmpAmp, imgPha, re, im);
    cv::Mat planes[2]={re, im};
    cv::Mat rc;
    cv::merge(planes, 2, rc);
    cv::idft(rc, rc, cv::DFT_SCALE, img1.getSizeSrc().height);
    cv::split(rc, planes);
    planes[0] =planes[0]( cv::Rect(0, 0, img1.getSizeSrc().width, img1.getSizeSrc().height) );

    planes[0] =Display::calib8U(planes[0]);
    cv::imshow("rc", planes[0]);
    cv::waitKey(0);

    return 0;
}
