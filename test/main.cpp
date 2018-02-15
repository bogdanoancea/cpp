#include <iostream>

using namespace std;

class loc {
    int lat, lng;
    public:
        loc() {}
        loc(int lt, int lg) {lat = lt; lng = lg;}

        void show() {
            cout << lat << " " << lng << endl;
        }
        loc operator+(loc op2);
        loc operator-(loc op2);
        loc operator=(loc op2);
        loc operator++();
};

loc loc::operator+(loc op2) {
    loc temp;
    temp.lat = op2.lat + lat;
    temp.lng = op2.lng + this->lng;
    return temp;
}


loc loc::operator-(loc op2) {
    loc temp;
    temp.lat = lat - op2.lat;
    temp.lng = lng - op2.lng;
    return temp;
}

loc loc::operator=(loc op2) {
    lat = op2.lat;
    lng = op2.lng;
    return *this;
}

loc loc::operator++() {
    lat++;
    lng++;
    return *this;
}


int main() {
    loc ob1(10,20), ob2(5,30), ob3(90,90);

    ob1.show();
    ob2.show();
    ++ob1;
    ob1.show();

    ob2 = ++ob1;
    ob1.show();
    ob2.show();

    ob1 = ob2 = ob3;
    ob1.show();
    ob2.show();
    return 0;
}
