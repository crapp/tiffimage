#include <iostream>
#include <memory>
#include "tiffimage.h"

using namespace std;

int main()
{
    shared_ptr<TiffImage> myimg(new TiffImage);
    myimg->setimageFile("../TiffImage/Resources/tifftest2.tiff");
    myimg->readImage();
    myimg->transformToComplentary();
    string outFile = getenv("HOME");
    outFile += "/tifftestComplement2.tiff";
    if (myimg->writeImage(outFile))
    {
        cout << "Writing of ouput image file was successful" << endl;
    }
    return  0;
}

