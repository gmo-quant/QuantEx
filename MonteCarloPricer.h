#pragma once

#include"stdafx.h"
#include"BlackScholesModel.h"
#include"CallOption.h"

class MonteCarloPricer{
public:
	MonteCarloPricer();
	double price(const CallOption& option, 
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