/*
	Library: Minimum spanning tree - Prime
    Algorithm: Prime and Priority Queue
    Input: edge connection
    Output: the weight of MST
*/

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class MST_Kruskal{
	public:
		#define MAXV 1001
		struct EDGE{
			int f, t, w;
			EDGE(){};
			EDGE(int a, int b, int c):f(a),t(b),w(c) {};
			bool operator<(const EDGE &a) const{	// minimum heap for PQ
				return (w>a.w);
			}
		};
		
		vector<EDGE> edge[MAXV], s;
		int Vnum, Enum, cost;
	
	public:
		void Initial(void){
			cost = 0;
			for(int i=0; i<=Vnum; i++)	edge[i].clear();
		}
		
		void Edge_Build(int a, int b, int w){	// default bidirectional
			edge[a].push_back(EDGE(a, b, w));
			edge[b].push_back(EDGE(b, a, w));
		}
		
		bool Run_Prime(void){	// if not connected, return true
			int cnt = Vnum;
			priority_queue<EDGE> pq;	bool walk[MAXV] = {0};
			pq.push(EDGE(1,1,0));	// default start from vertex 1
			while( !pq.empty() && cnt ){
				EDGE now = pq.top();	pq.pop();
				if( walk[now.t] )	continue;
				else				walk[now.t] = true, cnt--, cost+=now.w;
				//printf("%d %d\n", now.f, now.t);
				for(int i=0,j=edge[now.t].size(); i<j; i++)
				if( !walk[edge[now.t][i].t] )	pq.push(edge[now.t][i]);
			}
			return (cnt)?(true):(false);
		}
};

MST_Kruskal my;

int main(void){
    freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int a, b, w;
	
	while( scanf("%d %d", &my.Vnum, &my.Enum )!=EOF ){
		my.Initial();
		for(int i=0; i<my.Enum; i++){
			scanf("%d %d %d", &a, &b, &w);
			my.Edge_Build(a, b, w);
		}
		if( my.Run_Prime() )	puts("Not Connected");
		else					printf("The weight of MST is %d.\n", my.cost);
	}
	return 0;
}


