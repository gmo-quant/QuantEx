#include"Portfolio.h"
#include"CallOption.h"
#include"PutOption.h"

using namespace std;

/*  
 *  By using an abstract interface class with a factory constructor
 *  and only having the implementation in the C++ file we increase information
 *  hiding. Nobody knows about the PortfolioImpl class outside of the C++ file,
 *  so we can change it without any impact on anything else.
 */

class PortfolioImpl:public Portfolio{
public:
	/* 	Returns the number of items in the portfolio*/
	int size() const;
	/* 	add a new security to the portfolio, 
		returns the index at which is was added*/
	int add(double quantity, 
		std::shared_ptr<Priceable> security);
	/*  Update the quantity at a given index */
    void setQuantity( int index, double quantity );
    /*  Compute the current price */
    double price(
	    const BlackScholesModel& model ) const;

    // Nobody knows about the PortfolioImpl class outside of the C++ file
    // so be convienent, data member are public.
    vector<double> quantities;
    vector< shared_ptr<Priceable> > securities;
};

int PortfolioImpl::size() const{
	return quantities.size();
}

int PortfolioImpl::add(double quantity,
		shared_ptr<Priceable> security ){
	quantities.push_back(quantity);
	securities.push_back(security);
	return quantities.size();
}

double PortfolioImpl::price(
		const BlackScholesModel& model) const{
	double ret = 0;
	int size = this->size();
	for (int i=0; i<size; i++){
		ret += quantities[i] * securities[i]->price(model);
	}
	return ret;
}

void PortfolioImpl::setQuantity(int index,
		double quantity){
	quantities[index] = quantity;
}

/** 
 * create a portfolio
 */
shared_ptr<Portfolio> Portfolio::newPortfolio(){
	shared_ptr<Portfolio> ret = make_shared<PortfolioImpl>();
	return ret;
}	