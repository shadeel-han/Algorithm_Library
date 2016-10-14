/*
	Library: Shortest Path
    Algorithm: Dijkstra
    Input: edge connection (no negative cycle)
    Output: single source shortest path
    Notice: vertex index 1~n
*/

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

class Dijkstra{
	public:
		#define INF (int)1e9
		#define MAXN 1001
		struct EDGE{
			int to, w;
			EDGE() {};
			EDGE(int a, int b):to(a),w(b) {};
		};
		
		vector<EDGE> edge[MAXN];
		int Vnum, Enum, dis[MAXN], ava[MAXN];
		
	public:
		void Initial(){
			for(int i=0; i<=Vnum; i++)	edge[i].clear();
			memset(dis, 127, sizeof(dis));
			memset(ava, -1, sizeof(ava));
		}
		
		void Edge_Build(int a, int b, int w){	
			edge[a].push_back(EDGE(b, w));
			edge[b].push_back(EDGE(a, w));	// default bidirectional
		}
		
		void RunDijkstra(int source){
			int n = Vnum;
			dis[source] = 0;
			while( n-- ){
				int m = INF, c;
				for(int i=1; i<=Vnum; i++)if( ava[i] && (m>dis[i]) )
					m = dis[i], c = i;
				ava[c] = 0;
				for(int i=0,j=edge[c].size(); i<j; i++)
				if( dis[edge[c][i].to] > dis[c] + edge[c][i].w )
					dis[edge[c][i].to] = dis[c] + edge[c][i].w;
			}
		}
};

Dijkstra my;

int main(void){
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int a, b, c;
	
	while( scanf("%d %d", &my.Vnum, &my.Enum)!=EOF ){
		my.Initial();
		for(int i=0; i<my.Enum; i++){
			scanf("%d %d %d", &a, &b, &c);
			my.Edge_Build(a, b, c);
		}
		my.RunDijkstra(1);	// vertex 1 as source
		for(int i=1; i<=my.Vnum; i++)
			printf("1->%d: %d\n", i, my.dis[i]);
	}
	
	return 0;
}

