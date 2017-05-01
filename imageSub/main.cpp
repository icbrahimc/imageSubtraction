//
//  main.cpp
//  imageSub
//
//  Created by icbrahimc on 4/25/17.
//  Copyright © 2017 icbrahimc. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Image.hpp"

std::vector<Image> generateImages(std::string*, int);

int main(int argc, const char * argv[]) {
    std::string test = "testing";
    std::string filesToParse[20] = {
        "image002.ppm", "image003.ppm", "image004.ppm", "image005.ppm",
        "image006.ppm", "image007.ppm", "image008.ppm", "image009.ppm",
        "image010.ppm", "image011.ppm", "image013.ppm", "image014.ppm",
        "image015.ppm", "image016.ppm", "image017.ppm", "image018.ppm",
        "image019.ppm", "image020.ppm", "image021.ppm", "image022.ppm"
    };
    
    // Generate the images.
    std::vector<Image> imageVector = generateImages(filesToParse, 20);
//    imageVector[0].writeToFile("testing");
    // Create the image.
    for (int count = 1; count < imageVector.size(); count++) {
        Image createImage = imageVector[count].imagify(imageVector[count - 1]);
        createImage.blackOut();
        createImage.writeToFile(test + std::to_string(count));
    }
    
    
    return 0;
}

std::vector<Image> generateImages(std::string *listString, int sizeOfList) {
    std::vector<Image> output;
    for (int count = 0; count < sizeOfList; count++) {
        Image img = Image(listString[count]);
        output.push_back(img);
    }
    
    return output;
}
