#include "City.h"
#include <vector>
#include <sstream>
using namespace std;

City::City() {};


void City::setGroup(int a)
{
	G.Group = a;
}


void City::setPrice(int x)
{
	Price = x;
}

void City::setFees(int x)
{
	PassingFees = x;
}

int City::getPrice()
{
	return Price;
}

int City::getFees()
{
	return PassingFees;
}
