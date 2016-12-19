#ifndef BONDSTREAMINGSERVICE_HPP
#define BONDSTREAMINGSERVICE_HPP

#include "soa.hpp"
#include "streamingservice.hpp"
#include "products.hpp"


class BondStreamingService : public StreamingService<Bond>
{
private:
	map<string, PriceStream<Bond>> streams;
	vector<ServiceListener<PriceStream<Bond>>*> listener;
public:
	//default constructor
	BondStreamingService();
	BondStreamingService(const BondStreamingService& source) {
		streams = source.streams;
		listener = source.listener;
	}
	// Get data on our service given a key
	virtual PriceStream<Bond>& GetData(string key) {
		return streams[key];
	};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(PriceStream<Bond> &data) {
		string key = data.GetProduct().GetProductId();
		streams[key] = data;
		PublishPrice(data);
	};

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<PriceStream<Bond>> *_listener) {
		listener.push_back(_listener);
	}

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<PriceStream<Bond>>* >& GetListeners() const { return listener; };

	//publish the data
	void PublishPrice(PriceStream<Bond>& priceStream);

	//assignment operator
	BondStreamingService& operator=(const BondStreamingService& source) {
		streams = source.streams;
		listener = source.listener;
		return *this;
	}
};

BondStreamingService::BondStreamingService()
{
}

void BondStreamingService::PublishPrice(PriceStream<Bond>& priceStream)
{
	for (int i = 0; i < listener.size(); i++)
	{
		listener[i]->ProcessAdd(priceStream);
	}
}
#endif
