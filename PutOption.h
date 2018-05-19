#pragma once

#include"stdafx.h"
#include"BlackScholesModel.h" 
#include"PathIndependentOption.h"

class PutOption : 
	public ContinuousTimeOptionBase{
public:	
	/*
	 * computes the payoff of the option given 
	 * a history of prices
	 */
	double payoff(
		const std::vector<double>& stockPrices
		) const;
	/*
	 * computes the price given some hypothetical  market data
	 * in the form of BlackScholesModel
	 */
	double price (const BlackScholesModel& bsm) const;

 	bool isPathDependent() const {
        return false;
    };

};

void testPutOption();