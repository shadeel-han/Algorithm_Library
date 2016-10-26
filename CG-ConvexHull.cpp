/*
	Library: Computational Geometry - Convex Hull
    Algorithm: Graham Scan, Math - Cross Product
    Input: N points' coordinates 
    Output: a convex polygon that all points lie inside it
    Notice: Search convex hull only takes O(N), but O(NlogN) for polar sorting.
    		No three selected points on the same line, that's if mutiple points lie on the same 
			boundary of the convex polygon, this algorithm only picks the outmost two points.
*/

#include <cstdio>
#include <algorithm>

using namespace std;

class ConvexHull{
	public:
		#define MAXN 10001
		#define EPS 1e-8
		struct POINT{	// also vector
			double x, y, xx, yy, dis;
			POINT() {};
			POINT(double a, double b):x(a),y(b) {};
			POINT operator - (const POINT &k){
				return POINT(x-k.x, y-k.y);
			}
			double operator * (const POINT &k){	// overload for cross product
				return x*k.y - y*k.x;
			}
			bool operator < (const POINT &k) const{	// overload for polar angle sorting
				double d = xx*k.yy - yy*k.xx;
				return (d>0 || (d>-EPS && dis<k.dis) );
			}
		};
		
		POINT in[MAXN], poly[MAXN];
		int Vnum, PolyNum;
		
	public:
		double Dis(POINT a){
			return a.x*a.x + a.y*a.y;
		}
		
		// cross product implies the direction from oa to ob, +:counterclockwise, -:clockwise, 0:parallel
		double Cross(POINT org, POINT a, POINT b){
			return (a-org)*(b-org);
		}
		
		void FindBase_PolarSorting(void){
			int index = 0;	POINT base = in[0];
			for(int i=1; i<Vnum; i++)
			if( (in[i].y<base.y) || ((in[i].y==base.y) && (in[i].x<base.x)) )
				base = in[i], index = i;
			in[index] = in[0];	in[0] = base;
			for(int i=1; i<Vnum; i++){
				in[i].xx = in[i].x - base.x;
				in[i].yy = in[i].y - base.y;
				in[i].dis = Dis(in[i]-base);
			}
			sort(in+1, in+Vnum);
		}
		
		void FindConvexHull(void){
			PolyNum = 2;
			poly[0] = in[0], poly[1] = in[1];
			for(int i=2; i<Vnum; i++){
				while( PolyNum>=2 && Cross(poly[PolyNum-2], poly[PolyNum-1], in[i])<EPS )
					PolyNum--;
				poly[PolyNum++] = in[i];
			}
		}
};

ConvexHull my;

int main(void){
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	
	while( scanf("%d", &my.Vnum)!=EOF ){
		for(int i=0; i<my.Vnum; i++)	scanf("%lf %lf", &my.in[i].x, &my.in[i].y);
		my.FindBase_PolarSorting();
		my.FindConvexHull();
		printf("Convex Hull vertex number: %d\n", my.PolyNum);
		for(int i=0; i<my.PolyNum; i++)	printf("(%.2lf,%.2lf)\n", my.poly[i].x, my.poly[i].y);
	}
	
	return 0;
}

/*
	Input example:
	8
	0 0 1 0 2 0 2 1
	2 2 1 2 0 2 0 1
	4
	0 0 0 5 5 0 5 5
	5
	0 0 1 1 2 2 3 3 4 4
	10
	1.7 5.4 2.3 9.8 -1.2 6.7 -9.4 -3.1 5.4 8.8
	-4.3 1.0 -5.6 -5.3 4.9 -7.2 9.1 -6.8 -3.1 9.9

	Output example:
	Convex Hull vertex number: 4
	(0.00,0.00) (2.00,0.00)
	(2.00,2.00) (0.00,2.00)
	Convex Hull vertex number: 4
	(0.00,0.00) (5.00,0.00)
	(5.00,5.00) (0.00,5.00)
	Convex Hull vertex number: 2
	(0.00,0.00) (4.00,4.00)
	Convex Hull vertex number: 7
	(4.90,-7.20) (9.10,-6.80) (5.40,8.80) (2.30,9.80)
	(-3.10,9.90) (-9.40,-3.10) (-5.60,-5.30)
*/
