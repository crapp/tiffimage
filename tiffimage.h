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
#include <sstream>
#include <algorithm>
#include <tiffio.h>

using namespace std;

class TiffImage
{
public:
    TiffImage();

    void setimageFile(const string &imgFile);
    string getimageFile();

    void readImage();
    void writeImage();

    void rgbTester();

private:
    static string hexadecimal;
    vector<uint32> m_imgBuffer;
    string m_imageFile;
    vector<int> getComplementaryColour(const vector<int> &rgb);
    string rgbToHex(const vector<int> &rgb);
    vector<int> hextToRGB(const string &hexval);
    string subtractHex(const string &hexval);

};

#endif // TIFFIMAGE_H
