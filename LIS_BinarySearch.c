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

/*
	Two reminders of binary search
	(1) The argument end=(size or size-1):
		When doing insertion, you should consider the possibility of inserting behind the last elemnt.
	(2) Four combination of A and B:
		The euqality(==) condition is put at A or B. The (+1 at B) or (-1 at A) is chosen.
		for example - array[7] = 1, 3, 4, 4, 4, 8, 9, val = 4
		According to your action(find_min, find_max or insertion), you should choose appropriate format of A and B.
*/

int BinarySearch(int start, int end, int val){
	int low=start, up=end, mid;
	while( low!=up ){
        mid = (low+up)>>1;
		if( val > seq[mid] )	up = mid;		/* A */
		else                    low = mid + 1;	/* B */
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
