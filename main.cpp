#include "spec.h"
#include "myspace.h"
#include "applyfilter.h"

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
    cv::Size2i size1=img1.getSizeDft();
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
        ApplyFilter b(imgAmp1, imgPha1, imgAmp2, imgPha2, size1);
        b.saveOutput();
        b.showOutput();
    }

    return 0;
}
