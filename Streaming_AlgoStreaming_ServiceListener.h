#ifndef STREAMINGALGOSTREAMINGSERVICELISTENER_HPP
#define STREAMINGALGOSTREAMINGSERVICELISTENER_HPP


#include "soa.hpp"
#include "products.hpp"
#include "AlgoStreamingService.h"
#include "BondStreamingService.h"

class Streaming_AlgoStreaming_ServiceListener : public ServiceListener<AlgoStream<Bond>>
{
private:
	BondStreamingService *bondStreamingservice;
public:
	Streaming_AlgoStreaming_ServiceListener() {};
	Streaming_AlgoStreaming_ServiceListener(BondStreamingService *source) {
		bondStreamingservice = source;
	}
	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(AlgoStream<Bond> &data) {
		bondStreamingservice->PublishPrice(data.GetStreamingOrder());
	};

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(AlgoStream<Bond> &data) {};

	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(AlgoStream<Bond> &data) {};
};

#endif // !STREAMINGALGOSTREAMINGSERVICELISTENER_HPP

