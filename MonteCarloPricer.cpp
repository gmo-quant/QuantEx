#include"MonteCarloPricer.h"
#include"CallOption.h"
#include"matlib.h"

using namespace std;

MonteCarloPricer::MonteCarloPricer(): 
	_nScenarios(10000),
	_nSteps(10){}

double MonteCarloPricer::price(
		const ContinuousTimeOption& option, 
		const BlackScholesModel& model){
	int nSteps = _nSteps;
	if (!option.isPathDependent()){
		nSteps = 1;
	}
	double total = 0.0;
	for (int i = 0; i < _nScenarios; i++){
		vector<double> path = 
			model.generateRiskNeutralPricePath(
				option.maturity(), nSteps);
		// double stockPrice = path.back();
		double payoff = option.payoff(path);
		total += payoff;
	}

	double mean = total / _nScenarios;
	double R = model.riskFreeRate();
	double T = option.maturity() - model.date();

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
	std::cout << YELLOW "Test MonteCarloPricer" RESET << std::endl;
	TEST(testPriceCallOption);
}