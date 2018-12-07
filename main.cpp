#include "spec.h"
#include "applyfilter.h"

cv::Mat centralize(cv::Mat _src)
{
    for(int i=0; i<_src.rows; i++)
        for(int j=0; j<_src.cols; j++)
        {
            if( (i + j)%2 != 0)
                _src.at<uchar>(i, j) = - _src.at<uchar>(i, j);
        }
    return _src;
}

cv::Mat scalel(cv::Mat _src)
{
    _src +=cv::Scalar::all(1);
    cv::log( _src, _src );
    return _src;
}

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

    Spec img1(argv[1]);
    cv::Size2i size =img1.getSizeSrc();
    cv::Size2i size1 =img1.getSizeDft();
    cv::Mat imgPha1 =img1.getPha();
    cv::Mat imgAmp1 =img1.getAmp();
    imgAmp1.setTo(1);

    Spec img2(argv[2]);
    cv::Size2i size2=img2.getSizeDft();
    cv::Mat imgPha2 =img2.getPha();
    cv::Mat imgAmp2 =img2.getAmp();
    imgAmp2.setTo(1);
    imgPha2.setTo(0);

    if( size1 == size2 )
    {
        ApplyFilter b(imgAmp1, imgPha1, imgAmp2, imgPha2, size);
        b.showOutput();
    }

    return 0;
}
