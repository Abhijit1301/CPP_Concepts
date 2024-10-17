#include <iostream>

int main(int argc , char *argv[])
{
    printf("%c",**++argv);

	const int N = 10, M = 20;
	int *x[N] = (int*)malloc(M*sizeof(*x));
    printf("%d %d",sizeof(x),sizeof(*x));
}