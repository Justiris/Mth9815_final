#ifndef ALGOEXECUTIONSERVICE_HPP
#define ALGOEXECUTIONSERVICE_HPP

#include "products.hpp"
#include "executionservice.hpp"

template<typename T>
class AlgoExecution
{
private:
	ExecutionOrder<T> executionOrder;
public:
	//constructor and destructor
	AlgoExecution() {};
	AlgoExecution(const T &_product, PricingSide _side, string _orderId, OrderType _orderType, double _price, double _visibleQuantity, double _hiddenQuantity, string _parentOrderId, bool _isChildOrder)
		:executionOrder(_product,_side,_orderId,_orderType,_price,_visibleQuantity,_hiddenQuantity,_parentOrderId,_isChildOrder){}
	~AlgoExecution() {};

	//get Execution order
	ExecutionOrder<T> GetExecutionOrder() const {
		return executionOrder;
	}

};

template<typename T>
class AlgoExecutionService : public Service<string,AlgoExecution<T>>
{

};

class BondAlgoExecutionService : public AlgoExecutionService<Bond>
{
private:
	map<string, AlgoExecution<Bond>> book;
	vector<ServiceListener<AlgoExecution<Bond>>*> listener;
public:
	//default constructor
	BondAlgoExecutionService() {};
	BondAlgoExecutionService(const BondAlgoExecutionService& source);

	// Get data on our service given a key
	virtual AlgoExecution<Bond>& GetData(string key) { return book[key]; };

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(AlgoExecution<Bond> &data) {
		ExecuteOrder(data);

	};

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<AlgoExecution<Bond>> *_listener) {
		listener.push_back(_listener);
	};

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<AlgoExecution<Bond>>* >& GetListeners() const { return listener; };

	void ExecuteOrder(AlgoExecution<Bond> &data);

	//assignment operator
	BondAlgoExecutionService& operator=(const BondAlgoExecutionService& source) {
		listener = source.listener;
		return *this;
	}
};

BondAlgoExecutionService::BondAlgoExecutionService(const BondAlgoExecutionService& source)
{
	listener = source.listener;
}
void BondAlgoExecutionService::ExecuteOrder(AlgoExecution<Bond> &data)
{
	for (int i = 0; i < listener.size(); i++)
	{
		listener[i]->ProcessAdd(data);
	}
}
#endif
