//
//  Image.hpp
//  imageSub
//
//  Created by icbrahimc on 4/25/17.
//  Copyright © 2017 icbrahimc. All rights reserved.
//

#ifndef Image_hpp
#define Image_hpp
#define THRESHOLD 400

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>

#include "Blob.hpp"

struct Pixel {
    int red,
    green,
    blue;
    bool threshold;
};

class Image {
private:
    std::vector<Pixel> pixels;  // Vector of pixels that represents the image.
    int width, height, maxColor;    // Represents dimensions and the max color on the scale.
    std::string pValue; // The p value at the top of the ppm file.
    std::vector<Blob> blobs; // The blobs that exist.
public:
    // Constructor.
    Image() {
        width = 0;
        height = 0;
        maxColor = 255;
        pValue = "P3";
    };
    
    // Constructor to open the file.
    Image(std::string);
    
    // Blackout the background.
    void blackOut();
    
    // Write to file.
    void writeToFile(std::string);
    
    // Take two images and find the offset.
    Image imagify(Image);
    
    // Print the contents of the file.
    void printContents() const;
    
};

bool thresholdDeterminant(int, int, int);
bool isNotComment(std::string);
bool isNumber(std::string);
std::vector<std::string> listify(std::string);
int strToInt(std::string);
#endif /* Image_hpp */
