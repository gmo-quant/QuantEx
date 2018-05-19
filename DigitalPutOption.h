#pragma once
#include "PathIndependentOption.h"

class DigitalPutOption :
	public PathIndependentOption{
public:
	double payoff(double stockAtMaturity) const{
		if (stockAtMaturity > strike()){
			return 0.0;
		}else{
			return 1.0;
		}
	}
};

void testDigitalPutOption();