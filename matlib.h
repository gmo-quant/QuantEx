#pragma once

#include "stdafx.h"

/**
 *  Computes the cumulative
 *  distribution function of the
 *  normal distribution
 */
double normcdf( double x );

/**
 *  Computes the inverse of normcdf
 */
double norminv( double x ); 

/**
 *  Test function
 */
void testMatlib();