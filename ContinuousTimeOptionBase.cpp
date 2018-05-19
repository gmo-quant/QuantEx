#include"ContinuousTimeOptionBase.h"
#include"MonteCarloPricer.h"
// #include"CallOption.h"

double ContinuousTimeOptionBase::price(
		const BlackScholesModel& model) const{
	MonteCarloPricer pricer;
	return pricer.price(*this, model);
}

/////////////////////////////////
// UNIT TEST
/////////////////////////////	

static void testPrice(){}

void testContinuousTimeOptionBase(){
	TEST(testPrice);
}
