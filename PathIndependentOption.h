#pragma once

class PathIndependentOption{
public:
	/* virtual destructor */
	virtual ~PathIndependentOption(){}
	/* compute and return payoff at maturity */
	virtual double payoff(double finalStockPrice) const=0;
	/* return the maturity of the option*/
	virtual double maturity() const = 0;
};