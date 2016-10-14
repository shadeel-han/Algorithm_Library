/*
	Library: Longest Increaing Subsequence
    Algorithm: Dynamic Programming, Binary Search
    Input: integer array
    Output: the maximum length of increasing subsequence
    Notice: Use binary search to achieve time complexity O(nlogn) for LIS
			This code is UVa 231, remeber to modify input/output/code as neccesary
			C++ can use lower_bound() in <algorithm> to replace BinarySearch()
    		Add some arrays to record the path if you want to list feasible solution
*/

#include <stdio.h>

int seq[1000001];

int BinarySearch(int start, int end, int val){
	int low=start, up=end, mid;
	while( low!=up ){
        mid = (low+up)>>1;
		if( val > seq[mid] )	up = mid;
		else                    low = mid + 1;
	}
	return low;
}

int main(void){
    /*freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);*/
	int n, c=0, num, pos;
	while( scanf("%d", &seq[0]) && seq[0]!=-1){
		num = 1;
		while( scanf("%d", &n) && n!=-1 ){
            pos = BinarySearch(0, num, n);
            if( pos==num )  seq[num++] = n;
            else            seq[pos] = n;
		}
		if( c++ )   putchar('\n');
		printf("Test #%d:\n  maximum possible interceptions: %d\n", c, num);
	}
	return 0;
}
