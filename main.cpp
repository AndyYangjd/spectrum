#include "spec.h"

int main(int argc, char** argv)
{
    using namespace std;
    using namespace spec;

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
    img1.empty();
    img1.showSizeSrc();
    img1.showSizeDft();
    img1.saveAmp();
    img1.savePha();
    img1.saveSrcFile();

    return 0;
}
