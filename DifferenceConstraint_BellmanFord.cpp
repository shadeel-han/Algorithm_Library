/*
	Library: Difference Constraint
    Algorithm: Bellman Ford
    Input: difference constraints as edge connection
    Output: T/F if there's a feasible solution and the one solution
    Notice: Vertex 0 as pseudo-source
*/

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

class DiffCon{
	public:
		#define MAXN 1001
		struct EDGE{
			int u, v, w;
			EDGE() {};
			EDGE(int a, int b, int c):u(a),v(b),w(c) {};
			// [u] --- w ---> [v] : Xv-Xu<=w
		};
		
		vector<EDGE> edge;
		int val[MAXN], Vnum, Enum;
		
	public:
		void Initial(){
			edge.clear();
			memset(val, 64, sizeof(val));
		}
		
		// the order of arguments has to be [u] --- w ---> [v] : Xv-Xu<=w
		void Build_Edge(int u, int v, int w){
			edge.push_back(EDGE(u, v, w));
		}
		
		bool RunBellFord(int source){
			val[source] = 0;
			for(int i=0; i<Vnum; i++){		// run Vnum iteration
				bool stop = true;
				for(int j=0,k=edge.size(); j<k; j++)	// edge relaxation
				if( val[edge[j].v] > val[edge[j].u] + edge[j].w ){
					val[edge[j].v] = val[edge[j].u] + edge[j].w;
					stop = false;
				}
				if( stop )	break;
			}
			// check negative cycle
			for(int j=0,k=edge.size(); j<k; j++)
			if( val[edge[j].v] > val[edge[j].u] + edge[j].w )	return false;
			
			return true;
		}
};

DiffCon my;

int main(void){
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int u, v, w;
	
	while( scanf("%d %d", &my.Vnum, &my.Enum)!=EOF ){
		my.Initial();
		
		for(int i=0; i<my.Enum; i++){
			scanf("%d %d %d", &v, &u, &w);	// input format: Xv-Xu<=w
			my.Build_Edge(u, v, w);
		}
		/* add vertex 0 as pseudo-source, Xi-X0<=0
		   if there's feasible solution, change w to get different solution*/
		for(int i=1; i<=my.Vnum; i++)	my.Build_Edge(0, i, 0);
		if( !my.RunBellFord(0) )	puts("not feasible");
		else{
			for(int i=0; i<=my.Vnum; i++)	printf("%d ", my.val[i]);
			putchar('\n');
		}
	}
	return 0;
}

