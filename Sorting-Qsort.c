/*
    Library: Quick sort
    Algorithm: Call quicksort library
    Input: Unsorted integer sequence
    Output: Sorted integer sequence "in"
*/

#include <stdio.h> 
#include <stdlib.h>

#define MAXX 10000

int in[MAXX];

int compare( const void* a, const void* b ){ 
	return ( *(int*)a - *(int*)b );
    // return value <0  => exchange
	// return value >=0 => not exchange
}

int main(){
	int num, i;
	while( scanf("%d", &num)!=EOF ){
        for( i=0; i<num; ++i )	scanf("%d", &in[i]);
        qsort(in, num, sizeof(int), compare);
    }
	return 0; 
}
