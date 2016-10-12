/*
	Library: find cut edge/cut vertex (articulation point)
    Algorithm: DFS with dfn/low value
    Input: vertex index 1~n, bidirection edges
    Output: all cut vertices/edges
*/

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

class CutVertex{
	public:
		#define MAXN 1001
		vector<int> graph[MAXN], cutv;
		int dfn[MAXN], low[MAXN], cnt, Vnum, Enum;
		
	public:
		void dfnlow(int u, int v){	// v is parent of u
			int child = 0;	bool IsCut = false;
			dfn[u] = low[u] = cnt++;
			for(int i=0,j=graph[u].size(); i<j; i++){
				int w = graph[u][i];
				if( dfn[w]<0 ){		// w isn't visited, so w is child of u
					dfnlow(w,u);	child++;
					low[u] = (low[u]<low[w])?(low[u]):(low[w]);
					if( low[w]>=dfn[u] )	IsCut = true;
				}else if( w!=v )
					low[u] = (low[u]<low[w])?(low[u]):(low[w]);
			}
			// root has >=2 children, or u has a child w whose low[w]>=dfn[u]
			if( (child>1) || (v>=0 && IsCut) )	cutv.push_back(u);
			/* for cut edge, low[w]>dfn[u] (no ==) */
		}
		
		void Initial(void){
			for(int i=1; i<=Vnum; i++)	graph[i].clear();
			memset(dfn, -1, sizeof(dfn));
			memset(low, -1, sizeof(low));
			cutv.clear();	cnt = 0;
		}
		
		void FindCutVertex(void){
			for(int i=1; i<=Vnum; i++)
			if( dfn[i]==-1 )	dfnlow(i,-1);
		}
};

CutVertex my;

int main(void){
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	
	int f, t;
	
	while( scanf("%d %d", &my.Vnum, &my.Enum)!=EOF ){
		my.Initial();
		for(int i=0; i<my.Enum; i++){
			scanf("%d %d", &f, &t);
			my.graph[f].push_back(t);
			my.graph[t].push_back(f);
		}
		my.FindCutVertex();
		printf("There are %d cut vertex:", (int)my.cutv.size());
		for(int i=0,j=my.cutv.size(); i<j; i++)	printf(" %d", my.cutv[i]);
		putchar('\n');
	}
	
	return 0;
}

