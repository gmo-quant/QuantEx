#include "Histogram.h"
#include "testing.h"
#include "matlib.h"
#include "LineChart.h"

using namespace std;




/**
 *    This function computes the data needed to plot a histogram
 *    we have two vectors - one containing numBuckets+1 values which
 *    indicate the x coordinates of each "fence post" in our histogram
 *    and another containing numBuckets values which contains the heights
 *    of each fence post.
 */
static void histogramData( const vector<double>& values,
                           int numBuckets,
                           vector<double>& fencePosts,
                           vector<double>& heights ) {

    fencePosts = vector<double>( numBuckets+1, 0.0);
    heights = vector<double>( numBuckets, 0.0 );

    ASSERT( values.size()>0);
    vector<double> sortedValues = sort(values);

    double start = min( values );
    double end = max( values );

    double width = (end-start)/numBuckets;
    for (int i=0; i<numBuckets+1; i++) {
        fencePosts[i] = start + i*width;
    }

    int currentFence = 0;
    int numPoints = sortedValues.size();
    double fenceEnd = fencePosts[ currentFence+1];
    for (int i=0; i<numPoints; i++) {
        double value = sortedValues[i];
        while ( value>fenceEnd ) {
            currentFence++;
            fenceEnd = fencePosts[currentFence+1];
        }
        heights[ currentFence ]++;
    }

}

/**
 *  Having computed the fence posts and fence heights for our histogram
 *  we can convert this to a series of x and y points to plot. Google charts
 *  works fine with repeated x points, so this will give a nice looking result.
 */
static void fencePostsToPlotPoints( const vector<double>& fencePosts,
                                    const vector<double>& heights,
                                    vector<double>& xPoints,
                                    vector<double>& yPoints ) {
    int n = heights.size();
    xPoints = vector<double>(4*n, 0.0);
    yPoints = vector<double>(4*n, 0.0);
    int count = 0;
    for (int i=0; i<n; i++) {
        double x1 = fencePosts[i];
        double x2 = fencePosts[i+1];
        double y = heights[i];
        xPoints[count] = x1;
        yPoints[count] = 0.0;
        count++;
        xPoints[count] = x1;
        yPoints[count] = y;
        count++;
        xPoints[count] = x2;
        yPoints[count] = y;
        count++;
        xPoints[count] = x2;
        yPoints[count] = 0;
        count++;
    }
    ASSERT( count==4*n );
}


//////////////////////////////////
// Histogram class
/////////////////////////////////

Histogram::Histogram() :
  numBuckets(10),
  title("A Histogram") {
}

void Histogram::setTitle( const string& t) {
    title = t;
}

void Histogram::setData( const vector<double>& v) {
    data = v;
}

void Histogram::setNumBuckets( int n ) {
    numBuckets = n;
}


void Histogram::writeAsHTML( ostream& out ) const {
    vector<double> fencePosts, heights, x, y;
    histogramData( data, numBuckets, fencePosts, heights );
    fencePostsToPlotPoints( fencePosts, heights, x, y );
    LineChart lc;
    lc.setTitle( title );
    lc.setSeries(x,y);
    lc.writeAsHTML( out );
}

void Histogram::writeAsHTML( const string& file ) const {
    ofstream out;
    out.open( file.c_str() );
    writeAsHTML( out );
    out.close();
}




//////////////////////////////////////////////////////
//
//   TESTS
//
//////////////////////////////////////////////////////



void testHistogramData() {
    // a good test that is completely automated
    vector<double> data;
    data.push_back(1.0);
    data.push_back(2.0);
    data.push_back(3.0);
    data.push_back(4.0);
    data.push_back(5.0);

    vector<double> fencePosts;
    vector<double> heights;
    histogramData( data,
                   3,
                   fencePosts,
                   heights );

    ASSERT( fencePosts.size()==4);
    ASSERT( heights.size()==3);
    ASSERT_APPROX_EQUAL( fencePosts[0], 1.0, 0.001);
    ASSERT_APPROX_EQUAL( fencePosts[3], 5.0, 0.001);
    ASSERT_APPROX_EQUAL( sum(heights), 5.0, 0.001 );
}

void testFencePostsToPlotPoints() {
    // a good test that is completely automated
    vector<double> fencePosts;
    fencePosts.push_back(1);
    fencePosts.push_back(2);
    fencePosts.push_back(3);
    vector<double> heights;
    heights.push_back(1.0);
    heights.push_back(-1.0);

    vector<double> x,y;
    fencePostsToPlotPoints( fencePosts, heights, x, y );
    ASSERT_APPROX_EQUAL( x[0], 1.0, 0.001 );
    ASSERT_APPROX_EQUAL( x[1], 1.0, 0.001 );
    ASSERT_APPROX_EQUAL( x[2], 2.0, 0.001 );
    ASSERT_APPROX_EQUAL( x[3], 2.0, 0.001);
    ASSERT_APPROX_EQUAL( x[4], 2.0, 0.001);

    ASSERT_APPROX_EQUAL( y[0], 0.0, 0.001 );
    ASSERT_APPROX_EQUAL( y[1], 1.0, 0.001 );
    ASSERT_APPROX_EQUAL( y[2], 1.0, 0.001 );
    ASSERT_APPROX_EQUAL( y[3], 0.0, 0.001 );
    ASSERT_APPROX_EQUAL( y[4], 0.0, 0.001 );
    ASSERT_APPROX_EQUAL( y[5], -1.0, 0.001 );

}

static void testAll() {
    // a somewhat unsatisfactory test since it writes a file, but pretty much
    // everything it uses has been tested individually.
    Histogram h;
    h.setTitle("Uniform distribution");
    h.setData( randuniform(1000) );
    h.writeAsHTML( "uniformDistributionHistogram.html" );
}

void testHistogram() {
    TEST( testHistogramData );
    TEST( testFencePostsToPlotPoints );
    TEST( testAll );
}