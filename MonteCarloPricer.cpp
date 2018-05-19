#include"MonteCarloPricer.h"
#include"matlib.h"

using namespace std;

MonteCarloPricer::MonteCarloPricer(): nScenarios(10000){}

double MonteCarloPricer::price(const ContinuousTimeOption& option, 
			const BlackScholesModel& model){
	double total = 0.0;
	for (int i = 0; i < nScenarios; i++){
		vector<double> path = model.generateRiskNeutralPricePath(option.getMaturity(), 1);
		double stockPrice = path.back();
		double payoff = option.payoff(stockPrice);
		total += payoff;
	}

	double mean = total / nScenarios;
	double R = model.riskFreeRate();
	double T = option.getMaturity() - model.date();

	return exp(-R * T) * mean;
}

/////////////////////////////
// UNIT TEST
//////////////////////

static void testPriceCallOption(){
	rng("default");
	CallOption callOption;
	callOption.strike(110);
	callOption.maturity(2.0);

	BlackScholesModel model;
	model.volatility(0.1);
	model.riskFreeRate(0.05);
	model.stockPrice(100.0);
	model.drift(0.1);
	model.date(1.0);

	MonteCarloPricer pricer;
	double price = pricer.price(callOption, model);
	double expected =  callOption.price(model);

	ASSERT_APPROX_EQUAL(price, expected, 0.1);
}

void testMonteCarloPricer(){
	TEST(testPriceCallOption);
}