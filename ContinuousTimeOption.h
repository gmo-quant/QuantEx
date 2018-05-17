#pragma once
#include"stdafx.h"

/**
 * Interface class for an option whose payoff should
 * be approximated by looking at stock prices over all time
 * time points
 */

class ContinuousTimeOption{
public:
	/*virtual destructor*/
	virtual ~ContinuousTimeOption(){};
	/* the maturity of the option*/
	virtual double getMaturity() const = 0;
	/* Calculate the payoff of the option given a history of prices*/
	virtual double payoff(
		const std::vector<double>& stockPrices) const=0;
	/* is the option path-dependent?*/
	virtual bool isPathDependent() const = 0;
};