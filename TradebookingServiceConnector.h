#pragma once
#ifndef TRADEBOOKINGSERVICECONNECTOR_HPP
#define TRADEBOOKINGSERVICECONNECTOR_HPP

#include "soa.hpp"
#include "tradebookingservice.hpp"
#include "BondTradeBookingService.h"
#include <fstream>

class BondTradeBookingConnector : public Connector<Trade<Bond>>
{
private:
	BondTradeBookingService *tradebookservice;
public:
	BondTradeBookingConnector(BondTradeBookingService* source);
	~BondTradeBookingConnector() {};

	void GetTradeFromFile(string address);
};

BondTradeBookingConnector::BondTradeBookingConnector(BondTradeBookingService* source)
{
	tradebookservice = source;
}

void BondTradeBookingConnector::GetTradeFromFile(string address)
{
	Bond b2("912828U40", CUSIP, "T", 100.0, 1.00, date(2018, Nov, 30));
	Bond b3("912828U32", CUSIP, "T", 100.0, 1.00, date(2019, Nov, 30));
	Bond b5("912828U65", CUSIP, "T", 100.0, 1.75, date(2021, Nov, 30));
	Bond b7("912828U57", CUSIP, "T", 100.0, 2.125, date(2023, Nov, 30));
	Bond b10("912828U24", CUSIP, "T", 100.0, 2.00, date(2026, Nov, 30));
	Bond b30("912810RU4", CUSIP, "T", 100.0, 2.875, date(2046, Nov, 30));
	fstream log(address);
	string value[6];
	string line;
	string token, reminder;
	double price;
	double quantity;

	while (getline(log, line))
	{
		istringstream input(line);
		for (int i = 0; i < 6; i++)
		{
			getline(input, value[i], ',');
		}
		token = value[3].substr(0, value[1].find('-'));
		value[3].erase(0, value[3].find('-') + 1);
		price = stoi(token) + stoi(value[3].substr(0, 2)) / 32.0 + stoi(value[3].substr(2, 3)) / 256.0;
		quantity = stoi(value[4]);
		if (value[0] == "912828U40")
		{
			if (value[5] == "BUY") {
				Trade<Bond> trade(b2, price, value[1], value[2], quantity, BUY);
				tradebookservice->OnMessage(trade);
			}
			else {
				Trade<Bond> trade(b2, price, value[1], value[2], quantity, SELL);
				tradebookservice->OnMessage(trade);
			}
		}
		else if (value[0] == "912828U32")
		{
			if (value[5] == "BUY") {
				Trade<Bond> trade(b3, price, value[1], value[2], quantity, BUY);
				tradebookservice->OnMessage(trade);
			}
			else {
				Trade<Bond> trade(b3, price, value[1], value[2], quantity, SELL);
				tradebookservice->OnMessage(trade);
			}
		}
		else if (value[0] == "912828U65")
		{
			if (value[5] == "BUY") {
				Trade<Bond> trade(b5, price, value[1], value[2], quantity, BUY);
				tradebookservice->OnMessage(trade);
			}
			else {
				Trade<Bond> trade(b5, price, value[1], value[2], quantity, SELL);
				tradebookservice->OnMessage(trade);
			}
		}
		else if (value[0] == "912828U57")
		{
			if (value[5] == "BUY") {
				Trade<Bond> trade(b7, price, value[1], value[2], quantity, BUY);
				tradebookservice->OnMessage(trade);
			}
			else {
				Trade<Bond> trade(b7, price, value[1], value[2], quantity, SELL);
				tradebookservice->OnMessage(trade);
			}
		}
		else if (value[0] == "912828U24")
		{
			if (value[5] == "BUY") {
				Trade<Bond> trade(b10, price, value[1], value[2], quantity, BUY);
				tradebookservice->OnMessage(trade);
			}
			else {
				Trade<Bond> trade(b10, price, value[1], value[2], quantity, SELL);
				tradebookservice->OnMessage(trade);
			}
		}
		else if (value[0] == "912810RU4")
		{
			if (value[5] == "BUY") {
				Trade<Bond> trade(b30, price, value[1], value[2], quantity, BUY);
				tradebookservice->OnMessage(trade);
			}
			else {
				Trade<Bond> trade(b30, price, value[1], value[2], quantity, SELL);
				tradebookservice->OnMessage(trade);
			}
		}
	}
}
#endif