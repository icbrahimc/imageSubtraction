//
//  Image.cpp
//  imageSub
//
//  Created by icbrahimc on 4/25/17.
//  Copyright © 2017 icbrahimc. All rights reserved.
//

#include "Image.hpp"
const int OFFSET = 48;
const int AREA = 500;
const int BLOBOFFSET = 5;

// Initialize the image object from the
Image::Image(std::string fileToOpen) {
    std::string line;
    std::ifstream reader;
    reader.open(fileToOpen);
    
    bool pValueFlag = false,
    dimensionsFlag = false,
    maxFlag = false;
    
    
    
    if (reader.is_open()) {
        
        while (!reader.eof()) {
            if (!pValueFlag) {
                getline(reader, line);
                pValue = line;
                pValueFlag = true;
            }
            
            else if (!dimensionsFlag) {
                getline(reader, line);
                if (isNotComment(line)) {
                    std::vector<std::string> dimensions = listify(line);
                    width = strToInt(dimensions[0]);
                    height = strToInt(dimensions[1]);
                    dimensionsFlag = true;
                }
            }
            
            else if (!maxFlag) {
                if (isNotComment(line)) {
                    getline(reader, line);
                    maxColor = strToInt(line);
                    maxFlag = true;
                }
            }
            
            else {
                Pixel pixelToPush;
                int red = 0, green = 0, blue = 0;
                while (reader >> red >> green >> blue) {
                    pixelToPush.red = red;
                    pixelToPush.green = green;
                    pixelToPush.blue = blue;
                    pixels.push_back(pixelToPush);
                }
            }
        }
        
        reader.close();
    }
    
    else std::cout << "Unable to open file";
    
}

void Image::blackOut() {
    int miniX = 0,
    maxiX = 0,
    miniY = 0,
    maxiY = 0,
    idx = 0;
    
    std::vector<Pixel> mockPixels = pixels;
    
    for (int count = 0; count < pixels.size(); count++) {
        if (pixels[count].threshold) {
            continue;
        } else {
            pixels[count].red = 255;
            pixels[count].blue = 255;
            pixels[count].green = 255;
        }
    }
//    for (int count = 0; count < 1440; count++) {
//        pixels[count].red = 0;
//        pixels[count].blue = 0;
//        pixels[count].green = 0;
//    }
//    std::cout << "Blobs:" << blobs.size() << "\n";
//    miniX = 150;   // The x coordinate for the code.
//    maxiX = 180;
//    int mini = 300;
//    miniY = 300;
//    maxiY = 400;
//    for (int i = miniX; i < maxiX; i++) {
//        for (int j = miniY; j < maxiY; j++) {
//            idx = i + (720 * j);
//            std::cout << "IDX: " << idx << std::endl;
//            pixels[idx].red = 0;
//            pixels[idx].green = 0;
//            pixels[idx].blue = 0;
//        }
//    }
    
    for (int count = 0; count < blobs.size(); count++) {
        
        if (blobs[count].area() > AREA) {
            std::vector<int> coord = blobs[count].returnCoordinates();  // Return the coordinates of the  blob.
            std::vector<std::pair<int, int>> blobPoints = blobs[count].returnBlobPoints();  // Return the points of the blob.
            maxiX = coord[1];
            
            // Fill in the area between the point and the edge of the picture.
            for (int count = 0; count < blobPoints.size(); count++) {
                if ((blobPoints[count].second - maxiX) > BLOBOFFSET) {
                    for (int i = blobPoints[count].first; i < maxiX - BLOBOFFSET; i++) {
                        idx = i + (blobPoints[count].second*720);
                        pixels[idx].red = mockPixels[idx].red;
                        pixels[idx].green = mockPixels[idx].green;
                        pixels[idx].blue = mockPixels[idx].blue;
                    }
                }
            }
        }
    }
}

