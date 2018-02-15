#include <iostream>
#include<stdexcept>
using namespace std;

constexpr double C = 299792.458;

class Vector {
public:
    Vector(int size); //: elem {new double[size]}, s{size} {}
    double& operator [](int i);//{return elem[i];}
    int size(){return s;}
private:
    int s;
    double *elem;
};


double& Vector::operator[](int i) {
    if(i < 0 || i >= size())
        throw out_of_range{"Vector::operator[]"};
    return elem[i];
}

Vector::Vector(int size) {
    if(size <0)
        throw length_error{"negative size"};
    elem = new double[size];
    s = size;
}


double read_and_sum(int s) {
    Vector v(s);
    for(auto i = 0; i < v.size(); ++i)
        cin >> v[i];

    double sum = 0;
    for(auto i = 0 ; i < v.size(); ++i)
        sum+=v[i];

    return sum;

}

void f(double speed) {
    const double local_max = 160.0/(60*60);
    //static_assert(speed<C, "to fast");
    static_assert(local_max<C, "to fast too");
}



int main()
{
    //Vector v(6);
    //cout << "Hello world!" << v[0] << endl;

    cout << read_and_sum(3);
    return 0;
}
