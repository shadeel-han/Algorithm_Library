/*
	Library: Computational Geometry - Kernel Region / Polygon Intersection
    Algorithm: Half-Plane Cut, Math - Cross Product
    Input: coordinates of one/two polygons' vertices (counterclockwise order) 
    Output: kernel region of the polygon / intersection region of two polygons (in "polyB")
    Notice: Time Complexity O(N^2) / O(N*M)
*/

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct POINT{	// also vector
	double x, y;
	POINT() {};
	POINT(double a, double b):x(a),y(b) {};
	POINT operator - (const POINT &k){
		return POINT(x-k.x, y-k.y);
	}
	double operator * (const POINT &k){	// overload for cross product
		return x*k.y - y*k.x;
	}
};

struct LINE{
	POINT p1, p2;
	LINE() {};
	LINE(POINT a, POINT b):p1(a),p2(b) {};
};

class KernelRegion{
	public:
		#define EPS (1e-6)
		vector<POINT> polyA, polyB;	// output polygon's vertices will be in polyB
		int Anum, Bnum;
		double InterArea;
		
	public:
		void Initial(){
			polyA.clear();	polyB.clear();
		}
		
		int dbeps(double a){
			if( a < -EPS )	return -1;
			if( a > EPS )	return 1;
			return 0;
		}
		
		// cross product implies the direction from oa to ob, +:counterclockwise, -:clockwise, 0:parallel
		double Cross(POINT org, POINT a, POINT b){
			return (a-org)*(b-org);
		}
		
		// use Determinant to calculate the area of polygon
		// if the order of polygon's vertices is clockwise, return value is negative, otherwise positive
		double PolygonArea(vector<POINT> poly){
			double area = 0.0;
			poly.push_back(poly[0]);	// append the starting vertex for convenience
			for(int i=0,j=poly.size()-1; i<j; i++)
				area += poly[i]*poly[i+1];
			return area/2.0;
		}
		
		// use Cramer's Rule to find intersection of two infinite lines
		POINT IntersectPoint(LINE a, LINE b){
			POINT p12 = a.p2 - a.p1, p13 = b.p1 - a.p1, p34 = b.p2 - b.p1;
			double d1 = p13 * p34, d2 = p12 * p34;
			return POINT(a.p1.x + p12.x * (d1/d2), a.p1.y + p12.y * (d1/d2));
		}
		
		vector<POINT> FindHalfPlaneCut(POINT p1, POINT p2, vector<POINT> poly){
			vector<POINT> inter;
			int now, next;
			
			poly.push_back(poly[0]);	// append the starting vertex for convenience
			now = dbeps(Cross(p1, p2, poly[0]));
			for(int i=0,j=poly.size()-1; i<j; i++){
				// if the node is counterclockwise to p1p2 or on p1p2, it is what we want
				if( now >= 0 )
					inter.push_back(poly[i]);
				next = dbeps(Cross(p1, p2, poly[i+1]));
				// if next node is on different side to p1p2, we leave only the intersection point
				if( now * next < 0 )
					inter.push_back(IntersectPoint(LINE(p1,p2), LINE(poly[i], poly[i+1])));
				now = next;
			}
			return inter;
		}
		
		void FindIntersection(void){
			// make sure vertices of polygons are in counterclockwise order
			if( PolygonArea(polyA)<0 )	reverse(polyA.begin(), polyA.end());
			if( PolygonArea(polyB)<0 )	reverse(polyB.begin(), polyB.end());
			
			polyA.push_back(polyA[0]);	// append the starting vertex for convenience
			for(int i=0,j=polyA.size()-1; i<j; i++){
				if( !polyB.size() )	break;	// no more intersection
				polyB = FindHalfPlaneCut(polyA[i], polyA[i+1], polyB);
			}
			polyA.pop_back();			// remove the appending
			InterArea = PolygonArea(polyB);
		}
};

KernelRegion my;

int main(void){
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	double a, b;
	
	while( scanf("%d %d", &my.Anum, &my.Bnum)!=EOF ){	// if Bnum=0, find kernel region
		my.Initial();
		for(int i=0; i<my.Anum; i++){
			scanf("%lf %lf", &a, &b);
			my.polyA.push_back(POINT(a,b));
		}
		if( !my.Bnum )	my.Bnum = my.Anum, my.polyB = my.polyA;
		else for(int i=0; i<my.Bnum; i++){
			scanf("%lf %lf", &a, &b);
			my.polyB.push_back(POINT(a,b));
		}
		my.FindIntersection();
		printf("The area of intersection region: %.2lf\n", my.InterArea);
		for(int i=0,j=my.polyB.size(); i<j; i++)	printf("(%.2lf,%.2lf)\n", my.polyB[i].x, my.polyB[i].y);
	}
	
	return 0;
}

/*
	Input example:
	4 4
	0 0 1 0 1 1 0 1
	0 0 2 0 2 2 0 2
	4 4
	3 0 0 3 -3 0 0 -3
	2 2 -2 2 -2 -2 2 -2
	6 0
	3 3 -3 3 -2 0 -3 -3 3 -3 2 0
	7 0
	-3.1 9.9 -9.4 -3.1 -6 -4 4.9 -7.2
	5.4 8.8 2.3 9.8 -1.2 6.7
	
	Output example:
	The area of intersection region: 1.00
	(0.00,0.00) (1.00,0.00)
	(1.00,1.00) (0.00,1.00)
	The area of intersection region: 14.00
	(1.00,2.00) (-1.00,2.00) (-2.00,1.00) (-2.00,-1.00)
	(-1.00,-2.00) (1.00,-2.00) (2.00,-1.00) (2.00,1.00)
	The area of intersection region: 18.00
	(1.00,3.00) (-1.00,3.00) (-2.00,0.00) (-1.00,-3.00)
	(1.00,-3.00) (2.00,0.00)
	The area of intersection region: 103.39
	(-7.25,1.35) (-9.36,-3.01) (-6.00,-4.00) (4.91,-6.89)
	(5.01,-3.75) (-1.20,6.70)
*/

