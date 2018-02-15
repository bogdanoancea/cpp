#include <iostream>

using namespace std;

int fib_iter(int n) {
	int f1=1, f2=1, fn=1, i;
	if(n==0 || n==1)
		return 1;
	for(i=2;i<=n;i++) {
		fn=f1+f2;
		f2=f1;
		f1=fn;
	}
	return fn;
}

int fib_r(int n) {
	if( n== 0 || n==1)
		return 1;
	return fib_r(n-2) + fib_r(n-1);
}



int main()
{
    int n = 12;
    printf("finacii iterativ: %d\n", fib_iter(n));
    printf("finacii recursiv: %d\n", fib_r(n));

    return 0;
}
