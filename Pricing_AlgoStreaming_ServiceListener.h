#ifndef PRICINGALGOSTREAMINGSERVICELISTENER_HPP
#define PRICINGALGOSTREAMINGSERVICELISTENER_HPP

#include "BondPositionService.h"
#include "AlgoStreamingService.h"
#include "pricingservice.hpp"
#include "products.hpp"
#include "soa.hpp"

class Pricing_AlgoStreamingServiceListener : public ServiceListener<Price<Bond>>
{
private:
	BondAlgoStreamingService *algostream;
public:
	//default constructor
	Pricing_AlgoStreamingServiceListener() {};
	Pricing_AlgoStreamingServiceListener(BondAlgoStreamingService *source) {
		algostream = source;
	}

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(Price<Bond> &data) {
		PriceStreamOrder bidorder(data.GetMid() - data.GetBidOfferSpread(), 0, 0, BID);
		PriceStreamOrder offerorder(data.GetMid() + data.GetBidOfferSpread(), 0, 0, OFFER);
		const Bond product = data.GetProduct();
		AlgoStream<Bond> pricestream(product, bidorder, offerorder);
		algostream->PublishPrice(pricestream);
	}

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(Price<Bond> &data) {};

	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(Price<Bond> &data) {};
};


#endif