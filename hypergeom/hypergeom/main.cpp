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
using namespace std;

#define SUCCESS 0
#define NO_CONVERGENCE 1
#define OVERFLOW_ERROR 2


double hyp_rec_miller(double a, double b, double z, double tol, int* error) {
    double ak;

}



double hyp_asymtotic_a(double a, double b, double z, double tol, int* error) {
    double a1 = 1;
    double b1 = 1;
    double res;
    int j;
    for(j = 0; j < 500; ++j) {
        a1 *= (b-a+j)*(-a+j+1)/(j+1)/z;
        b1 += a1;
        if( fabs(a1)/fabs(b1) <tol )
            break;
    }
    if( j == 499 ) {
        *error = NO_CONVERGENCE;
    }
    return exp(z + (a-b)* log(z) + log(b1) + lgamma(b) - lgamma (a));
}


double hyp_asymtotic_b(double a, double b, double z, double tol, int* error) {
    double r[500]{0};
    double A[500]{0};
    int j;

    r[0] = (b-a) * (1-a);
    r[1] = (b-a+1) * (2-a)/2;

    A[0] = 1 + r[0] / z;
    A[1] = A[0] + r[0] * r[1] / (z * z);

    for (j = 2; j < 500; ++j) {
        r[j] = (b-a+j) * (j+1-a) / (j+1);
        A[j] = A[j-1] + ( A[j-1]- A[j-2]) * r[j] / z;
        if (  fabs(A[j]-A[j-1])/fabs(A[j-1]) < tol && fabs(A[j-1]- A[j-2])/fabs(A[j-1]) <tol )
            break;
    }
    if( j == 499 ) {
        *error = NO_CONVERGENCE;
    }

    return exp(z + (a-b)* log(z) + log(A[j]) + lgamma(b) - lgamma (a));
}


double hyp_taylor_a(double a, double b, double z, double tol, int* error) {

    double a1 = 1;
    double b1 = 1;
    int j;
    for(j = 0; j < 500; ++j) {
        a1 *= (a+j)/(b+j) * z /(j+1);
        b1 += a1;
        if (fabs(a1)/fabs(b1) < tol )
            break;
    }
    if(j == 499) {
        *error = NO_CONVERGENCE;
    }
    return b1;

}

double hyp_taylor_b(double a, double b, double z, double tol, int* error) {
    double r[500]{0};
    double A[500]{0};
    int j;

//    for(j = 0; j < 500 ; ++j) {
//        //r[j] = A[j] = 0;
//        //cout << r[j];
//    }

    r[0] = a/b;
    r[1] = (a+1)/2/(b+1);

    A[0] = 1 + z * r[0];
    A[1] = A[0] + (z*z)*a/b*r[1];

    for(j = 2; j < 500; ++j) {
        r[j] = (a+j)/(j+1)/(b+j);
        A[j] = A[j-1] + (A[j-1]-A[j-2])*r[j]*z;
        if( fabs(A[j]-A[j-1])/fabs(A[j-1]) < tol && fabs(A[j-1]-A[j-2])/fabs(A[j-2])<tol )
            break;
    }
    if(j == 499) {
        *error = NO_CONVERGENCE;
    }
    return A[j];
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

int main()
{
    int error1,error2, error3, error4, error5;
    double tol = 1e-8;
    double i ,j, k;

    //FILE* f = fopen("taylor_a.txt", "w");
    ofstream output;
    output.open ("hyp_taylor_a.txt", ios::out | ios::app);
    output << std::setw(22);

    for(i = 0.1; i < 180; i += 0.5)
        for(j = 0.1; j < 180; j += 0.5)
            for(k = 0.1; k < 180; k += 0.5) {
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
                output << setprecision(14);
                output << setw(4) << i << '\t' <<setw(4)<< j << '\t' <<setw(4)<< k << '\t' <<setw(16)<< res1 << '\t' << error1 << '\t' <<setw(16) << res2 << '\t' << error2 << '\t' <<setw(16)<< res3 << '\t' << error3 << '\t' <<setw(16)<< res4 << '\t' << error4 << '\t' <<setw(16)<< res5 << '\t' << error5 << endl;
            }
    output.close();
    return 0;
}
