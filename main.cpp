#include <iostream>
#include "spec.h"

using namespace std;

int main(int argc, char** argv)
{
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
    Spec lena(argv[1]);
    lena.empty();
    lena.showSizeSrc();
    lena.showSizeDft();
    lena.showAmp();
    lena.showAmp(Spec::NORMYES());
    lena.showPha();
    lena.showPha(Spec::NORMYES());
}
