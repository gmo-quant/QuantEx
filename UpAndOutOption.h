#pragma once

#include "KnockoutOption.h"

class UpAndOutOption: public KnockoutOption{
public:
	double payoff(
		const std::vector<double>& prices) const;
	double price(
		const BlackScholesModel& model) const{
		if (model.stockPrice() >= barrier()){
			return 0;
		}else{
			return KnockoutOption::price(model);
		}
	}
};

void testUpAndOutOption();