/*
	Library: Shortest Path Fast Algorithm
    Algorithm: Revised BFS/Bellmon-Ford
    Input: edge connection
    Output: T/F for negative cycle and single source shortest path
*/

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

class SPFA{
	public:
		#define MAXV 301
		struct EDGE{
			int next, w;
			EDGE(){};
			EDGE(int a, int b):next(a),w(b) {};
		};
		
		vector<EDGE> edge[MAXV];
		int Vnum, Enum, dis[MAXV], prev[MAXV];
		
	public:
		void Initial(void){	// Initialize necessary data
			for(int i=0; i<=Vnum; i++)	edge[i].clear();
			memset(dis, 127, sizeof(dis));
			memset(prev, -1, sizeof(prev));
		}
		
		void Build_Edge(int a, int b, int w){
			edge[a].push_back(EDGE(b,w));
			edge[b].push_back(EDGE(a,w));	// if bi-directional 
		}
		
		bool RunSPFA(int start){	// return true means negative cycle
			int count[MAXV]={0}, inqueue[MAXV]={0}, now, next;
			queue<int> que;

			que.push(start);	count[start]++;
			dis[start] = 0;	inqueue[start] = 1; 
			while( !que.empty() ){
				now = que.front();	que.pop();	inqueue[now] = 0;
				for(int i=0, j=edge[now].size(); i<j; i++){
					next = edge[now][i].next;
					if( dis[next] > dis[now] + edge[now][i].w ){
						dis[next] = dis[now] + edge[now][i].w;	prev[next] = now;
						if( !inqueue[next] )
							que.push(next), inqueue[next] = 1, count[next]++;
						// Negative cycle
						if( count[next]>=Vnum )	return true;
					}
				}
			}
			return false;
		}
};

SPFA my;

int main(void){
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	int a, b, w;
	while( scanf("%d %d", &my.Vnum, &my.Enum)!=EOF ){
		my.Initial();
		/* Read the edge */
		for(int i=0; i<my.Enum; i++){
			scanf("%d %d %d", &a, &b, &w);
			my.Build_Edge(a, b, w);
		}
		/* If the start point is 1 and destination point is Vnum */
		if(my.RunSPFA(1))	puts("Negative Cycle.");
		else				printf("%d\n", my.dis[my.Vnum]);
	}
	return 0;
}
