#ifndef BONDTRADEBOOKINGSERVICE_HPP
#define BONDTRADEBOOKINGSERVICE_HPP

#include <string>
#include <vector>
#include <set>
#include "soa.hpp"
#include "products.hpp"
#include "tradebookingservice.hpp"

using namespace std;

class BondTradeBookingService : public TradeBookingService<Bond>
{
private:
	map<string, vector<Trade<Bond>>> tradingbook;
	vector<ServiceListener<Trade<Bond>>* >listener;
public:
	//default constructor
	BondTradeBookingService(){}
	BondTradeBookingService(const BondTradeBookingService& source) {
		tradingbook = source.tradingbook;
		listener = source.listener;
	}
	//default destructor
	~BondTradeBookingService(){}

	//Book the trade
	void BookTrade(Trade<Bond> &trade);

	// Get data on our service given a key
	vector<Trade<Bond>>& GetRecord(string key);

	// The callback that a Connector should invoke for any new or updated data
	void OnMessage(Trade<Bond> &data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	void AddListener(ServiceListener<Trade<Bond>> *listener);

	// Get all listeners on the Service.
	const vector< ServiceListener<Trade<Bond>>* >& GetListeners() const;

	//assignment operator
	BondTradeBookingService& operator=(const BondTradeBookingService& source) {
		tradingbook = source.tradingbook;
		listener = source.listener;
		return *this;
	}
};


void BondTradeBookingService::OnMessage(Trade<Bond> &data)
{
	BookTrade(data);
}

void BondTradeBookingService::BookTrade(Trade<Bond> &trade)
{
	string key = trade.GetProduct().GetProductId();
	tradingbook[key].push_back(trade);
	for (int i = 0; i < listener.size(); i++)
	{
		listener[i]->ProcessAdd(trade);
	}
}

vector<Trade<Bond>>& BondTradeBookingService::GetRecord(string key)
{
	return tradingbook[key];
}
void BondTradeBookingService::AddListener(ServiceListener<Trade<Bond>> *_listener)
{
	listener.push_back(_listener);
}

const vector< ServiceListener<Trade<Bond>>* >& BondTradeBookingService::GetListeners() const
{
	return listener;
}



#endif
