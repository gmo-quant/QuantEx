#pragma once

#include "ContinuousTimeOptionBase.h"

/**
 * an option with a barrier
 */

class KnockoutOption : 
	public ContinuousTimeOptionBase{
public:
	virtual ~KnockoutOption(){}

	double barrier() const{ return _barrier;}
	void barrier(double barrier){_barrier = barrier;}
	bool isPathDependent() const{return true;}

private:
	double _barrier;
};