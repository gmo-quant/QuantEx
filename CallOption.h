#pragma once

#include"stdafx.h"
#include"BlackScholesModel.h"
#include"PathIndependentOption.h"

class CallOption :
	public PathIndependentOption{
public:
	

	/*
	 * computes the payoff at maturity
	 */
	double payoff(double stockAtMaturity) const;
	/*
	 * computes the price given some hypothetical  market data
	 * in the form of BlackScholesModel
	 */
	double price (const BlackScholesModel& bsm) const;
	double delta(const BlackScholesModel& bsm) const;
};

void testCallOption();