#pragma once
#include"BlackScholesModel.h" 
class PutOption{
public:	
	/*
	 * constructors
	 */
	PutOption();
	PutOption(double strike, double maturity);

	/*
	 * computes the payoff at maturity
	 */
	double payoff(double stockAtMaturity) const;
	/*
	 * computes the price given some hypothetical  market data
	 * in the form of BlackScholesModel
	 */
	double price (const BlackScholesModel& bsm) const;

	/* 
	 * access strike price
	 */
	double strike()const{return _strike;};
	/*
	 * access maturity
	 */
	double maturity()const{return _maturity;};
	/*
	 * change strike
	 */
	void strike(double strike){ _strike = strike;};
	/* 
	 * change maturity
	 */
	void maturity(double maturity){ _maturity = maturity;};
private:
	double _strike;
	double _maturity;
};

void testPutOption();