#ifndef BONDINQUIRYCONNECTOR_HPP
#define BONDINQUIRYCONNECTOR_HPP

#include "soa.hpp"
#include "products.hpp"
#include "inquiryservice.hpp"
#include "BondInquiryService.h"
#include <fstream>
#include <string>

class BondInquiryConnector : public Connector<Inquiry<Bond>>
{
private:
	BondInquiryService *inquiry;
public:
	//default constructor
	BondInquiryConnector(){}
	BondInquiryConnector(BondInquiryService* source);

	void GetInquiryFromFile(string address);

	// Publish data to the Connector
	virtual void Publish(Inquiry<Bond> &data);
};

BondInquiryConnector::BondInquiryConnector(BondInquiryService *source) {
	inquiry = source;
}

void BondInquiryConnector::GetInquiryFromFile(string address)
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
		token = value[4].substr(0, value[1].find('-'));
		value[4].erase(0, value[3].find('-') + 1);
		price = stoi(token) + stoi(value[3].substr(0, 2)) / 32.0 + stoi(value[3].substr(2, 3)) / 256.0;
		quantity = stoi(value[3]);
		if (value[1] == "912828U40")
		{
			if (value[2] == "BUY") inquiry->OnMessage(Inquiry<Bond>(value[0], b2, BUY, quantity, price, RECEIVED));
			else inquiry->OnMessage(Inquiry<Bond>(value[0], b2, SELL, quantity, price, RECEIVED));
		}
		else if (value[1] == "912828U32")
		{
			if (value[2] == "BUY") inquiry->OnMessage(Inquiry<Bond>(value[0], b3, BUY, quantity, price, RECEIVED));
			else inquiry->OnMessage(Inquiry<Bond>(value[0], b2, SELL, quantity, price, RECEIVED));
		}
		else if (value[1] == "912828U65")
		{
			if (value[2] == "BUY") inquiry->OnMessage(Inquiry<Bond>(value[0], b5, BUY, quantity, price, RECEIVED));
			else inquiry->OnMessage(Inquiry<Bond>(value[0], b2, SELL, quantity, price, RECEIVED));
		}
		else if (value[1] == "912828U57")
		{
			if (value[2] == "BUY") inquiry->OnMessage(Inquiry<Bond>(value[0], b7, BUY, quantity, price, RECEIVED));
			else inquiry->OnMessage(Inquiry<Bond>(value[0], b2, SELL, quantity, price, RECEIVED));
		}
		else if (value[1] == "912828U24")
		{
			if (value[2] == "BUY") inquiry->OnMessage(Inquiry<Bond>(value[0], b10, BUY, quantity, price, RECEIVED));
			else inquiry->OnMessage(Inquiry<Bond>(value[0], b2, SELL, quantity, price, RECEIVED));
		}
		else if (value[1] == "912810RU4")
		{
			if (value[2] == "BUY") inquiry->OnMessage(Inquiry<Bond>(value[0], b30, BUY, quantity, price, RECEIVED));
			else inquiry->OnMessage(Inquiry<Bond>(value[0], b2, SELL, quantity, price, RECEIVED));
		}
	}
}



void BondInquiryConnector::Publish(Inquiry<Bond> &data)
{
	data.SetState(QUOTED);
	inquiry->OnMessage(data);
}

#endif // !BONDINQUIRYCONNECTOR_HPP

