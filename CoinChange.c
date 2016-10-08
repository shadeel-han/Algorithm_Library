/*
    Library: Coin Change
    Algorithm: Dynamic Programming
    Input: manually set the kind of coins and dp range
    Output: dp table for possible ways of coin combination
*/

#include <stdio.h>
#define SIZE 10001
#define KIND 5

int coin[KIND] = {1,5,10,25,50}, dp[SIZE];

int main(){
    
    int i, j;
    
    for( i=0; i<SIZE; i++ )
         dp[i] = 1;
    for( i=1; i<KIND; i++ )
         for( j=coin[i]; j<SIZE; j++ )
              dp[j] += dp[j-coin[i]];
    
    while( scanf("%d", &i)!=EOF )
           printf("%d\n", dp[i]);
    
    return 0;
}

