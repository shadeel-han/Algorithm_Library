/*
	Library: Minimum spanning tree - Kruskal
    Algorithm: Kruskal and Disjoint Set
    Input: edge connection
    Output: the weight of MST
*/

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

class MST_Kruskal{
	public:
		#define MAXV 1001
		struct EDGE{
			int f, t, w;
			EDGE(){};
			EDGE(int a, int b, int c):f(a),t(b),w(c) {};
			bool operator<(const EDGE &a) const{	// overload for sorting
				return (w<a.w);
			}
		};
		
		vector<EDGE> edge[MAXV], s;
		int Vnum, Enum, p[MAXV], r[MAXV], cost;	// p, r used for disjoint set
	
	public:
		void Initial(void){
			cost = 0;	s.clear();
			for(int i=0; i<=Vnum; i++){
				//edge[i].clear();
				MakeSet(i);
			}
		}
		
		void Edge_Build(int a, int b, int w){	
			//edge[a].push_back(EDGE(a, b, w));
			//edge[b].push_back(EDGE(b, a, w));	// default bidirectional
			s.push_back(EDGE(a, b, w));
		}
		
		bool Run_Kruskal(void){	// if not connected, return true
			int cnt = Vnum-1;
			sort(s.begin(), s.end());
			for(int i=0, j=s.size(); i<j&&cnt; i++)
			if( FindSet(s[i].f) != FindSet(s[i].t) ){
				Union(s[i].f, s[i].t);
				cost += s[i].w;	cnt--;
				//printf("%d %d\n", s[i].f, s[i].t);
			}
			return (cnt)?(true):(false);
		}
		
		int FindSet(int x){
    		if(x!=p[x])	p[x] = FindSet(p[x]);
    		return p[x];
		}

		void Link(int x,int y){
    		if(r[x]>r[y])	p[y] = x;
    		else{
        		p[x] = y;
        		if(r[x]==r[y])	r[y]++;
    		}
		}

		void Union(int x,int y){
    		Link(FindSet(x),FindSet(y));
		}

		void MakeSet(int x){
			p[x] = x;	r[x] = 0;
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
		if( my.Run_Kruskal() )	puts("Not Connected");
		else					printf("The weight of MST is %d.\n", my.cost);
	}
	return 0;
}


