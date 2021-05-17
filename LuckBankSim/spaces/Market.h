#pragma once
class Market
{
private:
	int	  MarketPrice;
	int   MarketFees;
public:
	void setMarketPrice(int a);
	int getMarketPrice();
	void setMarketFees(int a);
	int getMarketFees();
	explicit Market();
};

