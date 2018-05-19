#include"matlib.h"
#include"BlackScholesModel.h"
#include"CallOption.h"
#include"PUtOption.h"
#include"MonteCarloPricer.h"
#include"UpAndOutOption.h"
#include"DownAndOutOption.h"
#include"DigitalCallOption.h"
#include"DigitalPutOption.h"

int main(){
	testBlackScholesModel();
	testCallOption();
	testPutOption();
	testMonteCarloPricer();
	testContinuousTimeOptionBase();
	testUpAndOutOption();
	testDownAndOutOption();
	testDigitalCallOption();
	testDigitalPutOption();
	return 0;
}