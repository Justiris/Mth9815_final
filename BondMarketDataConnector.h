#ifndef BONDMARKETDATACONNECTOR_HPP
#define BONDMARKETDATACONNECTOR_HPP

#include "soa.hpp"
#include "products.hpp"
#include "marketdataservice.hpp"
#include "BondMarketDataService.h"
#include <fstream>
using namespace std;

class BondMarketDataConnector : public Connector<OrderBook<Bond>>
{
private:
	BondMarketDataService *bondmarketdataservice;
public:
	BondMarketDataConnector() {};
	BondMarketDataConnector(BondMarketDataService *source);

	void GetMarketDataFromFile(string address);
};

BondMarketDataConnector::BondMarketDataConnector(BondMarketDataService *source)
{
	bondmarketdataservice = source;
}

void BondMarketDataConnector::GetMarketDataFromFile(string address)
{
	Bond b2("912828U40", CUSIP, "T", 100.0, 1.00, date(2018, Nov, 30));
	Bond b3("912828U32", CUSIP, "T", 100.0, 1.00, date(2019, Nov, 30));
	Bond b5("912828U65", CUSIP, "T", 100.0, 1.75, date(2021, Nov, 30));
	Bond b7("912828U57", CUSIP, "T", 100.0, 2.125, date(2023, Nov, 30));
	Bond b10("912828U24", CUSIP, "T", 100.0, 2.00, date(2026, Nov, 30));
	Bond b30("912810RU4", CUSIP, "T", 100.0, 2.875, date(2046, Nov, 30));
	fstream log(address);
	string value[4];
	string line;
	string token, reminder;
	double price;
	double quantity;
	vector<Order> bidstack1;
	vector<Order> bidstack2;
	vector<Order> bidstack3;
	vector<Order> bidstack4;
	vector<Order> bidstack5;
	vector<Order> bidstack6;
	vector<Order> offerstack1;
	vector<Order> offerstack2;
	vector<Order> offerstack3;
	vector<Order> offerstack4;
	vector<Order> offerstack5;
	vector<Order> offerstack6;

	while (getline(log, line))
	{
		istringstream input(line);
		for (int i = 0; i < 4; i++)
		{
			getline(input, value[i], ',');
		}
		token = value[1].substr(0, value[1].find('-'));
		value[1].erase(0, value[1].find('-') + 1);
		price = stoi(token) + stoi(value[1].substr(0, 2)) / 32.0 + stoi(value[1].substr(2, 3)) / 256.0;
		quantity = stoi(value[2]);
		if (value[0] == "912828U40")
		{
			if (value[3] == "BID") bidstack1.push_back(Order(value[0], price, quantity, BID));
			else offerstack1.push_back(Order(value[0], price, quantity, OFFER));
		}
		else if (value[0] == "912828U32")
		{
			if (value[3] == "BID") bidstack2.push_back(Order(value[0], price, quantity, BID));
			else offerstack2.push_back(Order(value[0], price, quantity, OFFER));
		}
		else if (value[0] == "912828U65")
		{
			if (value[3] == "BID") bidstack3.push_back(Order(value[0], price, quantity, BID));
			else offerstack3.push_back(Order(value[0], price, quantity, OFFER));
		}
		else if (value[0] == "912828U57")
		{
			if (value[3] == "BID") bidstack4.push_back(Order(value[0], price, quantity, BID));
			else offerstack4.push_back(Order(value[0], price, quantity, OFFER));
		}
		else if (value[0] == "912828U24")
		{
			if (value[3] == "BID") bidstack5.push_back(Order(value[0], price, quantity, BID));
			else offerstack5.push_back(Order(value[0], price, quantity, OFFER));
		}
		else if (value[0] == "912810RU4")
		{
			if (value[3] == "BID") bidstack6.push_back(Order(value[0], price, quantity, BID));
			else offerstack6.push_back(Order(value[0], price, quantity, OFFER));
		}

	}
	OrderBook<Bond> ob2(b2, bidstack1, offerstack1);
	OrderBook<Bond> ob3(b3, bidstack2, offerstack2);
	OrderBook<Bond> ob5(b5, bidstack3, offerstack3);
	OrderBook<Bond> ob7(b7, bidstack4, offerstack4);
	OrderBook<Bond> ob10(b10, bidstack5, offerstack5);
	OrderBook<Bond> ob30(b30, bidstack6, offerstack6);
	bondmarketdataservice->OnMessage(ob2);
	bondmarketdataservice->OnMessage(ob3);
	bondmarketdataservice->OnMessage(ob5);
	bondmarketdataservice->OnMessage(ob7);
	bondmarketdataservice->OnMessage(ob10);
	bondmarketdataservice->OnMessage(ob30);
}

#endif // !BONDMARKETDATACONNECTOR_HPP

