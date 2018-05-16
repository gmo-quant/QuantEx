#include"matlib.h"
#include"BlackScholesModel.h"
#include"CallOption.h"
#include"MonteCarloPricer.h"

int main(){
	testBlackScholesModel();
	testCallOption();
	testMonteCarloPricer();
	return 0;
}