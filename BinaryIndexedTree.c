/*
	Library: Binary Indexed Tree
    Algorithm: Lowbit_Value-based algorithm
    Input: initial data array(, maybe some modification), query in array[start, end]
    Output: query summantion values
    Notice: Modification and Query takes O(logn)
    		This algorithm is similar to Segment Tree but there's a difference: GetSum() returns the summantion value 
			in index 1~n. If ask the summation in range[start,end], you need to do GetSum(end)-GetSum(start-1).
    		
*/

#include <stdio.h>
#include <string.h>
#define SIZE 10001

int s[SIZE], maxsize;

int lowbit( int in ){	/* 1 2 3 4 5 6 7 8 */
    return in&(-in);	/* 1 2 1 4 1 2 1 8 */
}

/* 1D version */
int GetSum( int index ){
	int sum = 0;
	while( index>0 )
	{
		sum += s[index];
		index -= lowbit(index);
	}
	return sum;
}

/* 2D version 
int GetSum( int x, int y ){
	int sum = 0, i, j;
	for( i=x; i>0; i-=lowbit[i] )
       for( j=y; j>0; j-=lowbit[j] )
	       sum += s[i][j];
	return ans;
}*/

/* 1D version */
void Change( int index, int data ){
	int i;
	for( i=index; i<=maxsize; i+=lowbit(i) )
		s[i] += data;
}

/* 2D version 
void change ( int x, int y, int data ){
	int i, j;
	for( i=x; i<=maxsize; i+=lowbit[i] )
	    for( j=y; j<=maxsize; j+=lowbit[j] )
	       s[i][j] += data;
}*/

int main(){
    freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
    int i, j, num, in, q;

    while( scanf("%d %d %d", &num, &maxsize, &q)!=EOF ){
        // Initial
        memset(s,0,sizeof(s));
        // Input array
        for( i=0; i<num; ++i ){
            scanf("%d", &in);
            Change(in, 1);
        }
        // Query
        while( q-- ){
        	scanf("%d %d", &i, &j);
        	printf("The total number of integers %d~%d is %d.\n", i, j, GetSum(j)-GetSum(i-1));
		}
    }
    return 0;
}

/*
	Input example:
	10 8 3				// array with 10 elements, largest number 8, 3 query
	1 6 5 4 2 3 1 8 4 7	// array input
	1 8					// query
	2 3
	4 7

	Output example:
	The total number of integers 1~8 is 10.
	The total number of integers 2~3 is 2.
	The total number of integers 4~7 is 5.
*/



