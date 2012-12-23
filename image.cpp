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

#include "image.h"

Image::Image()
{
}

Image::~Image()
{
}

string Image::hexadecimal = "0123456789ABCDEF";

string Image::rgbToHex(const vector<int> &rgb)
{
    //rgb to hex
    string hexvalue = "";
    ostringstream oss;
    for (auto const &i : rgb)
    {
        oss << hex << i; // use std::hex and streams to transform an int to hexvalue
        hexvalue.append(oss.str());
        if (oss.str().compare("0") == 0)
        {
            hexvalue.append("0");
        }
        oss.str("");
    }
    transform(hexvalue.begin(), hexvalue.end(),hexvalue.begin(), ::toupper); //hexvalue to upper
    return hexvalue;
}

vector<int> Image::hextToRGB(const string &hexval)
{
    vector<int> complementaryRGB;
    stringstream ss;
    int j = 0;
    for (unsigned int i = 0 ; i < hexval.length(); i = i+2)
    {
        string rgbStr;
        rgbStr += hexval[i];
        rgbStr += hexval[i+1];
        ss << hex << rgbStr;
        ss >> j;
        complementaryRGB.push_back(static_cast<int>(j));
    }
    return complementaryRGB;
}

string Image::subtractHex(const string &hexval)
{
    string hexWhite = "FFFFFF";
    string subtractedHex;
    stringstream ss;
    for (int i = hexval.length() - 1; i >= 0 ; i--)
    {
        //get hex value when we subtract two other hex values
        int posHexWhite = this->hexadecimal.find(hexWhite[i]);
        int posHexval = this->hexadecimal.find(hexval[i]);
        int newPos = posHexWhite - posHexval;
        ss << hexadecimal.at(newPos); //use a stringstream otherwise there are strange side effects
        subtractedHex.insert(0, ss.str()); //we start to subtract at the rightmost position but the hex has to be written from left to right
        ss.str(""); //empty stringstream
    }
    return subtractedHex;
}

int Image::hexToDec(const string &hexval)
{
    int retDec = 0;
    std::stringstream ss;
    ss << hexval;
    ss >> std::hex >> retDec;
    return retDec;
}
