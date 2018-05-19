#pragma once

#include "stdafx.h"
#include "Priceable.h"

/**
 * A　Portfolio contains options in various quantities
 */

class Portfolio: public Priceable{
public:
	/* virtual destructor*/
	virtual ~Portfolio(){};
	/* Returns the number of items in the portfolio*/
	virtual int size() const = 0;
	/* add a new security to the portfolio, 
		returns the index at which is was added*/
	virtual int add(double quantity, 
		std::shared_ptr<Priceable> security)  = 0;
	/*	update the quantity at a given index */
	virtual void setQuantity(int index, double quantity) = 0;
	/* compute the current price*/
	virtual double price(
		const BlackScholesModel& model) const = 0;
	/* creates a portfolio*/
	static std::shared_ptr<Portfolio> newPortfolio();	
};

void testPortfolio();