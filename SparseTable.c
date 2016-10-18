/*
	Library: Sparse Table
    Algorithm: Sparse Table
    Input: range index start and end
    Output: biggest and smallest elements in [start, end] of array
    Notice: Table Construct takes O(nlogn), Query takes O(1)
    		This algorithm is used when n and number of query are large
*/

#include <stdio.h>
#include <math.h>

#define MAX(a,b) ((a>b)?(a):(b))
#define MIN(a,b) ((a<b)?(a):(b))
#define SIZE 50001
#define ROW 17	// row = log(SIZE)/log(2.0) + 2

int large[ROW][SIZE], small[ROW][SIZE];

int main(void){
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int num, que, i, j, k, power[ROW];
	double LOG2 = log(2.0);
	for(i=0,j=1; i<ROW; i++,j<<=1)	power[i] = j;
	
	while( scanf("%d %d", &num, &que)!=EOF ){
		for(i=1; i<=num; i++){
			scanf("%d", &large[0][i]);
			small[0][i] = large[0][i];
		}
		// Table Construct
		for(i=1,j=num-1; j>0; j-=power[i],i++){
			for(k=1; k<=j; k++){
				large[i][k] = MAX(large[i-1][k], large[i-1][k+power[i-1]]);
				small[i][k] = MIN(small[i-1][k], small[i-1][k+power[i-1]]);
			}
		}
		// Query
		for(i=0; i<que; i++){
			scanf("%d %d", &j, &k);
			int h = (int)(log((double)(k-j+1)) / LOG2), tmp = k-power[h]+1;
			printf("In array[%d~%d], Max:%d Min:%d\n", j, k, MAX(large[h][j], large[h][tmp]), MIN(small[h][j],small[h][tmp]));
		}
	}
	
	return 0;
}

