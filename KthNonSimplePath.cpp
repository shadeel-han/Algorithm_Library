/*
	Library: Kth NonSimple Path (Kth shortest path with possible identical nodes)
    Algorithm: Priority_Queue-based A* search
    Input: edge connection and K
    Output: the length of Kth non-simple shortest path
    Notice: Assume that path s->t exists
    		Since possible identical nodes on path, K is no limit.
*/

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

class KthNonSimple{
	public:
		#define MAXN 1001
		struct EDGE{
    		int to, c, sort_c;
    		EDGE() {};
    		EDGE(int a, int b, int c):to(a),c(b),sort_c(c) {};
    		bool operator < (const EDGE &k) const{	// priority min-que
				return (sort_c > k.sort_c);
			}
		};
		
		vector<EDGE> edge[MAXN];
		int Vnum, Enum, Kth, mindis[MAXN], Source, Target;
		
	public:
		void Initial(void){
			for(int i=0; i<=Vnum; i++)	edge[i].clear();
			memset(mindis, 0x7F, sizeof(mindis));
		}
		
		void Edge_Build(int a, int b, int c){
			edge[a].push_back(EDGE(b, c, 0));
			edge[b].push_back(EDGE(a, c, 0));	// default bidirectional
		}
		
		/* Here calculate the mindis from "Target" to every other nodes for priority_queue
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
		
		int Astar(void){
			if( mindis[Source]==0x7F7F7F7F )	return -1;	// path doesn't exist
			int kth = (Source==Target)?(Kth+1):(Kth);		// if source==target, k+1
			
			priority_queue<EDGE> que;	que.push(EDGE(Source, 0, mindis[Source]));
			int passtime[MAXN] = {0};
			while( !que.empty() ){
				EDGE now = que.top(); que.pop();
				++passtime[now.to];
				if( passtime[Target]==kth )	return now.c;	// Passing Target k times means we find kth path, cost is guaranteed by priority queue
				if( passtime[now.to]>kth )	continue;		// On kth shortest path, it's impossible that a node appears over k times
				for(int i=0,j=edge[now.to].size(); i<j; i++){
					int next = edge[now.to][i].to;
					que.push(EDGE(next, now.c+edge[now.to][i].c, now.c+edge[now.to][i].c+mindis[next]));
				}
			}
			return -1;
		}
};

KthNonSimple my;

int main(void){
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int a, b, c;
	
	while( scanf("%d %d %d", &my.Vnum, &my.Enum, &my.Kth)!=EOF ){
		my.Initial();
		for(int i=0; i<my.Enum; i++){
			scanf("%d %d %d", &a, &b, &c);
			my.Edge_Build(a, b, c);
		}
		scanf("%d %d", &my.Source, &my.Target);
		my.RunSPFA();
		printf("The length of %dth shortest path is %d.\n", my.Kth, my.Astar());
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
	The length of 2th shortest path is 6.
	The length of 3th shortest path is 8.
	The length of 4th shortest path is 8.
	The length of 5th shortest path is 9.
	The length of 6th shortest path is 10.
	The length of 7th shortest path is 10.
	The length of 8th shortest path is 10.
	The length of 9th shortest path is 10.
*/

