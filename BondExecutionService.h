#ifndef BONDEXECUTIONSERVICE_HPP
#define BONDEXECUTIONSERVICE_HPP

#include "executionservice.hpp"
#include "products.hpp"
#include "soa.hpp"

class BondExecutionService : public ExecutionService<Bond>
{
private:
	map<string, map<Market, vector<ExecutionOrder<Bond>>>> executionOrder;
	vector<ServiceListener<ExecutionOrder<Bond>>* > listener;
public:
	BondExecutionService() {}
	BondExecutionService(const BondExecutionService& source) {
		executionOrder = source.executionOrder;
		listener = source.listener;
	}
	// Get data on our service given a key
	//virtual ExecutionOrder<Bond>& GetData(string key) { return executionOrder[key]; }

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(ExecutionOrder<Bond> &data, Market market) {
		ExecuteOrder(data, market);
	}

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<ExecutionOrder<Bond>> *_listener) {
		listener.push_back(_listener);
	}

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<ExecutionOrder<Bond>>* >& GetListeners() const {
		return listener;
	}

	// Execute an order on a market
	void ExecuteOrder(ExecutionOrder<Bond>& order, Market market) {
		string key = order.GetProduct().GetProductId();
		if (executionOrder.find(key) != executionOrder.end())
		{
			if (executionOrder[key].find(market) != executionOrder[key].end())
			{
				executionOrder[key][market].push_back(order);
			}
			else {
				vector<ExecutionOrder<Bond>> v;
				executionOrder[key].insert(make_pair(market, v));
			}
		}
		else {
			map<Market,vector<ExecutionOrder<Bond>>> m1;
			executionOrder.insert(make_pair(key, m1));
		}
		for (int i = 0; i < listener.size(); i++)
		{
			listener[i]->ProcessAdd(order);
		}
	}

	//assignment operator
	BondExecutionService& operator=(const BondExecutionService& source) {
		executionOrder = source.executionOrder;
		listener = source.listener;
		return *this;
	}
};






#endif // !BondExecutionService_hpp
