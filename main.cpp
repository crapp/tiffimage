//    Copyright (C) 2012  Christian Rapp

//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <memory>
#include "tiffimage.h"

#define COMPLEMENTARY 0
#define COMBINE 1

using namespace std;

int main()
{
    unique_ptr<TiffImage> myimg(new TiffImage);
    unique_ptr<TiffImage> myimgOverlay(new TiffImage);
    //myimg->setimageFile("../TiffImage/Resources/tifftest2.tiff");
    myimg->setimageFile("/Users/chrwr/tiffCombineSource2.tiff");
    myimgOverlay->setimageFile("/Users/chrwr/tiffCombineWith2.tiff");
    myimg->readImage();
    myimgOverlay->readImage();

    if (COMPLEMENTARY == 1)
        myimg->transformToComplementary();
    if (COMBINE == 1)
        myimg->combineTwoTiff(0, 100, &(*myimgOverlay));

    string outFile = getenv("HOME");
    outFile += "/tifftestCombined2.tiff";
    if (myimg->writeImage(outFile))
    {
        cout << "Writing of ouput image file was successful" << endl;
    }
    return  0;
}
