/*
    Library: Prime
    Algorithm: Naiive brute force
    Input: no
    Output: boolean table "isprime", prime numbers in "prime", primenum is the total
*/

#include <cstdio>
#include <cstring>

#define MAXX 1000001

using namespace std;

bool isprime[MAXX];
int prime[MAXX/4];   // according to MAXX to change

int main(){
    
    int i, j, in, primenum=2;
    memset(isprime,true,sizeof(isprime));
    isprime[1] = false;
    // delete the even number
    for( i=4; i<MAXX; i+=2 )
         isprime[i] = false;
    prime[1] = 2;
    for( i=3; i<MAXX; i+=2 )
        if( isprime[i] ){
            // delete the multiple of the prime
            for( j=i<<1; j<MAXX; j+=i )
                isprime[j] = false;
            prime[primenum++] = i;
        }

    while( scanf("%d", &in) ){
           if( in==-1 )
               break;
           printf("%d\n", prime[in]);
    }
    return 0;
}

