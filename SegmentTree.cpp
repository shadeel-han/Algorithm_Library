/*
	Library: Segment Tree
    Algorithm: Segment Tree, a Binary_Tree-based algorithm
    Input: initial data array(, maybe some modification), query in array[start, end]
    Output: query values
    Notice: Tree construction takes O(n)
    		Modification and Query takes O(logn)
    		This algorithm is used when n and number of modify and query are large
    		Applications of segment tree vary widely, queries about min/max, summation or even accumulation 
				in any range can use this algorithm to solve. Therefore, you should revise ModifyTree() and 
				FindValue() according to your usage, this code is only for searching min/max
*/

#include <cstdio>
#include <algorithm>

using namespace std;
struct NODE{
	int beg, end, maxv, minv;
	NODE() {};
	NODE(int a, int b):maxv(a),minv(b) {};
};

class SegTree{
	public:
		#define INF 1000000000
		#define MAXN 100001
		/*struct NODE{
			int beg, end, maxv, minv;
			NODE() {};
			NODE(int a, int b):maxv(a),minv(b) {};
		};*/
		
		NODE tree[3*MAXN];	// because of binary tree, *3 is for safety of boundary
		int in[MAXN], Vnum;
		
	public:
		void CreateTree(int id, int beg, int end){
			tree[id].beg = beg;	// the beginning index of this tree node
			tree[id].end = end;	// the ending index of this tree node
			if( beg == end ){	// arrive leaf node
				tree[id].maxv = tree[id].minv = in[beg];
				return;
			}
			int mid = (beg+end)>>1, next = id<<1;	// if not leaf node
			CreateTree(next, beg, mid);				// left child binary tree
			CreateTree(next+1, mid+1, end);			// right child binary tree
			tree[id].maxv = max(tree[next].maxv, tree[next+1].maxv);
			tree[id].minv = min(tree[next].minv, tree[next+1].minv);
		}
		
		void ModifyTree(int id, int pos, int value){
			// the target position is not in the range of this tree node
			if( (tree[id].beg>pos) || (tree[id].end<pos) )	return;
			// arrive the target position
			if( tree[id].beg == tree[id].end ){
				tree[id].maxv = tree[id].minv = value;
				return;
			}
			// not yet arrive
			int next = id<<1;
			ModifyTree(next, pos, value);
			ModifyTree(next+1, pos, value);
			tree[id].maxv = max(tree[next].maxv, tree[next+1].maxv);
			tree[id].minv = min(tree[next].minv, tree[next+1].minv);
		}
		
		NODE FindValue(int id, int beg, int end){
			// this tree node doesn't overlap the query range
			if( (tree[id].beg>end) || (tree[id].end<beg) )		return NODE(-INF,INF);
			// this tree node is completely inside the query range
			if( (beg<=tree[id].beg) && (tree[id].end<=end) )	return tree[id];
			// this tree node partly overlaps the query range
			NODE left = FindValue(id<<1, beg, end);
			NODE right = FindValue((id<<1)+1, beg, end);
			return NODE(max(left.maxv, right.maxv), min(left.minv, right.minv));
		}
};

SegTree my;

int main(void){
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int q, a, b;
	
	while( scanf("%d %d", &my.Vnum, &q)!=EOF ){
		// data should store from index 1
		for(int i=1; i<=my.Vnum; i++)	scanf("%d", &my.in[i]);
		// tree construct, these arguments are always like this ones
		my.CreateTree(1, 1, my.Vnum);
		for(int i=0; i<q; i++){
			scanf("%d %d", &a, &b);
			// tree search, first argument is always 1
			NODE tmp = my.FindValue(1, a, b);
			printf("In array[%d~%d], Max:%d Min:%d\n", a, b, tmp.maxv, tmp.minv);
		}
	}
	return 0;
}

