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

#ifndef TIFFIMAGE_H
#define TIFFIMAGE_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <tiffio.h>

#include "image.h"

using namespace std;

class TiffImage : protected Image
{
public:
    TiffImage();

    void setimageFile(const string &imgFile);
    string getimageFile();

    void setCompressionOutput(const uint &compressionLevel);
    uint getCompressionOuput();

    void readImage();
    bool writeImage(const string &outFile);

    void transformToComplementary();
    //Combines two Images.
    //startPos is the starting position
    //timg is another instance of TiffImage. The Image Buffer will be used and all
    //Pixels in the original one will be substituted with the ones from the new buffer
    //We use here a raw Pointer so we can check for NULL, but the instance should have
    //been created as smart pointer
    void combineTwoTiff(const uint32 &startPos, TiffImage *timg);

private:
    const static uint32 bUIntValue = 4278190080;

    uint compressionOutput;

    vector<uint32> imgBuffer; //holds an image buffer
    uint32 imgWidth, imgHeight, imgOrientation; //width, height, orientation

    string imageFile; //path to image file

    //return complementary color as vector<int>
    int getComplementaryColour(const vector<int> &rgb);

};

#endif // TIFFIMAGE_H
