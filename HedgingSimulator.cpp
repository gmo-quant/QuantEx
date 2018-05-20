#include"HedgingSimulator.h"
#include"testing.h"
#include"matlib.h"

using namespace std;

HedgingSimulator::HedgingSimulator(){
	//Choose default models and options
	shared_ptr<BlackScholesModel> model(new BlackScholesModel());
	model->stockPrice(1);
	model->date(0);
	model->riskFreeRate(0.05);
	model->volatility(0.2);
	model->drift(0.10);

	shared_ptr<CallOption> option = make_shared<CallOption>();
	// shared_ptr<CallOption> option(new CallOption());
	option->strike(model->stockPrice());
	option->maturity(1);

	setToHedge(option);
	setSimulationModel(model);
	setPricingModel(model);
	setNSteps(10);
}

/* Runs a number of simulations and returns a
 * vector of the profit and loss 
 */
std::vector<double>
	HedgingSimulator::runSimulations(
							int nSimulations)const{
		std::vector<double> ret(nSimulations);
		for(int i = 0; i < nSimulations; i++){
			ret[i] = runSimulation();
		}
		return ret;
}
/* Run a simulation and compute the profit and loss*/
double HedgingSimulator::runSimulation() const{
	double T = _toHedge->maturity();
	double S0 = _simulationModel->stockPrice();
	vector<double> pricePath = 
		_simulationModel->generatePricePath(T, _Steps);
	double dt = T/ _nSteps;
	double charge = chooseCharge(S0);
	double stockQuantity = selectStockQuantity(0, S0);
	double bankBalance = charge - stockQuantity * S0;
	for (int i = 0; i < _nSteps - 1; i++){
		double balanceWithInterest = bankBalance * 
			exp(_simulationModel->riskFreeRate() * dt);
		double S = pricePath[i];
		double date = dt*(i+1);
		double newStockQuantity = 
			selectStockQuantity(date, S);
		double costs = 
			(newStockQuantity - stockQuantity) * S;
		bankBalance = balanceWithInterest - costs;
		stockQuantity = newStockQuantity;
	}
	double balanceWithInterest = bankBalance *
		exp(_simulationModel->riskFreeRate() * dt);
	double S = pricePath[_nSteps - 1];
	double stockValue = stockQuantity * S;
	double payout = _toHedge->payoff(S);
	return balanceWithInterest + stockValue - payout;
}

/* How much should we charge the customer */
double HedgingSimulator::chooseCharge(
						double stockPrice) const{
	// create a copy of the pricing model
	BlackScholesModel pm = * _pricingModel;
	pm.stockPrice(stockPrice);
	return _toHedge->price(pm);
}

/* how much stock should we hold*/
double HedgingSimulator::selectStockQuantity(
		double date,
		double stockPrice) const {
	// create a copy of the pricing model
	BlackScholesModel pm = * _pricingModel;
	pm.stockPrice(stockPrice);
	pm.date(date);
	return _toHedge->delta(pm);
}
////////////////////////
// UNIT TEST
////////////////////////

void testHedgingSimulator(){

}
