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
    lena.saveRcUsePha();

    return 0;
}
