#include<math.h>
#include<stdio.h>


long combinari(long n,long k) {
  long s1 = 0;
  long s2 = 0;
  int i;
  for(i=1; i<= n-k+1; i++)
    s1+=log(i);

  for(i=1; i <= k; i++)
    s2+=log(i);

  return exp(s1-s2);
}

long EMAD(long N){
  long s = 0;
  int j, k;
  double pk;
  for(k=10; k<=99; k++) {
    pk = log10(1+1/k);
    for(j=0; j<= N; j++) {
      s += combinari(N,j)*pow(pk, (double)j) * pow((1-pk), (double)(N-j)) * abs(j/N - pk)/90;
    }
  }
  return s;
}

int main() {
    printf("%ld", EMAD(3000));
    return 0;
}
