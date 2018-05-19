#include"matlib.h"
#include"BlackScholesModel.h"
#include"CallOption.h"
#include"PUtOption.h"
#include"MonteCarloPricer.h"
#include"UpAndOutOption.h"

int main(){
	testBlackScholesModel();
	testCallOption();
	testPutOption();
	testMonteCarloPricer();
	testContinuousTimeOptionBase();
	testUpAndOutOption();
	return 0;
}