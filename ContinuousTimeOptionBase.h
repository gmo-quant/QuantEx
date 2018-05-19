#pragma once
#include"BlackScholesModel.h"
#include"ContinuousTimeOption.h"

class ContinuousTimeOptionBase: 
	public ContinuousTimeOption{
public:
	virtual ~ContinuousTimeOptionBase(){}

    /*  
     *  Convenience method to calculate an approximate price
     *  for the option using the most appropriate method for
     *  the given option. Note that since you can't control
     *  the accuracy of the calculation this isn't a good method
     *  for general use, but is handy for tests.
     */
	virtual double price(
		const BlackScholesModel& model) const;

	double getMaturity() const{ return maturity;}

	void setMaturity(double maturity){
		this->maturity = maturity;
	}
	
	double getStrike() const{return strike;}
	
	void setStrike(double strike){
		this->strike = strike;
	}
	
private:
	double maturity;
	double strike;
};

////////////////////////
// UNIT TEST
/////////////////////////
void testContinuousTimeOptionBase();