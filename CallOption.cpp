#include"CallOption.h"
#include"matlib.h"
CallOption::CallOption() : _strike(0.0), _maturity(0.0){}
CallOption::CallOption(double s, double m): _strike(s), _maturity(m){}
/*
 * computes the payoff at maturity
 */
double CallOption::payoff(double stockAtMaturity) const{
	if (stockAtMaturity > _strike){
		return stockAtMaturity - _strike;
	}else{
		return 0.0;
	}
}
/*
 * computes the price given some hypothetical  market data
 * in the form of BlackScholesModel
 */
double CallOption::price(const BlackScholesModel& bsm) const{
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
	return S * normcdf(d1)  - exp(-R * T ) * K * normcdf(d2);
}


///////////////////////
// UNIT TEST
////////////////////////
static void testCallOptionPrice(){
	CallOption callOption(105.0, 2.0);
	// callOption.strike(105.0);
	// callOption.maturity(2.0);

	BlackScholesModel bsm;
	bsm.date(1.0);
	bsm.volatility(0.1);
	bsm.riskFreeRate(0.05);
	bsm.stockPrice(100.0);

	double price = callOption.price(bsm);
	ASSERT_APPROX_EQUAL(price, 4.046, 0.01);
}
void testCallOption(){
	TEST(testCallOptionPrice);
}