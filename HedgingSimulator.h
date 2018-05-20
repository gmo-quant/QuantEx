#pragma once

#include"stdafx.h"
#include"BlackScholesModel.h"
#include"CallOption.h"

/**
 * simulate the delta hedging strategy
 */

class HedgingSimulator{
public:
	/* runs a number of simulations
	 * and returns a vector of the profit and loss
	 */
	std::vector<double> runSimulations(
			int nSimulations) const;

	void setToHedge(
		std::shared_ptr<CallOption> toHedge){
		_toHedge = toHedge;
	}

	void setSimulationModel(
		std::shared_ptr<BlackScholesModel> model){
		_simulationModel = model;
	}

	void setPricingModel(
		std::shared_ptr<BlackScholesModel> model){
		_pricingModel = model;
	}

	void setNSteps(int nSteps){
		_nSteps = nSteps;
	}
	/* default constructor */
	HedgingSimulator();
private:
	/* the option that has been written */
	std::shared_ptr<CallOption> _toHedge;
	/* the model used to simulate stock prices */
	std::shared_ptr<BlackScholesModel> _simulationModel;
	/* the model used to compute prices and delta*/
	std::shared_ptr<BlackScholesModel> _pricingModel;
	/* the number of steps to use*/
	int _nSteps;
	/* Run a simulation and compute the profit and loss*/
	double runSimulations() const;
	/* how much should we charge the customer */
	double chooseCharge(double stockPrice) const;
	/* how much stock should we hold*/
	double selectStockQuantity(
		double date,
		double stockPrice) const;
};

/////////////////////////////
// UNIT TEST
////////////////////////



void testHedgingSimulator();