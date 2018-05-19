#pragma once

#include "stdafx.h"
#include "ContinuousTimeOptionBase.h"

/** 
 *	all path independent options
 * have a payoff determined by the final stock price
 */
class PathIndependentOption : 
		public ContinuousTimeOptionBase {
public:
	/* virtual destructor */
	virtual ~PathIndependentOption(){}
	/* return payoff at maturity */
	virtual double payoff(double finalStockPrice) const=0;
	/* Compute the payoff from a price path*/
	double payoff(
		const std::vector<double>& stockPrices) const{
		return payoff(stockPrices.back());
	}
	/* is the option path dependent? */
	bool isPathDependent() const{
		return false;
	}
};