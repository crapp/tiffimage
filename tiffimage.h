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
