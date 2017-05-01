//
//  Blob.cpp
//  imageSub
//
//  Created by icbrahimc on 4/29/17.
//  Copyright © 2017 icbrahimc. All rights reserved.
//

#include "Blob.hpp"

const float DISTANCETHRESHOLD = 10;

// Add a dot to the blob.
void Blob::addToBlob(int x, int y) {
    points.push_back(std::pair<int, int>(x,y));
    minX = min(x, minX);
    minY = min(y, minY);
    maxX = max(x, maxX);
    maxY = max(y, maxY);
}

// If the dot is near the blob.
bool Blob::isNear(int x, int y) {
    float centeredX = (minX + maxX) / 2;
    float centeredY = (minY + maxY) / 2;
    
    float distance = 10000000;
    
    for (int count = 0; count < points.size(); count++) {
        float temp = ((x - points[count].first) * (x - points[count].first)) + ((y - points[count].second) * (y - points[count].second));
        if (temp < distance) {
            distance = temp;
        }
    }
    
    if (distance < DISTANCETHRESHOLD * DISTANCETHRESHOLD) {
        return true;
    } else {
        return false;
    }
    return true;
}

// Min function.
int min(int one, int two) {
    if (one < two) {
        return one;
    }
    
    return two;
}

// Max function.
int max(int one, int two) {
    if (one < two) {
        return two;
    }
    
    return one;
}
