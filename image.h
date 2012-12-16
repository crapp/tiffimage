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

#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> //for transform

using namespace std;

class Image
{
public:
    Image();
    virtual ~Image();
protected:
    //Provide some basic Functions that all image formats may find useful.
    //converts rgb(a) values to hex values
    string rgbToHex(const vector<int> &rgb);
    //converts hex to rgb(a) values
    vector<int> hextToRGB(const string &hexval);
    //subtracs two hex values. in this case it subtractes the given hex value
    //from white (FFFFFF) which results in the complementary color.
    string subtractHex(const string &hexval);
    //transform hex to decimal
    int hexToDec(const string &hexval);
private:
    static string hexadecimal;
};

#endif // IMAGE_H
