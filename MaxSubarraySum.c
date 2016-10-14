/*
	Library: Maximum Subarray Sum
    Algorithm: Dynamic Programming
    Input: n-by-n integer array
    Output: the maximum sum of subarray
    Notice: Time complexity 2D: O(n^3), 3D: O(n^5)
    		This code is UVa 108, remeber to modify input/output/code as neccesary
*/

#include <stdio.h>
#include <string.h>
#define MAXN 100

int arr[MAXN][MAXN];

void Input(int n){
	int i, j;
	for(i=0; i<n; i++)for(j=0; j<n; j++)
	    scanf("%d", &arr[i][j]);
}

int OneDMax(int n, int s[MAXN]){
	int i, sum=0, maxx=-200;
	for(i=0; i<n; ++i){
		sum += s[i];
		if(sum < s[i])	sum = s[i];
		if(sum > maxx)	maxx = sum;
	}
	return maxx;
}

int Solve(int n){
	int i, j, k, s[MAXN], ans=-200, tmp;
	for(i=0; i<n; i++){
        memset(s, 0, sizeof(s));
		for(j=i; j<n; j++){
			for(k=0; k<n; k++)	s[k] += arr[j][k];
			tmp = OneDMax(n, s);
			if( ans < tmp ) ans = tmp;
		}
	}
	return ans;
}

int main(void){
    /*freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);*/
	int n;
	while( scanf("%d", &n)!=EOF ){
		Input(n);
		printf("%d\n", Solve(n));
	}

	return 0;
}
