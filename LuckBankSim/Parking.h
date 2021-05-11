#pragma once
class Parking
{
private:
	int GaragePrice;
	int GarageFees;
public:
	explicit Parking();
	void setGaragePrice(int a);
	int getGaragePrice();
	void setGarageFees(int a);
	int getGarageFees();
};

