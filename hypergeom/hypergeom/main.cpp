//
//  main.cpp
//  hypergeom
//
//  Created by Bogdan Oancea on 27/03/2018.
//  Copyright © 2018 Bogdan Oancea. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <climits>
#include <vector>
using namespace std;

#define SUCCESS 0
#define NO_CONVERGENCE 1
#define OVERFLOW_ERROR 2
#define PARAM_TOO_LARGE_ERROR 3



double hyp_asymtotic_a(double a, double b, double z, double tol, int* error) {
    double a1 = 1;
    double b1 = 1;
    double res;
    int j;
    for(j = 0; j < 1000; ++j) {
        a1 *= (b-a+j)*(-a+j+1)/(j+1)/z;
        b1 += a1;
        if( fabs(a1)/fabs(b1) <tol )
            break;
    }
    if( j == 1000 ) {
        *error = NO_CONVERGENCE;
    }
    res = exp(z + (a-b)* log(z) + log(b1) + lgamma(b) - lgamma (a));
    if(res == INFINITY || res == NAN)
        *error = OVERFLOW_ERROR;

    return res;
}


double hyp_asymtotic_b(double a, double b, double z, double tol, int* error) {
    double r[1000]{0};
    double A[1000]{0};
    int j;
    
    r[0] = (b-a) * (1-a);
    r[1] = (b-a+1) * (2-a)/2;
    
    A[0] = 1 + r[0] / z;
    A[1] = A[0] + r[0] * r[1] / (z * z);
    
    for (j = 2; j < 1000; ++j) {
        r[j] = (b-a+j) * (j+1-a) / (j+1);
        A[j] = A[j-1] + ( A[j-1]- A[j-2]) * r[j] / z;
        if (  fabs(A[j]-A[j-1])/fabs(A[j-1]) < tol && fabs(A[j-1]- A[j-2])/fabs(A[j-1]) < tol )
            break;
    }
    if( j == 1000 ) {
        *error = NO_CONVERGENCE;
    }
    double res = exp(z + (a-b)* log(z) + log(A[j]) + lgamma(b) - lgamma (a));
    if(res == INFINITY || res == NAN)
        *error = OVERFLOW_ERROR;
    
    return res;
}


double hyp_taylor_a(double a, double b, double z, double tol, int* error) {
    
    double a1 = 1;
    double b1 = 1;
    int j;
    for(j = 0; j < 1000; ++j) {
        a1 *= (a+j)/(b+j) * z/(j+1);
        b1 += a1;
        if (fabs(a1)/fabs(b1) < tol )
            break;
    }
    if(j == 1000) {
        *error = NO_CONVERGENCE;
    }
    if(b1 == INFINITY || b1 == NAN)
        *error = OVERFLOW_ERROR;
    
    return b1;
}

double hyp_taylor_b(double a, double b, double z, double tol, int* error) {
    double r[1000]{0};
    double A[1000]{0};
    int j;
    double res;

    
    r[0] = a/b;
    r[1] = (a+1)/2/(b+1);
    
    A[0] = 1 + z * r[0];
    A[1] = A[0] + (z*z)*a/b*r[1];
    
    for(j = 2; j < 1000; ++j) {
        r[j] = (a+j)/(j+1)/(b+j);
        A[j] = A[j-1] + (A[j-1]-A[j-2])*r[j]*z;
        if( fabs(A[j]-A[j-1])/fabs(A[j-1]) < tol && fabs(A[j-1]-A[j-2])/fabs(A[j-2])<tol )
            break;
    }
    
    if(j == 1000) {
        *error = NO_CONVERGENCE;
        res = A[j-1];
    }
    else {
        if(A[j] == INFINITY || A[j] == NAN)
            *error = OVERFLOW_ERROR;
        res = A[j];
    }
    return res;
}


double hyp_singlefrac(double a, double b, double z, double tol, int* error) {
    double a1[500];
    double b1[500];
    double c1[500];
    double d1[500];
    int j;
    
    a1[0] = 0;
    a1[1] = b;
    b1[0] = 1;
    b1[1] = a*z;
    c1[0] = 1;
    c1[1] = b;
    d1[0] = 1;
    d1[1] = (b+a*z)/b;
    
    for(j = 2; j < 500; ++j) {
        
        a1[j] = (a1[j-1]+b1[j-1])*(j)* (b+j-1);
        b1[j] = b1[j-1]*(a+j-1)*z;
        c1[j] = c1[j-1]*j*(b+j-1);
        
        if( (a1[j] == INFINITY) || (b1[j] == INFINITY) || (c1[j] == INFINITY ) ) {
            *error = OVERFLOW_ERROR;
            break;
        }
        d1[j] = (a1[j]+b1[j])/c1[j];
        if( fabs(d1[j]-d1[j-1])/fabs(d1[j-1]) < tol && fabs(d1[j-1]-d1[j-2])/fabs(d1[j-2]) < tol )
            break;
        
    }
    if( j == 499) {
        *error = NO_CONVERGENCE;
    }
    
    return d1[j];
}


