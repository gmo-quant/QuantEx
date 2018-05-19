#pragma once

#include"BlackScholesModel.h"
#include"ContinuousTimeOption.h"

/**
 *  Convenience class for eliminating the drudgery of
 *  writing option classes
 */
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

	double maturity() const{ return _maturity;}

	void maturity(double maturity){
		_maturity = maturity;
	}
	
	double strike() const{return _strike;}
	
	void strike(double strike){
		_strike = strike;
	}
	
private:
	double _maturity;
	double _strike;
};

////////////////////////
// UNIT TEST
/////////////////////////

void testContinuousTimeOptionBase();