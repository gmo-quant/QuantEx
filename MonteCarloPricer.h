#pragma once

#include"stdafx.h"
#include"BlackScholesModel.h"
#include"ContinuousTimeOption.h"

class MonteCarloPricer{
public:
	MonteCarloPricer();
	double price(const ContinuousTimeOption& option, 
				const BlackScholesModel& model);
	// double price(const PathIndependentOption& option, 
	// 			const BlackScholesModel& model);
private:
	int nScenarios; // number of scenarios
};

/////////////////////////////////
// UNIT TEST
//////////////////////////////////////

void testMonteCarloPricer();