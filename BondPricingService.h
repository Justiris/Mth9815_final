#ifndef BONDPRICINGSERVICE_HPP
#define BONDPRICINGSERVICE_HPP

#include "soa.hpp"
#include "products.hpp"
#include "pricingservice.hpp"
#include "AlgoStreamingService.h"

class BondPricingService : public PricingService<Bond>
{
private:
	map<string, Price<Bond>> pricebook;
	vector<ServiceListener<Price<Bond>>*> listener;

public:
	//default constructor
	BondPricingService() {}

	BondPricingService(const BondPricingService& source) {
		pricebook = source.pricebook;
		listener = source.listener;
	}
	// Get data on our service given a key
	virtual Price<Bond>& GetData(string key) {
		return pricebook[key];
	};


	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Price<Bond> &data) {
		if (pricebook.find(data.GetProduct().GetProductId()) != pricebook.end()) pricebook[data.GetProduct().GetProductId()] = data;
		else pricebook.insert(make_pair(data.GetProduct().GetProductId(), data));
		for (int i = 0; i < listener.size(); i++)
		{
			listener[i]->ProcessAdd(data);
		}
	};

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<Price<Bond>> *_listener) {
		listener.push_back(_listener);
	};

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<Price<Bond>>* >& GetListeners() const {
		return listener;
	};

	//assignment operator
	BondPricingService& operator=(const BondPricingService& source) {
		pricebook = source.pricebook;
		listener = source.listener;
		return *this;
	}

};

#endif // !BONDPRICINGSERVICE_HPP

