 #ifndef BONDPOSITIONSERVICE_HPP
#define BONDPOSITIONSERVICE_HPP

#include "soa.hpp"
#include "products.hpp"
#include "tradebookingservice.hpp"
#include "positionservice.hpp"

class BondPositionService : PositionService<Bond>
{
private:
	map<string, Position<Bond>> bondposition;
	vector<ServiceListener<Position<Bond>>*> listener;
public:
	//default constructor
	BondPositionService(){}
	BondPositionService(const BondPositionService& source){
		bondposition = source.bondposition;
		listener = source.listener;
	}
	//add a trade to the position
	void AddTrade(const Trade<Bond>& trade);

	// Get data on our service given a key
	Position<Bond>& GetData(string key)
	{
		return bondposition[key];
	}

	// The callback that a Connector should invoke for any new or updated data
	void OnMessage(Position<Bond> &data) {};

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	void AddListener(ServiceListener<Position<Bond>> *_listener) {
		listener.push_back(_listener);
	}

	// Get all listeners on the Service.
	const vector< ServiceListener<Position<Bond>>* >& GetListeners() const {
		return listener;
	}

	//assignment operator
	BondPositionService& operator=(const BondPositionService& source) {
		bondposition = source.bondposition;
		listener = source.listener;
		return *this;
	}
};


void BondPositionService::AddTrade(const Trade<Bond>& trade)
{
	string key = trade.GetProduct().GetProductId();
	string book = trade.GetBook();
	double amount = 0;
	if (trade.GetSide() == BUY) amount = 1;
	else amount = -1;
	amount *= trade.GetQuantity();
	if(bondposition.find(key)!=bondposition.end()) bondposition[key].SetPosition(book, amount);
	else
	{
		Position<Bond> posi(trade.GetProduct());
		posi.SetPosition(book, amount);
		bondposition.insert(make_pair(key, posi));
	}
	for (int i = 0; i < listener.size(); i++)
	{
		listener[i]->ProcessAdd(bondposition[key]);
	}

}


#endif