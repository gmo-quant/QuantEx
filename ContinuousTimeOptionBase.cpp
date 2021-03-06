#include"ContinuousTimeOptionBase.h"
#include"MonteCarloPricer.h"
#include"UpAndOutOption.h"
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

	UpAndOutOption knockoutOption;
	knockoutOption.strike(100);
	knockoutOption.maturity(1.0);
	knockoutOption.barrier(1000);
	
	// why use reference?  is it because COB is abstract or ?
	ContinuousTimeOptionBase& o1 = callOption;
	ContinuousTimeOptionBase& o2 = knockoutOption;

	double p1 = o1.price(bsm);
	double p2 = o2.price(bsm);
	//why compare with p1 and p2?
	ASSERT_APPROX_EQUAL( p1, p2, 0.1);
	// ASSERT_APPROX_EQUAL( p1, 3.98, 0.1);
}

void testContinuousTimeOptionBase(){
	std::cout << YELLOW "Test ContinuousTimeOptionBase" RESET << std::endl;
	TEST(testPrice);
}
