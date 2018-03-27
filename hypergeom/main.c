#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define SUCCESS 0
#define NO_CONV 1
#define OVERFLOW_ERR 2

double hyp_taylor_a(double a, double b, double z, double tol, int* error) {

    double a1 = 1;
    double b1 = 1;
    int j;
    for(j = 0; j < 500; ++j) {
        a1 *= (a+j)/(b+j) * z/(j+1);
        b1 += a1;
        if (fabs(a1)/fabs(b1) < tol )
            break;
    }
    if(j == 499) {
        *error = NO_CONV;
    }
    return b1;

}

double hyp_taylor_b(double a, double b, double z, double tol, int* error) {
    double r[500];
    double A[500];
    int j;

    for(j = 0; j < 500 ; ++j) {
     r[j] = A[j] = 0;
    }

    r[0] = a/b;
    r[1] = (a+1)/2/(b+1);

    A[0] = 1 + z * r[0];
    A[1] = A[0] + (z^2.0)*a/b*r[1];

    for(j =2; j < 500; ++j) {
        r[j] = (a+j)/(j+1)/(b+j);
        A[j] = A[j-1] + (A[j-1]-A[j-2])*r[j]*z;
        if( fabs(A[j]-A[j-1])/fabs(A[j-1]) < tol && fabs(A[j-1]-A[j-2])/fabs(A[j-2])<tol )
            break;
    }
    if(j == 499) {
         *error = NO_CONV;
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
            *error = OVERFLOW;
            break;
        }
        d1[j] = (a1[j]+b1[j])/c1[j];
        if( fabs(d1[j]-d1[j-1])/fabs(d1[j-1]) < tol && fbas(d1[j-1]-d1[j-2])/fabs(d1[j-2]) < tol )
            break;

    }
    if( j == 499) {
        *error = NO_CONV;
    }

    return d1[j];
}

int main()
{
    int error = NO_ERR;
    double tol = 1e-8;
    double i ,j, k;
    FILE* f = fopen("taylor_a.txt", "w");
    for(i = 0.1; i < 180; i += 0.5)
        for(j = 0.1; j < 180; j += 0.5)
            for(k = 0.1; k < 180; k += 0.5) {
                double res = hyp_taylor_a(i, j, k, tol, &error);
                if(error == NO_ERR)
                   fprintf(f,"%g, %g, %g, %g\n", i, j, k, res);
                else
                    fprintf(f,"%g, %g, %g, %g\n", i, j, k, -1);

            }
    fclose(f);
    return 0;
}

