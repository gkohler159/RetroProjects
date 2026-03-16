#include <iostream>
#include "png_to_ascii.h"
#include <fstream>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <filesystem>

/*
PNG to ASCII Converter 
Author: Grace Kohler

Project: A program that reads in a .PNG or .JPG file and converts it into an ASCII photo design

 */

using namespace cv;
namespace fs = std::filesystem;

std::vector<char> shading_chars = {'@', '%', '#', '*', '+', '-', ':', '.'};

char matchValueWithChar(int pixel_brightness, std::vector<char> shading_chars)
{
    //shading chars go from darkest to lightest
    //0 is darkest, 256 is lightest
    int idx = pixel_brightness * shading_chars.size() / 256;
    char c = shading_chars[idx];
    return c;
}

bool returnValidFilePath(fs::path filepath)
{
    std::string extension =  filepath.extension().string();
    for(char& c : extension)
    {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    if(extension != ".jpeg" && extension != ".png" && extension != ".jpg")
    {
        std::cout << extension << std::endl;
        return false;
    }
    return true;
}

//Usage is ./image_to_ascii image.png
int main(int argc, char* argv[])
{
    //Steps

    //0. Verify image is valid
    if(argc != 2)
    {
        std::cout<<"Usage: "<<argv[0]<< "image.png"<<std::endl;
        return 1;
    }

    fs::path fullpath{argv[1]};
    std::string imagefilename = fullpath.stem().string();
    std::string imagefile = fullpath.string();
    if(!returnValidFilePath(fullpath))
    {
        std::cout<<"Error: File must have a .PNG or .JPG extension"<<std::endl;
        return 1;
    }

    std::string asciipathname = imagefilename.append(".txt"); //generates an ascii filepathname
    std::string extension = fullpath.extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    Mat image;
    if(extension == "png")
    {
        image = imread(fullpath.string(), IMREAD_COLOR);
    }
    else
    {
        //assume it is a jpeg without alpha channel
        image = imread(fullpath.string());
    }

    std::string asciiCharList;
    std::ofstream outfile(asciipathname);
    Mat hsv_image;
    cvtColor(image, hsv_image, COLOR_BGR2HSV);
    for(int i=0; i < hsv_image.rows; i++)
    {
        for(int j=0; j<hsv_image.cols; j++)
        {
            Vec3b pixel = hsv_image.at<Vec3b>(i, j);
            int pBrightness = pixel[2];
            int idx = pBrightness * asciiCharList.size() / 256;
            char outputChar = matchValueWithChar(pBrightness, shading_chars);
            outfile << outputChar;
        }
        outfile << "\n";
    }
    outfile.close();
    return 0;
}
