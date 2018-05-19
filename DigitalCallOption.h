#pragma once

#include"PathIndependentOption.h"

class DigitalCallOption :
	public PathIndependentOption{
public:
	double payoff(double stockAtMaturity) const{
		if(stockAtMaturity > strike()){
			return 1.0;
		}else{
			return 0.0;
		}
	}
};

void testDigitalCallOption();