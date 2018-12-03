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

    Spec lena(argv[1]);
    lena.showSizeSrc();
    lena.showSizeDft();

    lena.showAmp();
    lena.showAmp(spec::CENYES);
    lena.showPha();
    lena.showPha(spec::CENYES);

    char closeStatus;
    cout << "Do your want to close all windows?" << endl
         << "y for Yes, others for No :  ";
    cin >> closeStatus;
    lena.closeAllwindows(closeStatus);

    if( closeStatus != 'y' )
        lena.closeAllwindows('y');

    return 0;
}
