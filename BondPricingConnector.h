#ifndef BONDPRICINGCONNECTOR_HPP
#define BONDPRICINGCONNECTOR_HPP

#include "soa.hpp"
#include "products.hpp"
#include "pricingservice.hpp"
#include "BondPricingService.h"
#include <fstream>
using namespace std;

class BondPricingConnector : public Connector<Price<Bond>>
{
private:
	BondPricingService *bondPricingservice;
public:
	BondPricingConnector() {};
	BondPricingConnector(BondPricingService *source);

	void GetPriceFromFile(string address);
};

BondPricingConnector::BondPricingConnector(BondPricingService *source)
{
	bondPricingservice = source;
	
}

void BondPricingConnector::GetPriceFromFile(string address)
{
	Bond b2("912828U40", CUSIP, "T", 100.0, 1.00, date(2018, Nov, 30));
	Bond b3("912828U32", CUSIP, "T", 100.0, 1.00, date(2019, Nov, 30));
	Bond b5("912828U65", CUSIP, "T", 100.0, 1.75, date(2021, Nov, 30));
	Bond b7("912828U57", CUSIP, "T", 100.0, 2.125, date(2023, Nov, 30));
	Bond b10("912828U24", CUSIP, "T", 100.0, 2.00, date(2026, Nov, 30));
	Bond b30("912810RU4", CUSIP, "T", 100.0, 2.875, date(2046, Nov, 30));
	fstream log(address);
	string value[3];
	string line;
	string token;
	double price;
	double spread;

	while (getline(log, line))
	{
		istringstream input(line);
		for (int i = 0; i < 3; i++)
		{
			getline(input, value[i], ',');
		}
		token = value[1].substr(0, value[1].find('-'));
		value[1].erase(0, value[1].find('-') + 1);
		price = stoi(token) + stoi(value[1].substr(0, 2)) / 32.0 + stoi(value[1].substr(2, 3)) / 256.0;
		spread = stoi(value[2]) / 256.0;
		if (value[0] == "912828U40")
		{
			bondPricingservice->OnMessage(Price<Bond>(b2, price, spread));
		}
		else if (value[0] == "912828U32")
		{
			bondPricingservice->OnMessage(Price<Bond>(b3, price, spread));
		}
		else if (value[0] == "912828U65")
		{
			bondPricingservice->OnMessage(Price<Bond>(b5, price, spread));
		}
		else if (value[0] == "912828U57")
		{
			bondPricingservice->OnMessage(Price<Bond>(b7, price, spread));
		}
		else if (value[0] == "912828U24")
		{
			bondPricingservice->OnMessage(Price<Bond>(b10, price, spread));
		}
		else if (value[0] == "912810RU4")
		{
			bondPricingservice->OnMessage(Price<Bond>(b30, price, spread));
		}
	}

}
#endif // !BONDPRICINGCONNECTOR_HPP
