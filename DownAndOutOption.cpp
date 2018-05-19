#include"DownAndOutOption.h"
#include"KnockoutOption.h"

using namespace std;

double DownAndOutOption::payoff(
		const vector<double>& prices) const{
	int size = prices.size();
	for (int i = 0; i < size; i++){
		if(prices[i] < barrier()){
			return 0.0;
		}
	}
	double stockAtMaturity = prices.back();
	if (stockAtMaturity > strike()){
		return stockAtMaturity - strike();
	}else{
		return 0.0;
	}
}

/////////////////////////
///// UNIT TEST
////////////

static void testPayoff(){}

void testDownAndOutOption(){
	TESTCase(DownAndOutOption);
	TEST(testPayoff);
}