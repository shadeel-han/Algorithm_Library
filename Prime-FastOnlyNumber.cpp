/*
    Library: FastPrime
    Algorithm: Naiive brute force without calculating even number
    Input: no
    Output: prime numbers in "prime", primenum is the total
*/

#include <cstdio>
#include <cstring>

#define MAXX (1000000/2+1)

using namespace std;

bool isprime[MAXX];
int prime[MAXX/2];   // according to MAXX to change

int main()
{
	int i , j, primenum=2, tmp, in;
	memset(isprime,true,sizeof(isprime));
	prime[1] = 2;
	for( i=1; i<MAXX; i++)
        if( isprime[i] ){
            tmp = (i<<1) + 1;
			for( j=i+tmp; j<MAXX; j+=tmp)
				isprime[j] = false;
			prime[primenum++] = tmp;
        }
	while(scanf("%d",&in)){
		if(in==-1)
			return 0;
		printf("%d\n",prime[in]);
	}
}
