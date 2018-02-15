#include <iostream>
#include<stdexcept>
#include<list>

using namespace std;

constexpr double C = 299792.458;


class Container {
public:
    virtual double& operator[](int i) = 0;
    virtual int size() const = 0;
    virtual ~Container(){};
};


void use(Container& c) {
    const int sz = c.size();
    for(auto i=0; i!=sz;++i)
        cout << c[i]<< endl ;
}



class Vector{
public:
    Vector(int size); //: elem {new double[size]}, s{size} {}
    Vector(std::initializer_list<double> lst):elem{new double[lst.size()]}, s{lst.size()}{
        copy(lst.begin(), lst.end(), elem);
    }
    ~Vector() { delete[] elem;}
    double& operator [](int i);//{return elem[i];}
    int size()const {return s;}
    void push_back(double d);
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
    for(auto i = 0; i != size; ++i)
        elem[i] = 0;
    s = size;
}


class Vector_container : public Container {
    Vector v;
public:
    Vector_container(int s): v(s) {}
    Vector_container(std::initializer_list<double> lst): v(lst) {} //in carte nu e constructorul asta si functia go merge!!!
    ~Vector_container() {}

    double& operator[](int i) { return v[i];}
    int size() const {return v.size();}

};


class List_container : public Container {
    list<double> l;
public:
    List_container() {}
    List_container(std::initializer_list<double> lst): l(lst) {} //in carte nu e constructorul asta si functia go merge!!!
    ~List_container() {}

    double& operator[](int i) {
        for(auto& x: l){
            if(i==0)
                return x;
            --i;
        }
            throw out_of_range("List container");
    }

    int size() const {return l.size();}

};


void go(){
    Vector_container vc{10,9,8,7,6,5,4,3,2,1,0};
    use(vc);
}


void h(){
    List_container lc{1,2,3,4,5,6,7,8,9};
    use(lc);
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

    //cout << read_and_sum(3);
    go();
    h();
    return 0;
}
