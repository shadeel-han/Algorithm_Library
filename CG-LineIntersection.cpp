/*
	Library: Computational Geometry - Line Intersection
    Algorithm: Math - Cross Product and Cramer's Rule
    Input: lines with double-type vertices
    Output: T/F two lines intersect, if T find the intersection point
    Notice: Intersection judegement relies on many times of cross product, so much multiplication will be used.
    		Beware of multiplication is highly time-consuming instruction for CPU, not to mention double-type.
    		Attention proper/nonproper situation, end-points of lines are excluded/included. Nonproper is more general.
    		This code is for lines with end-points, if infinite lines, nonproper intersection isn't needed.
*/

#include <cstdio>
#include <algorithm>

using namespace std;
#define EPS (1e-6)

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
};

int double_eps(double a){
	if( a > EPS )	return 1;
	if( a < -EPS )	return -1;
	return 0;
}

bool OnSegment(POINT a, POINT b, POINT c){	// b is between a and c
	return ( min(a.x,c.x)<=b.x && b.x<=max(a.x,c.x) && min(a.y,c.y)<=b.y && b.y<=max(a.y,c.y) );
}

int Intersection_Judge(LINE a, LINE b, POINT &point){
	// vector
	POINT p12 = a.p2 - a.p1, p34 = b.p2 - b.p1;
	POINT p13 = b.p1 - a.p1, p14 = b.p2 - a.p1;
	POINT p31 = a.p1 - b.p1, p32 = a.p2 - b.p1;
	// cross product implies the direction, +:counterclockwise, -:clockwise, 0:parallel
	double d1 = p34 * p31;	// direction of p34 to p31
	double d2 = p34 * p32;	// direction of p34 to p32
	double d3 = p12 * p13;	// direction of p12 to p13
	double d4 = p12 * p14;	// direction of p12 to p14
	double d5 = p12 * p34;	// direction of p12 to p34
	
	/* finite lines */
	// parallel/overlap
	if( !double_eps(d5) ){
		if( !double_eps(d1) )	return 2;
		else					return 1;
	}
	// proper intersection
	if( double_eps(d1*d2)<0 && double_eps(d3*d4)<0 ){
		point.x = a.p1.x + p12.x * (d1/d5);	// Cramer's Rule
		point.y = a.p1.y + p12.y * (d1/d5);
		return 0;
	}
	// nonproper intersection
	if( !double_eps(d1) && OnSegment(b.p1,a.p1,b.p2) ){ point = a.p1; return 0; }
	if( !double_eps(d2) && OnSegment(b.p1,a.p2,b.p2) ){ point = a.p2; return 0; }
	if( !double_eps(d3) && OnSegment(a.p1,b.p1,a.p2) ){ point = b.p1; return 0; }
	if( !double_eps(d4) && OnSegment(a.p1,b.p2,a.p2) ){ point = b.p2; return 0; }
	return 3;
}

int main(void){
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	LINE s1, s2;
	POINT point;
	
	while( scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &s1.p1.x, &s1.p1.y, 
		&s1.p2.x, &s1.p2.y, &s2.p1.x, &s2.p1.y, &s2.p2.x, &s2.p2.y)!=EOF ){
		int c = Intersection_Judge(s1, s2, point);
		if( c==1 )		puts("Two lines are parallel.");
		else if( c==2 )	puts("Two lines are overlapping.");
		else if( c==3 )	puts("Two lines straddle each other.");
		else			printf("Two lines intersect at (%.2lf, %.2lf).\n", point.x, point.y);
	}
	
	return 0;
}

/*
	Input example:
	0 0 1 1 1 0 2 1
	0 0 1 1 2 2 3 3
	0 0 1 1 1 0 0 1
	0 0 1 1 2 0 0 2
	0 0 1 1 3 0 0 4
	4 9 5 -3 2 2 10 6
	
	Output example:
	Two lines are parallel.
	Two lines are overlapping.
	Two lines intersect at (0.50, 0.50).
	Two lines intersect at (1.00, 1.00).
	Two lines straddle each other.
	Two lines intersect at (4.48, 3.24).
*/

