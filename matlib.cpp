#include "matlib.h"
const double PI = 3.1415926535897932384626433832795028842;
const double ROOT_2_PI = sqrt( 2.0 * PI );


static inline double hornerFunction( double x, double a0, double a1) {
	return a0 + x*a1;
}

static inline double hornerFunction( double x, double a0, double a1, double a2) {
	return a0 + x*hornerFunction( x, a1, a2);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3) {
	return a0 + x*hornerFunction( x, a1, a2, a3);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4) {
	return a0 + x*hornerFunction( x, a1, a2, a3, a4);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
					   double a5) {
	return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
					   double a5, double a6) {
	return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5, a6);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
					   double a5, double a6, double a7) {
	return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5, a6, a7);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
					   double a5, double a6, double a7, double a8) {
	return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5, a6, a7, a8);
}

/**
 *  Arguably this is a little easier to read than the original normcdf
 *  function as it makes the use of horner's method obvious.
 */
double normcdf( double x ) {
    DEBUG_PRINT( "normcdf("<<x<<")");
	if (x<0) {
		return 1-normcdf(-x);
	}
	double k = 1/(1 + 0.2316419*x);
	double poly = hornerFunction(k,
								 0.0, 0.319381530, -0.356563782,
								 1.781477937,-1.821255978,1.330274429);
	double approx = 1.0 - 1.0/ROOT_2_PI * exp(-0.5*x*x) * poly;
	return approx;
}

/*  Constants required for Moro's algorithm */
static const double a0 = 2.50662823884;
static const double a1 = -18.61500062529;
static const double a2 = 41.39119773534;
static const double a3 = -25.44106049637;
static const double b1 = -8.47351093090;
static const double b2 = 23.08336743743;
static const double b3 = -21.06224101826;
static const double b4 = 3.13082909833;
static const double c0 = 0.3374754822726147;
static const double c1 = 0.9761690190917186;
static const double c2 = 0.1607979714918209;
static const double c3 = 0.0276438810333863;
static const double c4 = 0.0038405729373609;
static const double c5 = 0.0003951896511919;
static const double c6 = 0.0000321767881768;
static const double c7 = 0.0000002888167364;
static const double c8 = 0.0000003960315187;

double norminv( double x ) {
	// We use Moro's algorithm
    DEBUG_PRINT( "norminv(" << x <<")" );
	double y = x - 0.5;
	if (y<0.42 && y>-0.42) {
		double r = y*y;
        DEBUG_PRINT( "Case 1, r=" << r );
		return y*hornerFunction(r,a0,a1,a2,a3)/hornerFunction(r,1.0,b1,b2,b3,b4);
	} else {
		double r;
		if (y<0.0) {
			r = x;
		} else {
			r = 1.0 - x;
		}
        DEBUG_PRINT( "Case 2, r=" << r);
		double s = log( -log( r ));
		double t = hornerFunction(s,c0,c1,c2,c3,c4,c5,c6,c7,c8);
		if (x>0.5) {
			return t;
		} else {
			return -t;
		}
	}
}

///////////////////////////////////////////////
//
//   TESTS
//
///////////////////////////////////////////////


void testNormCdf() {
    ASSERT_APPROX_EQUAL( normcdf( 1.96 ), 0.975, 0.001 );
}

void testNormInv() {
    ASSERT_APPROX_EQUAL( norminv( 0.975 ), 1.96, 0.01 );
}



void testMatlib() {
    setDebugEnabled(true);
    TEST( testNormInv );
    setDebugEnabled(false);
    TEST( testNormCdf );
}
