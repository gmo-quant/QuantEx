#pragma once

#include"stdafx.h"
#include"BlackScholesModel.h"
#include"ContinuousTimeOption.h"

class MonteCarloPricer{
public:
	MonteCarloPricer();
	double price(const ContinuousTimeOption& option, 
				const BlackScholesModel& model);
private:
	int _nScenarios; // number of scenarios
	int _nSteps;
};

/////////////////////////////////
// UNIT TEST
//////////////////////////////////////

void testMonteCarloPricer();