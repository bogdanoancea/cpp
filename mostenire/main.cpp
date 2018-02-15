#include <iostream>

using namespace std;
class baza1 {
protected:
    int i;
public:
    baza1(int x) { i = x; cout << "Construieste baza 1" << endl;}
    ~baza1() { cout << "Distruge baza 1" << endl;}
};

class baza2 {
protected:
    int k;
    baza2(int x) { k = x; cout <<"Construieste baza2"<< endl;}
    ~baza2() {cout << "Distruge baza2"<<endl;}
};

class derivat: public baza1, public baza2 {
int j;
public:
    derivat(int x, int y, int z): baza1(y), baza2(z) {j = x; cout<<"Contruieste derivat"<<endl;}
    ~derivat(){cout<<"Distruge derivat"<<endl;}
    void show();
 };

 void derivat::show() {
 cout << i << " " << j << " " <<k << endl;
 }

 int main() {
    derivat ob(3,4,5);
    ob.show();
    return 0;
 }
