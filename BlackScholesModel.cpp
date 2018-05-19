#include"BlackScholesModel.h"
#include"matlib.h"	
#include"LineChart.h"
/*
 * constructors
 */
BlackScholesModel::BlackScholesModel():
	_stockPrice(0.0),
	_volatility(0.0),
	_riskFreeRate(0.0),
	_date(0.0),
	_drift(0.0) {}

BlackScholesModel::BlackScholesModel(double s): _stockPrice(s){}

/*
 * generate a simulated stock price path
 * @param
 * toDate: a final date
 * nSteps: number of steps
 */
std::vector<double> BlackScholesModel::generatePricePath(double toDate, int nSteps) const{
	return generatePricePath( toDate, nSteps, _drift );
}

/* 
 * behave same as generatePricePath(), except that it
 * use Q-measure to compute the path,
 */
std::vector<double> BlackScholesModel::generateRiskNeutralPricePath(double toDate, int nSteps) const{
	return generatePricePath(toDate, nSteps, _riskFreeRate);
}



/* 
 * private method allow you to choose the drift in the simulation of the price path
 * it is private because we've only created it to make the implementation easier.
 */
std::vector<double> BlackScholesModel::generatePricePath(double toDate, int nSteps, double drift) const{
	std::vector<double> path(nSteps, 0.0);
	std::vector<double> epsilon = randn(nSteps);
	double dt = (toDate - _date) / nSteps;
	double a = (drift  - _volatility * _volatility * 0.5) * dt;
	double b = _volatility * sqrt(dt);
	double currentLogS = log(_stockPrice);

	for (int i = 0; i < nSteps; i++){
		double dLogS =  a + b * epsilon[i];
		double logS = currentLogS + dLogS;
		path[i] = exp (logS);
		currentLogS = logS;
	}
	return path;
}

/////////////////////////////////
// UNIT TEST
/////////////////////////////

static void testRiskNeutralPricePath() {
    rng("default");

    BlackScholesModel bsm;
    bsm.riskFreeRate(0.05);
    bsm.volatility(0.1);
    bsm.stockPrice(100.0);
    bsm.date(2.0);

    int nPaths = 10000;
    int nsteps = 5;
    double maturity = 4.0;
    std::vector<double> finalPrices(nPaths,0.0);
    for (int i=0; i<nPaths; i++) {
        std::vector<double> path =
            bsm.generateRiskNeutralPricePath( maturity,
                                              nsteps );
        finalPrices[i] = path.back();
    }
    ASSERT_APPROX_EQUAL( mean( finalPrices ),
        exp( bsm.riskFreeRate()*2.0)*bsm.stockPrice(), 0.5);
}

static void testVisually(){
	BlackScholesModel bsm;
	bsm.riskFreeRate(0.05);
	bsm.volatility(0.1);
	bsm.stockPrice(100.0);
	bsm.date(2.0);

	int nSteps = 1000;
	double maturity = 4.0;
	std::vector<double> path =  bsm.generatePricePath(maturity, nSteps);
	double dt = (maturity - bsm.date()) / nSteps;
	std::vector<double> times = linspace(dt, maturity, nSteps);
	LineChart lineChart;
	lineChart.setTitle("Stock Price Path");
	lineChart.setSeries(times, path);
	lineChart.writeAsHTML("examplePricePath.html");
}
void testBlackScholesModel(){
	std::cout << YELLOW "Test BlackScholesModel" RESET << std::endl;
	TEST( testRiskNeutralPricePath);
	TEST( testVisually ); 
}