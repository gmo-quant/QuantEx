#pragma once

#include "KnockoutOption.h"

class DownAndOutOption :
	public KnockoutOption{
public:
	double payoff(
		const std::vector<double>& prices) const;
};

void testDownAndOutOption();