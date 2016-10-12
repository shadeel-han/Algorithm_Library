/*
    Library: Quick sort
    Algorithm: quick sort implementation
    Input: Unsorted integer sequence
    Output: Sorted integer sequence "in"
*/

#include <stdio.h>
#define SIZE 10001

int in[SIZE];

void swap(int a, int b){
	int tmp = in[a];
	in[a] = in[b];	in[b] = tmp;
}

int Partition(int low, int high){
	int i=low+1, j=high;
	while(1){
		for( ; i<=j; i++ )	if(in[i]>=in[low])	break;
		for( ; i<=j; j-- )  if(in[j]<in[low])	break;
		if( i<j )	swap(i,j);
		else{
			swap(low, j);	return j;
			/*	elemets before in[j] are smaller than it
				elemets after in[j] are bigger than it */
		}
	}
}

void QuickSort(int low, int high){
	if( high>low ){
		int k = Partition(low, high);
		QuickSort(low, k-1);
		QuickSort(k+1, high);
	}
}

int main(void){
	int num, i;
    while( scanf("%d", &num)!=EOF ){
        for( i=0; i<num; i++ )	scanf("%d", &in[i]);
        QuickSort(0,num-1);
        for(i=0; i<num; i++)	printf("%d ", in[i]);
    }
	return 0;
}

