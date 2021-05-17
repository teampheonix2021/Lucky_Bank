#include "Market.h"


Market::Market() {};

void Market::setMarketPrice(int a)
{
	MarketPrice = a;
}

int Market::getMarketPrice()
{
	return MarketPrice;
}

void Market::setMarketFees(int x)
{
	MarketFees = x;
}

int Market::getMarketFees()
{
	return MarketFees;
}
