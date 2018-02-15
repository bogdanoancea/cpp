#include <iostream>

using namespace std;


class complex {
    double re, im;
public:
    complex(double r, double i): re{r}, im{i} {}
    complex(double r): re{r}, im{0} {}
    complex(): re{0}, im{0} {}


    double real() const {return re;}
    void real(double d) {re = d;}
    double imag() const {return im;}
    void imag(double d) {im = d;}


    complex& operator+=(complex z) { re +=z.re; im+=z.im; return *this;}
    complex& operator-=(complex z) { re -=z.re; im-=z.im; return *this;}

};

complex operator+(complex a, complex b) {return a+=b;}
complex operator-(complex a, complex b) { return a-=b;}
complex operator-(complex a) {return {-a.real(), -a.imag()};}
bool operator==(complex a, complex b) { return a.real() == b.real() && a.imag() == b.imag();}
bool operator!=(complex a, complex b) {return !(a==b);}





int main()
{
    complex a{2,3};
    complex b {a+complex{2,3}};
    complex c{a+b+complex{1,2.3}};

    c = -(b+a);
    return 0;
}
