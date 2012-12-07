#include <iostream>
#include <memory>
#include "tiffimage.h"


using namespace std;

int main()
{
    shared_ptr<TiffImage> myimg(new TiffImage);
    myimg->setimageFile("/home/saedelaere/tifftest.tiff");
    myimg->readImage();
    myimg->transformToComplentary();
    myimg->writeImage();
    return  0;
}

