/*
    Library: MergeSort
    Algorithm: Divide and Conquer
    Input: Unsorted integer sequence
    Output: Sorted integer sequence "in"
*/

#include <stdio.h>

#define MAXX 10000

int in[MAXX], b[MAXX];

void merge( int low, int high, int mid ){ 	
    int i, j, k;
    for( k=0,i=low,j=mid+1; i<=mid && j<=high; k++ ){
        if( in[i]<=in[j] )  b[k] = in[i++];  
        else                b[k] = in[j++];
    }
	if( j>high )
    for( k=mid; k>=i; k-- )
        in[--j] = in[k];
    for( i=low,k=0; i<j; i++,k++ )
        in[i] = b[k];
} 

void mergeSort( int low, int high ){
    if( high>low ){
        int k=(low+high)>>1;
        mergeSort( low, k );
        mergeSort( k+1, high );
        merge( low, high, k );
    }
}

int main(){
    int num, i;
    while( scanf("%d", &num)!=EOF ){
        for( i=0; i<num; i++ )	scanf("%d", &in[i]);
        mergeSort(0,num-1);
        for(i=0; i<num; i++)	printf("%d ", in[i]);
    }
    return 0;
}
