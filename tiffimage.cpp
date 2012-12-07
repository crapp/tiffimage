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

#include "tiffimage.h"

string TiffImage::hexadecimal = "0123456789ABCDEF";

TiffImage::TiffImage() : m_imgBuffer(0)
{
}

void TiffImage::setimageFile(const string &imgFile)
{
    this->m_imageFile = imgFile;
}

string TiffImage::getimageFile()
{
    return this->m_imageFile;
}

void TiffImage::readImage()
{
    TIFF *tif = TIFFOpen(this->getimageFile().c_str(), "r");
    if (tif) {
        uint32 w, h;
        size_t npixels;
        uint32* raster;

        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
        TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
        npixels = w * h;
        raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32));
        if (raster != NULL) {
            if (TIFFReadRGBAImage(tif, w, h, raster, 0)) {
                //...process raster data...
                //write data in vector member so we can do with it what we want

                uint32 *rasterPrint = raster;
                for(size_t n=0;n<npixels;n++)
                {
                    m_imgBuffer.push_back(raster[n]);
                    cout << "New Pixel R: ";
                    cout << TIFFGetR(*rasterPrint) << " G: ";
                    cout << TIFFGetG(*rasterPrint) << " B: ";
                    cout << TIFFGetB(*rasterPrint) << endl;
                    *rasterPrint++;
                }
                cout << raster[0] << endl;
                cout << raster[1] << endl;
                cout << TIFFGetR(*raster) << endl;
                cout << TIFFGetG(*raster) << endl;
                cout << TIFFGetB(*raster) << endl;
            }
            _TIFFfree(raster);
        }
        TIFFClose(tif);
    }
}

void TiffImage::writeImage(const string &outFile)
{
    TIFF *output_image;

    // Open the TIFF file
    if ((output_image = TIFFOpen(outFile.c_str(), "w")) == 0)
    {
      cerr << "Unable to write tif file: " << output_filename << endl;
    }

    // We need to set some values for basic tags before we can add any data
    TIFFSetField(output_image, TIFFTAG_IMAGEWIDTH, m_width);
    TIFFSetField(output_image, TIFFTAG_IMAGELENGTH, m_height);
    TIFFSetField(output_image, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(output_image, TIFFTAG_SAMPLESPERPIXEL, 4);
    TIFFSetField(output_image, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

    TIFFSetField(output_image, TIFFTAG_COMPRESSION, COMPRESSION_DEFLATE);
    TIFFSetField(output_image, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

    // Write the information to the file
    TIFFWriteEncodedStrip(output_image, 0, &m_image_data[0], m_width*m_height * 4);

    // Close the file
    TIFFClose(output_image);
}

vector<int> TiffImage::getComplementaryColour(const vector<int> &rgb)
{
    vector<int> complementaryRGB;
    string hexvalue = this->rgbToHex(rgb);
    string subtractedHex = this->subtractHex(hexvalue);
    complementaryRGB = this->hextToRGB(subtractedHex);
    return complementaryRGB;
}

string TiffImage::rgbToHex(const vector<int> &rgb)
{
    //rgb to hex
    string hexvalue = "";
    ostringstream oss;
    for (auto const &i : rgb)
    {
        oss << hex << i;
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

vector<int> TiffImage::hextToRGB(const string &hexval)
{
    vector<int> complementaryRGB;
    stringstream ss;
    int j = 0;
    for (uint i = 0 ; i < hexval.length(); i = i+2)
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

string TiffImage::subtractHex(const string &hexval)
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

void TiffImage::rgbTester()
{
    vector<int> tester;
    tester.push_back(100);
    tester.push_back(150);
    tester.push_back(0);
    tester = getComplementaryColour(tester);
}


void TiffImage::transformToComplentary()
{
    if (this->m_imgBuffer != 0)
    {
        vector<int> rgba;
        vector<uint32>::iterator vit = m_imgBuffer.begin();
        for (auto i : m_imgBuffer)
        {
            rgba.push_back(TIFFGetR(i));
            rgba.push_back(TIFFGetG(i));
            rgba.push_back(TIFFGetB(i));
            rgba = getComplementaryColour(rgba);
        }
    }
}
