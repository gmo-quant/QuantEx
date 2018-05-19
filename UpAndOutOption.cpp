#include"UpAndOutOption.h"
#include"KnockoutOption.h"

using namespace std;

double UpAndOutOption::payoff(
		const vector<double>& prices) const{
	int size = prices.size();
	for (int i = 0; i < size; i++ ){
		if (prices[i] > barrier()){
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

//////////////////////////////
// UNIT TESTS
//////////////////////////////

static void testPayoff(){
	UpAndOutOption o;
	o.barrier(100);
	o.strike(70);
	vector<double> prices;
	prices.push_back(120);
	prices.push_back(80);
	ASSERT_APPROX_EQUAL(o.payoff(prices), 0.0, 0.001);
	prices[0] = 90;
	ASSERT_APPROX_EQUAL(o.payoff(prices), 10.0, 0.001);
	prices[1] = 60;
	ASSERT_APPROX_EQUAL(o.payoff(prices), 0.0, 0.001);
}

void testUpAndOutOption(){
	std::cout << YELLOW "Test UpAndOutOption" RESET << std::endl;
	TEST( testPayoff);
}