#include"ContinuousTimeOptionBase.h"
#include"MonteCarloPricer.h"
#include"CallOption.h"
#include"stdafx.h"
#include"matlib.h"

using namespace std;
double ContinuousTimeOptionBase::price(
		const BlackScholesModel& model) const{
	MonteCarloPricer pricer;
	return pricer.price(*this, model);
}

/////////////////////////////////
// UNIT TEST
/////////////////////////////	

static void testPrice(){
	rng("default");

	BlackScholesModel bsm;
	bsm.volatility(0.1);
	bsm.stockPrice(100);

	CallOption callOption;
	callOption.strike(100);
	callOption.maturity(1.0);

	ContinuousTimeOptionBase& o1 = callOption;

	double p1 = o1.price(bsm);
	// ASSERT_APPROX_EQUAL( p1, p2, 0.1);
	ASSERT_APPROX_EQUAL( p1, 3.98, 0.1);
}

void testContinuousTimeOptionBase(){
	TEST(testPrice);
}
