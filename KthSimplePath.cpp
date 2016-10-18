/*
	Library: Kth Simple Path (Kth shortest path with no two identical nodes)
    Algorithm: DFS-based A* search
    Input: edge connection and K
    Output: the length of Kth simple shortest path "CostSum" and one feasible path
    Notice: Assume that path s->t exists
    		K should not exceed the maximum number of possible path
*/

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

class KthSimple{
	public:
		#define MAXN 1001
		struct EDGE{
    		int to, c;
    		EDGE() {};
    		EDGE(int a, int b):to(a),c(b) {};
		};
		
		vector<EDGE> edge[MAXN];
		int Vnum, Enum, Kth, CostSum, mindis[MAXN], Source, Target, walk[MAXN];
		int path[MAXN];	// Find_Path() to get one feasible path
		
	public:
		void Initial(void){
			for(int i=0; i<=Vnum; i++)	edge[i].clear();
			memset(mindis, 127, sizeof(mindis));
			memset(walk, 0, sizeof(walk));
			memset(path, -1, sizeof(path));
			CostSum = 0;
		}
		
		void Edge_Build(int a, int b, int c){
			edge[a].push_back(EDGE(b, c));
			edge[b].push_back(EDGE(a, c));	// default bidirectional
			CostSum += c;
		}
		
		/* Here calculate the mindis from "Target" to every other nodes for DFS prune condition
			if path is one-way, be sure to modify the edge */
		void RunSPFA(void){	// you can choose any shorest path algorithm as you like
			int inqueue[MAXN]={0}, now, next;
			queue<int> que;	que.push(Target);

			mindis[Target] = 0;	inqueue[Target] = 1; 
			while( !que.empty() ){
				now = que.front();	que.pop();	inqueue[now] = 0;
				for(int i=0, j=edge[now].size(); i<j; i++){
					next = edge[now][i].to;
					if( mindis[next] > mindis[now] + edge[now][i].c ){
						mindis[next] = mindis[now] + edge[now][i].c;
						if( !inqueue[next] )
							que.push(next), inqueue[next] = 1;
					}
				}
			}
		}
		
		void BinarySearch_KthCost(void){
			int cost_up = CostSum, cost_low = 1, now_cost;
			walk[Source] = 1;
			do{
				CostSum = 0;
				now_cost = (cost_up+cost_low)>>1;
				DFS_Search(Source, now_cost, 0);
				if( CostSum>=Kth )	cost_up = now_cost;	// if there are exactly k paths whose cost<=now_cost, try lower cost
				else				cost_low = now_cost + 1;
			}while(cost_up > cost_low);
			CostSum = cost_up;	// the length of Kth shortest path
		}
		
		void DFS_Search(int s, int limit, int now_cost){
			if( now_cost + mindis[s] > limit )	return;	// prune condition
			for(int i=0,j=edge[s].size(); i<j && CostSum<=Kth; i++){
				int next = edge[s][i].to, new_cost = now_cost+edge[s][i].c;
				if( next == Target ){
					if( new_cost <= limit )	CostSum++;
					continue;
				}
				if( walk[next] || (new_cost>=limit) )	continue;
				
				walk[next] = 1;
				DFS_Search(next, limit, new_cost);
				walk[next] = 0;
			}
		}
		
		bool Find_Path(int s, int now_cost, int index){
			if( now_cost + mindis[s] > CostSum )	return false;	// prune condition
			for(int i=0,j=edge[s].size(); i<j; i++){
				int next = edge[s][i].to, new_cost = now_cost+edge[s][i].c;
				path[index] = next;
				if( next == Target ){
					if( new_cost == CostSum )	return true;
					else						continue;
				}
				if( walk[next] || (new_cost>=CostSum) )	continue;
				
				walk[next] = 1;
				if(Find_Path(next, new_cost, index+1))	return true;
				walk[next] = 0;
			}
			return false;
		}
};

KthSimple my;

int main(void){
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int a, b, c;
	
	while( scanf("%d %d %d", &my.Vnum, &my.Enum, &my.Kth)!=EOF ){
		my.Initial();
		for(int i=0; i<my.Enum; i++){
			scanf("%d %d %d", &a, &b, &c);
			my.Edge_Build(a, b, c);
		}
		scanf("%d %d", &my.Source, &my.Target);
		my.RunSPFA();
		my.BinarySearch_KthCost();
		my.Find_Path(my.Source, 0, 0);
		printf("The length of %dth shortest path is %d.\nPath: %d", my.Kth, my.CostSum, my.Source);
		for(int i=0; my.path[i]!=-1; i++) printf("->%d", my.path[i]);	putchar('\n');
	}
	return 0;
}

/*
	Input example: (K=1~9)
	5 8 K
	1 2 1
	1 3 4
	1 5 8
	5 2 7
	5 3 6
	5 4 2
	3 4 5
	4 2 3
	1 4
	
	Output example:
	The length of 1th shortest path is 4.
	Path: 1->2->4
	The length of 2th shortest path is 9.
	Path: 1->3->4
	The length of 3th shortest path is 10.
	Path: 1->2->5->4
	The length of 4th shortest path is 10.
	Path: 1->2->5->4
	The length of 5th shortest path is 12.
	Path: 1->3->5->4
	The length of 6th shortest path is 18.
	Path: 1->5->2->4
	The length of 7th shortest path is 19.
	Path: 1->2->5->3->4
	The length of 8th shortest path is 19.
	Path: 1->2->5->3->4
	The length of 9th shortest path is 20.
	Path: 1->3->5->2->4
*/

