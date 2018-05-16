#pragma once

class BlackScholesModel{
public:
	/*
	 * constructors
	 */
	BlackScholesModel();
	explicit BlackScholesModel(double stockPrice);


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
};


/////////////////////////////////////
// UNIT TEST
///////////////////////////////////////////
void testBlackScholesModel();
