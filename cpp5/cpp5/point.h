//
//  point.h
//  cpp5
//
//  Created by Bogdan Oancea on 15/02/2018.
//  Copyright © 2018 Bogdan Oancea. All rights reserved.
//

#ifndef point_h
#define point_h
#include<iostream>
using namespace std;

class Point {
    double x, y;
public:
    Point(double xx, double yy): x{xx}, y{yy} {};
    double getX() const {return x;}
    double getY() const {return y;}
    void draw() const { std::cout << x << " " << y << endl;}
};


#endif /* point_h */

