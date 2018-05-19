#include"PutOption.h"
#include"matlib.h"

double PutOption::payoff( const std::vector<double>& stockPrices) const {
	double stockAtMaturity = stockPrices.back();
	if (stockAtMaturity < strike()){
		return strike() - stockAtMaturity;
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
	double K = strike();
	double sigma = bsm.volatility();
	double R = bsm.riskFreeRate();
	double T = maturity() - bsm.date();

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

	std::vector<double> d;
	d.push_back(110.0);
	ASSERT_APPROX_EQUAL(putOption.payoff(d), 0.0, 0.001);
	d[0] = 100.0;
	ASSERT_APPROX_EQUAL(putOption.payoff(d), 5.0, 0.001);
}
static void testPutOptionPrice(){
	PutOption PutOption;
	PutOption.strike(105.0);
	PutOption.maturity(2.0);

	BlackScholesModel bsm;
	bsm.date(1.0);
	bsm.volatility(0.1);
	bsm.riskFreeRate(0.05);
	bsm.stockPrice(100.0);

	double price = PutOption.price(bsm);
	ASSERT_APPROX_EQUAL(price, 3.925, 0.01);
}
void testPutOption(){
	std::cout << YELLOW "Test PutOption" RESET << std::endl;
	TEST(testPayoff);
	TEST(testPutOptionPrice);
}