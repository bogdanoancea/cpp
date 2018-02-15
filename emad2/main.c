#include<math.h>
#include<stdio.h>
#include<float.h>

long double combinari(long n,long k) {
   double s1 = 0;
   double s2 = 0;
  int i;
  for(i= n-k+1;i <=n;  i++)
    s1+=( double)log((double)i);

  for(i=1; i <= k; i++)
    s2+=( double)log((double)i);

  printf("%f %f\n", s1 ,s2);
  long double res = expl(s1-s2);
  return res;
}

long double absd(long double d) {
    return d >=0 ? d : -d;
}

long double EMAD(long N){
  long double s = 0;
  int j, k;
  long double pk;
  for(k = 10; k<=99; k++) {
    pk = log10(1+1./(long double)k);
    //printf("%d %lf\n", k , pk);
    for(j=1; j<= N; j++) {
      //printf("Combinari %d, %d %ld\n", N, j, combinari(N,j));
      s += combinari(N,j)* pow(pk, ( long double)j) * pow((1-pk), (long double)(N-j)) * absd((long double)j/(long double)N - pk)/90.;
      //printf("%d %lf %lf %lf %lf %lf %lf \n", j, s, combinari(N,j), pow(pk, (double)j), pow((1-pk), (double)(N-j)), abs((double)j/(double)N - pk)/90. );
      //getch();
    }
    //printf("%lf\n", s);
  }
  return s;
}

int main() {
    printf("%E", LDBL_MAX);
    //printf("%Lf\n", combinari(3000,300));
    //printf("%lf", EMAD(3000));
     int k = 1;
     double pk = log10(1+1./(double)k);
    // printf("%g\n", (1./3000.));
    //int N =3000;
    //int j = 300;
    //printf("%lf\n", combinari(N,j)* pow(pk, (double)j) * pow((1-pk), (double)(N-j)) * absd((double)j/(double)N - pk)/90.);
    //printf("%lf\n", combinari(N,j));
    //printf("%lf\n", pow(pk, (double)j) );
    //printf("%15.14lf\n", pow((1-pk), (double)(N-j)) );
    //printf("%lf\n", absd((double)j/(double)N - pk)/90.);
    return 0;
}
