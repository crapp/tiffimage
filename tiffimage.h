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
#include <tiffio.h>

#include "image.h"

using namespace std;

class TiffImage : protected Image
{
public:
    TiffImage();

    void setimageFile(const string &imgFile);
    string getimageFile();

    void readImage();
    bool writeImage(const string &outFile);

    void transformToComplentary();

private:
    const static uint32 bUIntValue = 4278190080;

    string compressionInput;
    string compressionOutput;

    vector<uint32> imgBuffer; //holds an image buffer
    uint32 imgWidth, imgHeight; //width and height

    string imageFile; //path to image file

    //return complementary color as vector<int>
    int getComplementaryColour(const vector<int> &rgb);

};

#endif // TIFFIMAGE_H
