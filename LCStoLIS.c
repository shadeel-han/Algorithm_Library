/*
	Library: Transfer Longest Common Subsequence to Longest Increaing Subsequence
    Algorithm: Dynamic Programming, Binary Search
    Input: two positive integer arrays, no identical element in each array
    Output: the maximum length of common subsequence
    Notice: Instead of munipulating on values, use the appearing index of that number, thus we can find LCS in O(nlogn)
    		If there are identical elements in each arrays, use C++ version LCStoLIS() to record all indices
    		This code is UVa 10635, remeber to modify input/output/code as neccesary
*/

#include <stdio.h>
#include <string.h>

#define MAXN 62501

int sta[MAXN], a[MAXN], b[MAXN];

void Input(int p, int q){   /* change LCS to LIS, no identical element in each array */
	int i, tmp;
	memset(a, -1, sizeof(a));
	for(i=0; i<=p; i++){
		scanf("%d", &tmp);  a[tmp] = i;
	}
	for(i=0; i<=q; i++){
        scanf("%d", &tmp);  b[i] = a[tmp];
	}
}

int BinarySearch(int start, int end, int val){
	int low=start, up=end, mid;
	while( low!=up ){
        mid = (low+up)>>1;
		if( sta[mid] >= val )	up = mid;
		else                    low = mid + 1;
	}
	return low;
}

int Solve(int q){
	int i, num = 0, pos;
	sta[0] = 0;
	for(i=0; i<=q; i++)if( b[i]>0 ){	/* b[i]==-1, b[i] doesn't appear in a */
        if( b[i] > sta[num] ){
			sta[++num] = b[i];
		}else{
            pos = BinarySearch(0, num, b[i]);
            sta[pos] = b[i];
        }
	}
	return num+1;
}

/*int LCStoLIS(vector<int>& s1, vector<int>& s2){
	int a=s1.size(), b=s2.size();
	if( (!a) || (!b) )	return 0;
	
	vector<int> v, p[1001];	// input number between 1~1000
	for(int i=0; i<a; i++)	p[s1[i]].push_back(i);
	
	v.push_back(-1);	// prevent v.back error
	for(int i=0; i<b; i++)
	for(int j=p[s2[i]].size()-1; j>=0; j--){
		int n = p[s2[i]][j];
		if( n > v.back() )	v.push_back(n);
		else				*lower_bound(v.begin(), v.end(), n) = n;
	}
	return v.size()-1;	// subtract the default -1
}*/

int main(void){
    /*freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);*/
	int c=0, cas, n, p, q;
	scanf("%d", &cas);
	while( cas-- ){
		scanf("%d %d %d", &n, &p, &q);
		Input(p,q);
		printf("Case %d: %d\n", ++c, Solve(q));
	}
	return 0;
}