Image Image::imagify(Image imgOne) {
    Image createImage;
    
    int x = 0,
    y = 0,
    red = 0,
    green = 0,
    blue = 0,
    diffRed = 0,
    diffGreen = 0,
    diffBlue = 0;
    
    Pixel pixelsToPass;
    
    // Setup the old values for the new image.
    createImage.height = height;
    createImage.width = width;
    createImage.pValue = pValue;
    createImage.maxColor = maxColor;
    
    for (int count = 0; count < pixels.size(); count++) {
        // The x and y coordinates of the pixel.
        x = count % 720;
        y = count / 720;
        // Extract the rgb values from the next frame.
        red = imgOne.pixels[count].red;
        green = imgOne.pixels[count].green;
        blue = imgOne.pixels[count].blue;
        
        // The square root of the difference between the rgb values to compare to a threshold.
        diffRed = (red - pixels[count].red) * (red - pixels[count].red);
        diffGreen = (green - pixels[count].green) * (green - pixels[count].green);
        diffBlue = (blue - pixels[count].blue) * (blue - pixels[count].blue);
        
        // Threshold determinants.
        if (thresholdDeterminant(diffRed, diffBlue, diffGreen)) {
            pixelsToPass.red = red;
            pixelsToPass.green = green;
            pixelsToPass.blue = blue;
            pixelsToPass.threshold = true;
            
            bool found = false;
            for (int i = 0; i < createImage.blobs.size(); i++) {
                if (createImage.blobs[i].isNear(x, y)) {
                    createImage.blobs[i].addToBlob(x, y);
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                Blob newBlob = Blob(x, y);
                
                createImage.blobs.push_back(newBlob);
            }
            
            createImage.pixels.push_back(pixelsToPass);
        } else {
            pixelsToPass.red = red;
            pixelsToPass.green = green;
            pixelsToPass.blue = blue;
            pixelsToPass.threshold = false;
            createImage.pixels.push_back(pixelsToPass);
        }
        
    }
    
    return createImage;
}

// Print the contents of the image object.
void Image::printContents() const {
    std::cout << pValue << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Length: " << height << std::endl;

    for (int count = 0; count < pixels.size(); count++) {
        std::cout << pixels[count].red << ", " << pixels[count].green << ", " << pixels[count].blue <<std::endl;
    }
}

// Determines if a string is a number
bool isNumber(std::string number) {
    for (int i = 0; i < number.length(); i++) {
        if (!((int)number[i] - OFFSET < 10 && (int)number[i] - OFFSET >= 0)) {
            return false;
        }
    }
    return true;
}

// Takes a string and makes an array on the spaces and saves the size
std::vector<std::string> listify(std::string content) {
    std::vector<std::string> result;
    std::istringstream iss(content);
    // splits a string on spaces into a std::vector of strings
    for (std::string s; iss >> s; ) {
        result.push_back(s);
    }
    return result;
}

// Converts a string to a number, returns -1 if it cannot convert
int strToInt(std::string number) {
    int result = 0, length = number.size();
    if (isNumber(number)) {
        for (int digit = 0; digit < length; digit++) {
            result += (number[digit] - OFFSET) * pow(10, length - (digit + 1));
        }
    } else {
        result = -1;
    }
    return result;
}

// If the value is a not a comment.
bool isNotComment(std::string input) {
    return (input[0] != '#');
}

// Threshold determinant.
bool thresholdDeterminant(int one, int two, int three) {
    return (one+two+three) > THRESHOLD;
}

// Write the image to a file.
void Image::writeToFile(std::string name) {
    std::string fileName = name + ".ppm";
    std::ofstream newFile;
    newFile.open(fileName);
    int counter = 0;
    
    newFile << pValue << "\n";
    newFile << width << " " << height << "\n";
    newFile << maxColor << "\n";
    
    for (int count = 0; count < pixels.size(); count++) {
        newFile << pixels[count].red << " " << pixels[count].green << " " << pixels[count].blue << " ";
        
        counter += 3;
        if (counter >= 24) {
            newFile << "\n";
            counter = 0;
        }
    }
    
    newFile.close();
}
