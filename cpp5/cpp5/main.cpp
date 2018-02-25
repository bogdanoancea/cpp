//
//  main.cpp
//  cpp5
//
//  Created by Bogdan Oancea on 15/02/2018.
//  Copyright © 2018 Bogdan Oancea. All rights reserved.
//

#include <iostream>
#include <vector>
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

class Triangle: public Shape {
public:
    Triangle(Point pp1, Point pp2, Point pp3):p1{pp1}, p2{pp2}, p3{pp3}{}
    ~Triangle() {}
    Point center() const {return Point(0,0);}
    void move(Point to) {cout << "Not yet implemented" << endl;}
    void draw() const { cout << "don't know how to draw a traingle" << endl;}
    void rotate(int angle){cout<< "Not yet implemented" << endl;}
private:
    Point p1,p2,p3;
};



class Smiley: public Circle {
public:
    Smiley(Point p, double r): Circle{p,r}, mouth{nullptr}{}
    ~Smiley() {
        delete mouth;
        for(auto p: eyes) delete p;
    }
    void move(Point to) const;
    void draw() const;
    //void rotate(int angle);
    void add_eye(Shape* s) { eyes.push_back(s);}
    virtual void wink(int i){};
    
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


Shape* read_shape(istream& is) {
    kind k = kind::circle;
    int type;
    double x, y, r, x1, x2, x3, y1, y2, y3;
    cout << "shape type: 1- circle; 2- triangle; 3 - smiley" << endl;
    is >> type;
    if(type == 1 ) k = kind::circle;
    if(type == 2 ) k = kind::triangle;
    if(type == 3 ) k = kind::smiley;
    switch(k) {
        case kind::circle:{
            is >> x >> y >> r;
            Point p = Point(x,y);
            return new Circle{p, r};
        }
        case kind::triangle:
        {
            is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            return new Triangle(Point(x1,y1), Point(x2,y2), Point(x3,y3));
        }
        case kind::smiley:
        {
            is >> x >> y >> r;
            Point p1 = Point(x,y);
            return new Smiley{p1, r};
        }
        default:
            throw exception();
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    int x;
    cin >> x;
    std::cout << "Hello, World!\n";
    Shape* s = read_shape(std::cin);
    s->draw();
    return 0;
}


