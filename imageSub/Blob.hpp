//
//  Blob.hpp
//  imageSub
//
//  Created by icbrahimc on 4/29/17.
//  Copyright © 2017 icbrahimc. All rights reserved.
//

#ifndef Blob_hpp
#define Blob_hpp


#include <iostream>
#include <stdio.h>
#include <vector>

class Blob {
private:
    std::vector<std::pair<int, int>> points;
    int minY,
    minX,
    maxY,
    maxX;
public:
    // Base constructor.
    Blob() {
        minX = 0;
        maxX = 0;
        minY = 0;
        maxY = 0;
    }
    
    // Constructor.
    Blob(int x, int y) {
        points.push_back(std::pair<int, int>(x,y));
        minX = x;
        maxX = x;
        minY = y;
        maxY = y;
    }
    
    // Add to the user blob.
    void addToBlob(int, int);
    
    // Check if the new valid points is close to a blob.
    bool isNear(int, int);
    
    // Size of the blob dimensionally.
    int area() { return (maxX - minX) * (maxY - minY); };
    
    // Print the blob.
    void printBlob() const {
        std::cout << "MaxX: " << maxX << " MaxY: " << maxY << "\n";
        std::cout << "MinX: " << minX << " MinY: " << minY << "\n";
    };
    
    // Return the coordinates of the plane.
    std::vector<int> returnCoordinates() {
        std::vector<int> coord;
        coord.push_back(minX);
        coord.push_back(maxX);
        coord.push_back(minY);
        coord.push_back(maxY);
        return coord;
    };
    
    // Return the blob points of the structure.
    std::vector<std::pair<int,int>> returnBlobPoints() { return points; };
};

int min(int, int);
int max(int, int);
#endif /* Blob_hpp */
