#pragma once

#include "stdafx.h"


/*  Create a linearly spaced vector */
std::vector<double> linspace( double from, double to, int numPoints );
/*  Compute the sum of a vector */
double sum( const std::vector<double>& v );
/*  Compute the mean of a vector */
double mean( const std::vector<double>& v );
/*  Compute the standard deviation of a vector */
double standardDeviation( const std::vector<double>& v, bool population=0 );
/*  Find the minimum of a vector */
double min( const std::vector<double>& v );
/*  Find the maximum of a vector */
double max( const std::vector<double>& v );
/*  Find the given percentile of a vector */
double prctile( const std::vector<double>& v, double percentage );
/*  Sort a vector */
std::vector<double> sort( const std::vector<double>&  v );

/*  Create uniformly distributed random numbers */
std::vector<double> randuniform( int n );
/*  Create normally distributed random numbers */
std::vector<double> randn( int n );
/*  Seeds the default random number generator */
void rng( const std::string& setting );

/**
 *  Computes the cumulative
 *  distribution function of the
 *  normal distribution
 */
double normcdf( double x );

/* Computes the inverse of normcdf */
double norminv( double x ); 


/*  Create a line chart */
void plot( const std::string& fileName,
           const std::vector<double>& x,
           const std::vector<double>& y);

/*  Plot a histogram */
void hist( const std::string& fileName,
           const std::vector<double>& values,
           int numBuckets=10);


/**
 *  Test function
 */
void testMatlib();
