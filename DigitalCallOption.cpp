#include"DigitalCallOption.h"
#include"MonteCarloPricer.h"
#include"matlib.h"

static void testMonteCarloPrice(){
	rng("default");
	DigitalCallOption option;
	option.maturity(1.0);
	option.strike(100.0);
	BlackScholesModel model;
	model.drift(0.0);
	model.stockPrice(100.0);
	model.volatility(0.2);
	model.riskFreeRate(0.0);
	MonteCarloPricer pricer;
	double price = pricer.price(option, model);
	ASSERT_APPROX_EQUAL(price, 0.5, 0.1);
}

void testDigitalCallOption() {
	TESTCase(DigitalCallOption);
	TEST(testMonteCarloPrice);
}