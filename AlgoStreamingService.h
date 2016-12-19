#ifndef ALGOSTREAMINGSERVICE_HPP
#define ALGOSTREAMINGSERVICE_HPP

#include "soa.hpp"
#include "products.hpp"
#include "streamingservice.hpp"

template<typename T>
class AlgoStream
{
private:
	PriceStream<T> StreamingOrder;
public:
	//default constructor
	AlgoStream(){}
	AlgoStream(const T &_product, const PriceStreamOrder &_bidOrder, const PriceStreamOrder &_offerOrder):StreamingOrder(_product, _bidOrder, _offerOrder){}

	//get the streamingorder
	PriceStream<T> GetStreamingOrder() const
	{
		return StreamingOrder;
	}

};

template<typename T>
class AlgoStreamingService : public Service<string, AlgoStream<T>>
{

};

class BondAlgoStreamingService : public AlgoStreamingService<Bond>
{
private:
	map<string, AlgoStream<Bond>> book;
	vector<ServiceListener<AlgoStream<Bond>>*> listener;
public:
	//default constructor
	BondAlgoStreamingService() {};
	BondAlgoStreamingService(const BondAlgoStreamingService& source);

	// Get data on our service given a key
	virtual AlgoStream<Bond>& GetData(string key) { return book[key]; };

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(AlgoStream<Bond> &data) {
		PublishPrice(data);
	};

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<AlgoStream<Bond>> *_listener) {
		listener.push_back(_listener);
	};

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<AlgoStream<Bond>>* >& GetListeners() const { return listener; };

	//publish the two-way price
	void PublishPrice(AlgoStream<Bond> &data);

	BondAlgoStreamingService& operator=(const BondAlgoStreamingService& source){
		book = source.book;
		listener = source.listener;
		return *this;
	}
};

BondAlgoStreamingService::BondAlgoStreamingService(const BondAlgoStreamingService& source)
{
	book = source.book;
	listener = source.listener;
}

void BondAlgoStreamingService::PublishPrice(AlgoStream<Bond> &data)
{
	for (int i = 0; i < listener.size(); i++)
	{
		listener[i]->ProcessAdd(data);
	}
}

#endif // !ALGOSTREAMINGSERVICE_HPP

