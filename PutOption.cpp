#include"PutOption.h"
#include"matlib.h"
PutOption::PutOption() : 
		_strike(0.0), 
		_maturity(0.0){}

PutOption::PutOption(double s, double m): _strike(s), _maturity(m){}
/*
 * computes the payoff at maturity
 */
double PutOption::payoff(double stockAtMaturity) const{
	if (stockAtMaturity < _strike){
		return _strike - stockAtMaturity;
	}else{
		return 0.0;
	}
}
/*
 * computes the price given some hypothetical  market data
 * in the form of BlackScholesModel
 */
double PutOption::price(const BlackScholesModel& bsm) const{
	double S = bsm.stockPrice();
	double K = _strike;
	double sigma = bsm.volatility();
	double R = bsm.riskFreeRate();
	double T = _maturity - bsm.date();

	double numerator = 
		log(S/K)  + (R + sigma * sigma * 0.5) * T;
	double denominator = sigma * sqrt(T);
	double d1 = numerator / denominator ;
	double d2 = d1 - denominator;
	return -S * normcdf(-d1)  + exp(-R * T ) * K * normcdf(-d2);
}


///////////////////////
// UNIT TEST
////////////////////////

static void testPayoff(){
	PutOption putOption;
	putOption.strike(105.0);
	putOption.maturity(2.0);

	ASSERT_APPROX_EQUAL(putOption.payoff(110.0), 0.0, 0.001);
	ASSERT_APPROX_EQUAL(putOption.payoff(100.0), 5.0, 0.001);
}
static void testPutOptionPrice(){
	PutOption PutOption(105.0, 2.0);
	// PutOption.strike(105.0);
	// PutOption.maturity(2.0);

	BlackScholesModel bsm;
	bsm.date(1.0);
	bsm.volatility(0.1);
	bsm.riskFreeRate(0.05);
	bsm.stockPrice(100.0);

	double price = PutOption.price(bsm);
	ASSERT_APPROX_EQUAL(price, 3.925, 0.01);
}
void testPutOption(){
	TEST(testPayoff);
	TEST(testPutOptionPrice);
}