#pragma once
#include"BlackScholesModel.h"

class Priceable{
public:
	/* 
	 * Compute the price of the security via Black--Scholes Model
	 */
	virtual double price(
		const BlackScholesModel& model) const = 0;
};