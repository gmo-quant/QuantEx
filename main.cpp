#include"matlib.h"
#include"BlackScholesModel.h"
#include"CallOption.h"
#include"PUtOption.h"
#include"MonteCarloPricer.h"

int main(){
	testBlackScholesModel();
	testCallOption();
	testPutOption();
	testMonteCarloPricer();
	testContinuousTimeOptionBase();
	return 0;
}