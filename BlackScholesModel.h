#pragma once

#include"stdafx.h"

class BlackScholesModel{
public:
	/*
	 * constructors
	 */
	BlackScholesModel();
	explicit BlackScholesModel(double stockPrice);

	/*
	 * generate a simulated stock price path
	 * @param
	 * toDate: a final date
	 * nStep: number of steps
	 */
	std::vector<double> generatePricePath(double toDate, int nStep) const;

	/* 
	 * behave same as generatePricePath(), except that it
	 * use Q-measure to compute the path,
	 */
	std::vector<double> generateRiskNeutralPricePath(double toDate, int nStep) const;

	/* 
	 * access stock price, volatility, risk free rate, date
	 */
	double stockPrice() const{return _stockPrice;};
	double volatility() const{return _volatility;};
	double riskFreeRate() const{return _riskFreeRate;};
	double date() const{return _date;};

	/* 
	 * change stock price, volatility, risk free rate, date
	 */
	void stockPrice(double stockPrice) { _stockPrice = stockPrice;};
	void volatility(double volatility) { _volatility = volatility;};
	void riskFreeRate(double riskFreeRate) { _riskFreeRate = riskFreeRate;};
	void date(double date){ _date = date;};

private:
	double _stockPrice;
	double _volatility;
	double _riskFreeRate;
	double _date; 
	double _drift;

	/* 
	 * private method allow you to choose the drift in the simulation of the price path
	 * it is private because we've only created it to make the implementation easier.
	 */
	std::vector<double> generatePricePath(double toDate, int nStep, double drift) const;

};


/////////////////////////////////////
// UNIT TEST
///////////////////////////////////////////
void testBlackScholesModel();
