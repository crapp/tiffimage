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

TiffImage::TiffImage() : compressionOutput(5)
{
}

void TiffImage::setimageFile(const string &imgFile)
{
    this->imageFile = imgFile;
}

string TiffImage::getimageFile()
{
    return this->imageFile;
}

void TiffImage::setCompressionOutput(const uint &compressionLevel)
{
    //1 No Compression
    //5 LZW
    //7 JPEG
    //32909 DEFLATE
    vector<int> compLevels = {1, 5, 7, 32909};

    if (find(compLevels.begin(), compLevels.end(), compressionLevel) != compLevels.end())
    {
        this->compressionOutput = compressionLevel;
    }
    else
    {
        cerr << "Supported values for compression are 5(LZW), 7(JPEG), 32909(DEFLATE)!" << endl;
    }
}

uint TiffImage::getCompressionOuput()
{
    return this->compressionOutput;
}

void TiffImage::readImage()
{
    TIFF *tif = TIFFOpen(this->getimageFile().c_str(), "r");
    if (tif) {
        size_t npixels;
        uint32* raster;

        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &imgWidth);
        TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &imgHeight);
        TIFFGetField(tif, TIFFTAG_ORIENTATION, &imgOrientation);
        npixels = imgWidth * imgHeight; //no of pixels in image
        raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32));
        if (raster != NULL) {
            if (TIFFReadRGBAImage(tif, imgWidth, imgHeight, raster, 0)) {
                //...process raster data...
                //write data in vector member so we can do with it what we want

                uint32 *rasterPrint = raster;
                for(size_t n=0;n<npixels;n++)
                {
                    imgBuffer.push_back(raster[n]);
                    cout << "New Pixel R: ";
                    cout << TIFFGetR(*rasterPrint) << " G: ";
                    cout << TIFFGetG(*rasterPrint) << " B: ";
                    cout << TIFFGetB(*rasterPrint) << " uint32: ";
                    cout << *rasterPrint << endl;
                    *rasterPrint++;
                }

            }
            _TIFFfree(raster);
            //TIFFRedRGBAImage is starting in the lower left corner, so we
            //got to swap our vector. this means we hve to swap first row with last
            //and so on.
            uint32 upBufPos, downBufPos;
            for (uint32 i = 0 ; i < this->imgHeight / 2; i++)
            {
                for (uint32 j = 0 ; j < this->imgWidth; j++)
                {
                    upBufPos = i * this->imgWidth + j;
                    if (i*j == 0)
                    {
                        upBufPos = i+j;
                    }
                    downBufPos = ((this->imgHeight - i - 1) * this->imgWidth) + j;
                    swap(this->imgBuffer[upBufPos], this->imgBuffer[downBufPos]);
                }
            }
        }
        TIFFClose(tif);
    }
}

bool TiffImage::writeImage(const string &outFile)
{
    bool retBool = false;
    TIFF *output_image;

    // Open the TIFF file
    if ((output_image = TIFFOpen(outFile.c_str(), "w")) == 0)
    {
      cerr << "Unable to write tif file: " << outFile << endl;
    }

    // We need to set some values for basic tags before we can add any data
    TIFFSetField(output_image, TIFFTAG_IMAGEWIDTH, this->imgWidth);
    TIFFSetField(output_image, TIFFTAG_IMAGELENGTH, this->imgHeight);
    TIFFSetField(output_image, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(output_image, TIFFTAG_SAMPLESPERPIXEL, 4);
    TIFFSetField(output_image, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

    TIFFSetField(output_image, TIFFTAG_COMPRESSION, this->getCompressionOuput());
    TIFFSetField(output_image, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
    TIFFSetField(output_image, TIFFTAG_ORIENTATION, this->imgOrientation);

    // Write the information to the file
    if (TIFFWriteEncodedStrip(output_image, 0, &imgBuffer[0], imgWidth*imgHeight * 4) > -1)
    {
        retBool= true; //if bigger than -1 writing was successful
    }


    // Close the file
    TIFFClose(output_image);
    return retBool;
}

int TiffImage::getComplementaryColour(const vector<int> &rgb)
{
    string hexvalue = this->rgbToHex(rgb); //RGB to hex
    string subtractedHex = this->subtractHex(hexvalue); //Get hex value of complementary color by subtracting from white
    //complementaryRGB = this->hextToRGB(subtractedHex); //Transform back to RGB
    return this->hexToDec(subtractedHex);
}

void TiffImage::transformToComplementary()
{
    if (this->imgBuffer.size() > 0) //Look if there is something in the image Buffer
    {
        vector<int> rgba;
        int newDec = 0;
        vector<uint32>::iterator vit = imgBuffer.begin();
        for (auto i : imgBuffer) //Loop over Im age Buffer
        {
            //Get RGB values
            rgba.push_back(TIFFGetR(i));
            rgba.push_back(TIFFGetG(i));
            rgba.push_back(TIFFGetB(i));
            //request complementary color
            newDec = getComplementaryColour(rgba);
            *vit = bUIntValue + newDec; //use iterator to update data in buffer
            vit++; //don't forget to increase the iterator so we look at the right position
            rgba.clear(); //deletes all entries in the vector
            rgba.shrink_to_fit(); //shrinks vector to fit actual size.
        }
    }
}

void TiffImage::combineTwoTiff(const uint32 &startPos, TiffImage *timg)
{
    if (timg == 0)
    {
        //blub
    }
}
