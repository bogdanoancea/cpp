//
//  main.cpp
//  cpp5
//
//  Created by Bogdan Oancea on 15/02/2018.
//  Copyright © 2018 Bogdan Oancea. All rights reserved.
//

#include <iostream>
#include <istream>
#include<vector>
#include "point.h"
using namespace std;

enum class kind {circle, triangle, smiley};


class Shape {
public:
    virtual Point center() const = 0;
    virtual void move(Point to) = 0;
    
    virtual void draw() const = 0;
    virtual void rotate(int angle) = 0;
    
    virtual ~Shape() {}
    
};


class Circle: public Shape {
public:
    Circle(Point p, double radius);
    Point center() const { return c;}
    void move(Point to) { c = to; }
    void draw() const;
    void rotate(int angle){cout<< "Not yet implemented" << endl;}
    ~Circle() {}
private:
    Point c;
    double rd;
};


Circle::Circle(Point p, double radius): c{p.getX(), p.getY()} {
    rd = radius;
}

void Circle::draw() const {
    c.draw();
}


class Smiley: public Circle {
public:
    Smiley(Point p, double r): Circle{p,r}, mouth{nullptr}{}
    ~Smiley() {
        delete mouth;
        for(auto p: eyes) delete p;
    }
    void move(Point to);
    void draw() const;
    void rotate(int angle);
    void add_eye(Shape* s) { eyes.push_back(s);}
    virtual void wink(int i);
    
private:
    vector<Shape*> eyes;
    Shape* mouth;
};

void Smiley::draw() const {
    Circle::draw();
    for(auto p : eyes)
        p->draw();
    mouth->draw();
}


Shape* read_shape(istream is) {
    kind k;
    int type;
    double x, y, r;
    is >> type;
    if(type == 1 ) k = kind::circle;
    if(type == 2 ) k = kind::triangle;
    if(type == 3 ) k = kind::smiley;
    switch(k) {
        case kind::circle:
            is >> x >> y >> r;
            Point p = Point(x,y);
            return new Circle{p, r};
        case kind::triangle:
            is >>x;
        case kind::smiley:
            
            
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
