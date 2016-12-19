#ifndef MARKETDATAALGOEXECUTIONSERVICELISTENER_HPP
#define MARKETDATAALGOEXECUTIONSERVICELISTENER_HPP

#include "BondMarketDataService.h"
#include "AlgoExecutionService.h"
#include "products.hpp"
#include "soa.hpp"

class MarketData_AlgoExecutionServiceListener : public ServiceListener<OrderBook<Bond>>
{
private:
	BondAlgoExecutionService *algoexecution;
public:
	//default constructor
	MarketData_AlgoExecutionServiceListener() {};
	MarketData_AlgoExecutionServiceListener(BondAlgoExecutionService *source) {
		algoexecution = source;
	}

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(OrderBook<Bond> &data) {
		double price = data.GetBidStack(0).GetPrice();
		int count_bid = 0;
		for (int i = 0; i < data.GetBidStack().size(); i++)
		{
			if (price < data.GetBidStack(i).GetPrice()) count_bid = i;
		}
		Order order = data.GetBidStack(count_bid);
		algoexecution->ExecuteOrder(AlgoExecution<Bond>(data.GetProduct(), order.GetSide(), "xxx", FOK, order.GetPrice(), order.GetQuantity(), 0, "XXXX", 1));
	}

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(OrderBook<Bond> &data) {};

	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(OrderBook<Bond> &data) {};
};


#endif
