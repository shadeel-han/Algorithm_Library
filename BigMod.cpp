/*
    Library: BigMod
    Algorithm: Recursive
    Input: base a, exponent b, mod c
    Output: (a^b)%c
*/

#include <cstdio>

#define SQ(x) (x*x)

using namespace std;

int bigmod(int a, int b, int c, int d){
    if( !b )        return 1%c;
    else if( b&1 )  return (d*bigmod(a,b-1,c,d))%c;
    else            return SQ(bigmod(a,b>>1,c,d))%c;
}

int main(){
    int base, exp, mod, one;
    while( scanf("%d%d%d", &base, &exp, &mod)!=EOF ){
            printf("%d\n", bigmod(base,exp,mod,base%mod));
    }
    return 0;
}
