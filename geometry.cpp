#include "geometry.h"
#include "stdafx.h"
#include "testing.h"

using namespace std;

/**
 *   Computes the area of a circle
 */
double Circle::area() {
	return PI*radius*radius;
}

/**
 *  Computes the circumference of a circle
 */
double Circle::circumference() {
	return 2*PI*radius;
}

/**
 *  Computes the distance between two cartesian points
 */
double CartesianPoint::distanceTo( const CartesianPoint& other ) const {
    double dx = other.x - x;
    double dy = other.y - y;
    return sqrt( dx*dx + dy*dy );
}

/**
 *  Computes the distance between this and a polar point
 */
double CartesianPoint::distanceTo( const PolarPoint& other ) const {
    return distanceTo( polarToCartesian( other ));
}



/**
 *  Converts polar coordinates to cartesian. Note, this changes x and y.
 */
CartesianPoint polarToCartesian( const PolarPoint& p ) {
    CartesianPoint c;
	c.x = p.r*cos( p.theta );
	c.y = p.r*sin( p.theta );
    return c;
}

/**
 *   Converts Cartesian coordinates to polar coordinates. Note this
 *   changes r and theta.
 */
PolarPoint cartesianToPolar( const CartesianPoint& c) {
    PolarPoint p;
	// Not as easy as it looks to do this
	p.r = sqrt( c.x*c.x + c.y*c.y);
	if (c.y==0.0) {
		if (c.x>=0.0) {
			p.theta = 0.0;
		} else if (c.x<0.0) {
			p.theta = -PI;
		}
	} else {
		p.theta = acos( c.x/p.r);
		if (c.y<0) {
			p.theta = -p.theta;
		}
	}
    return p;
}


/////////////////////////////////////////////////
//
//  Geometry tests
//
/////////////////////////////////////////////////

static void testUsage() {
    CartesianPoint cartesianPoint;
    cartesianPoint.x = 100;
    cartesianPoint.y = 150;
    cout << "Coordinates (";
    cout << cartesianPoint.x ;
    cout << ", ";
    cout << cartesianPoint.y ;
    cout << ")\n";

    cartesianPoint.x *= 2;
    cartesianPoint.y *= 2;
    cout << "Rescaled cordinates (";
    cout << cartesianPoint.x ;
    cout << ", ";
    cout << cartesianPoint.y ;
    cout << ")\n";
}

static void testAreaOfCircle() {
    Circle c;
    c.radius = 4;
	ASSERT_APPROX_EQUAL( c.area(), 16*PI, 0.01 );
}

static void testCircumferenceOfCircle() {
    Circle c;
    c.radius = 2;
	ASSERT_APPROX_EQUAL( c.circumference(), 4*PI, 0.01 );
}

static void testPolarToCartesian() {
    PolarPoint p;
    p.r = 2.0;
    p.theta = PI/2;
	CartesianPoint c = polarToCartesian( p );
	ASSERT_APPROX_EQUAL( c.x,0.0,0.001 );
	ASSERT_APPROX_EQUAL( c.y,2.0,0.001 );
}

static void testCartesianToPolar() {
	// the logic of cartesian to polar is quite complex so we have more tests
	vector<double> angles;
	angles.push_back( 0.0 );
	angles.push_back( PI/4 );
	angles.push_back( PI/2 );
	angles.push_back( 7*PI/8 );
	angles.push_back( PI);
	angles.push_back( -PI/4 );
	angles.push_back( -PI/2 );
	angles.push_back( -7*PI/8 );

	int nAngles = angles.size();
	for (int i=0; i<nAngles; i++) {
        PolarPoint p;
		p.r = 2.0;
		p.theta =angles[i];
		CartesianPoint c =polarToCartesian( p);
		PolarPoint p2;
		p2 = cartesianToPolar( c );
		ASSERT_APPROX_EQUAL( p.r,p2.r,0.001 );
		ASSERT_APPROX_EQUAL( p.theta,p2.theta,0.001 );
	}
}

static void testDistanceTo() {
    CartesianPoint p1;
    p1.x = 1;
    p1.y = 1;
    CartesianPoint p2;
    p2.x = 4;
    p2.y = 5;
    double d = p1.distanceTo( p2 );
    ASSERT_APPROX_EQUAL( d, 5.0, 0.0001);    
}

static void testDistanceToPolar() {
    CartesianPoint p1;
    p1.x = 1;
    p1.y = 1;
    CartesianPoint p2;
    p2.x = 4;
    p2.y = 5;
    double d = p1.distanceTo( cartesianToPolar(p2) );
    ASSERT_APPROX_EQUAL( d, 5.0, 0.0001);    
}

static void testPerimeter() {
	CartesianPoint a, b, c;
	a.x = 0.0;
	a.y = 0.0;
	b.x = 3.0;
	b.y = 0.0;
	c.x = 0.0;
	c.y = 4.0;
	ASSERT_APPROX_EQUAL(perimeter(a, b, c), 12.0, 0.001);
}



void testGeometry() {
    TEST (testUsage );
	TEST( testAreaOfCircle );
	TEST( testCircumferenceOfCircle );
	TEST( testPolarToCartesian );
	TEST( testCartesianToPolar );
    TEST( testDistanceTo );
    TEST( testDistanceToPolar );
	TEST(testPerimeter);
}