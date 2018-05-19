#include"matlib.h"
#include"BlackScholesModel.h"
#include"CallOption.h"
#include"PUtOption.h"
#include"MonteCarloPricer.h"
#include"UpAndOutOption.h"
#include"DownAndOutOption.h"

int main(){
	testBlackScholesModel();
	testCallOption();
	testPutOption();
	testMonteCarloPricer();
	testContinuousTimeOptionBase();
	testUpAndOutOption();
	testDownAndOutOption();
	return 0;
}