double hyp_rec_olver0p(double a, double b, int k, double z, double tol, int* error) {
    
    double f0 = tgamma(b-a)/tgamma(b)*hyp_taylor_a(a, b, z, tol, error);
    cout << f0 << endl;
    //Apply recurrences to obtain stopping condition
    double p[1000] {0}, r[1000] {0};
    int j, N;
    p[0] = 1;
    p[1] = 1+b/z;
    r[0] = (b-a)/z;
    r[1] = (b-a)*(b-a+1)/(z*z);
    
    double maxpj = 0;
    for(j = 1; j < 1000; j++) {
        p[j+1] = -(b-a+j)*p[j-1]/z+(b+j+z)*p[j]/z;
        r[j+1] = (b-a+j+1)*r[j]/z;
        maxpj = max(maxpj,abs(p[j-1]));
        cout << p[j] << " " << p[j+1] << "  " << r[j] << " " << maxpj << " " << endl;
        if (fabs( r[j]/(p[j]*p[j+1])) * maxpj < tol)
            break;
    }
    
    //Set condition on application of algorithm
    N = j-1;
    if (k >= N)
        *error = PARAM_TOO_LARGE_ERROR;
    
    cout << " N=" << N << endl;
    //Apply back substitution
    double f[1000] {0};
    f[N-1] = r[N-1]/p[N];
    for( j = N-2; j >= k; --j) {
        f[j] = (r[j]+p[j]*f[j+1])/p[j+1];
        cout << j << " " << f[j] << endl;
    }
    
    //Return solution
    return (f[k]/tgamma(b-a+k));
}


double hyp_rec_miller0p(double a, double b, int k, double z, double tol, int* error) {
    
    int n = k*1000;
    double* f = new double[k+1]();
    double* v = new double[n+1]();
    double* a1 = new double[n-1]();
    double* b1 = new double[n-1]();
    int i, j, t;
    
    for( i = 0; i < n-1; i++) {
        a1[i] = (b+i-a)/z;
        b1[i] = -(b+i)/z-1;
    }
    double f0 = tgamma(b-a) * hyp_taylor_a(a,b,z, tol, error)/tgamma(b);
    v[n] = 0;
    v[n-1] = 1;
    for(j = 2; j <= n; j++) {
        v[n-j] = - (v[n+2-j] + b1[n-j]*v[n+1-j])/a1[n-j];
    }
    for(t = 0; t <= k; t++) {
        f[t] = f0/v[0]*v[t]*tgamma(b+t)/tgamma(b+t-a);
    }
    return f[k];
}

int main()
{
    int error1, error2, error3, error4, error5;
    double tol = 1e-16;
    
    ofstream output;
    output.open ("hyp_taylor_a.txt", ios::out | ios::app);
    output << std::setw(26);
    std::vector<double> a(400);
    std::vector<double> b(400);
    std::vector<double> z(400);
    
    std::generate(a.begin(), a.begin()+9, [] {
        static double i = 0;
        return i+=0.1;
    });
    std::generate(a.begin()+9, a.end(), [] {
        static double i = 1;
        return i+=0.5;
    });

    std::generate(b.begin(), b.begin()+9, [] {
        static double i = 0;
        return i+=0.1;
    });
    std::generate(b.begin()+9, b.end(), [] {
        static double i = 1;
        return i+=0.5;
    });
    
    std::generate(z.begin(), z.begin()+9, [] {
        static double i = 0;
        return i+=0.1;
    });
    std::generate(z.begin()+9, z.end(), [] {
        static double i = 1;
        return i+=0.5;
    });
    
    for(auto ia:a)
    {
        cout << ia<< endl;
    }
    
    for(auto i:a)
        for(auto j:b)
            for(auto k:z) {
                error1 = SUCCESS;
                double res1 = hyp_taylor_a(i, j, k, tol, &error1);
                if(error1 != SUCCESS)
                    res1 = -1;
                error2 = SUCCESS;
                double res2 = hyp_taylor_b(i, j, k, tol, &error2);
                if(error2 != SUCCESS)
                    res2 = -1;
                error3 = SUCCESS;
                double res3 = hyp_singlefrac(i, j, k, tol, &error3);
                if(error3 != SUCCESS)
                    res3 = -1;
                error4 = SUCCESS;
                double res4 = hyp_asymtotic_a(i, j, k, tol, &error4);
                if(error4 != SUCCESS)
                    res4 = -1;
                error5 = SUCCESS;
                double res5 = hyp_asymtotic_b(i, j, k, tol, &error5);
                if(error5 != SUCCESS)
                    res5 = -1;
                output << setprecision(22);
                output << setw(4) << i << '\t' <<setw(4)<< j << '\t' <<setw(4)<< k << '\t' <<setw(22)<< res1 << '\t' << error1 << '\t' <<setw(22) << res2 << '\t' << error2 << '\t' <<setw(22)<< res3 << '\t' <<error3 << '\t' <<setw(22)<< res4 << '\t' << error4 << '\t' <<setw(22)<< res5 << '\t' << error5 << endl;
            }
    output.close();
    return 0;
}
