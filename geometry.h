#pragma once

const double PI = 3.1415926535897932384626433832795028842;

// forward declarations, allows references
// to be used between the different classes
class Circle;
class PolarPoint;
class CartesianPoint;

class Circle {
public:
    double radius;
    double area();
    double circumference();
};

class CartesianPoint {
public:
    double x;
    double y;

    double distanceTo( const CartesianPoint& x ) const;
    double distanceTo( const PolarPoint& x ) const;
};

class PolarPoint {
public:
    double r;
    double theta;

};



/**
 *   Computes the area of a circle
 */
double areaOfCircle(double r);

/**
 *  Computes the circumference of a circle
 */
double circumferenceOfCircle(double r);

/**
 *   Converts Cartesian coordinates to polar coordinates. Note this
 *   changes r and theta.
 */
PolarPoint cartesianToPolar( const CartesianPoint& );

/**
 *  Converts polar coordinates to cartesian. Note, this changes x and y.
 */
CartesianPoint polarToCartesian( const PolarPoint& );

/**
 *  Computes the perimeter of a triangle
 */
inline double perimeter( const CartesianPoint& p1,
                  const CartesianPoint& p2,
                  const CartesianPoint& p3 ) {
	return p1.distanceTo(p2) + p2.distanceTo(p3) + p3.distanceTo(p1); 
}

/**
 *  Test suite
 */
void testGeometry();