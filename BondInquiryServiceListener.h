#ifndef BONDINQUIRYSERVICELISTENER_HPP
#define BONDINQUIRYSERVICELISTENER_HPP

#include "soa.hpp"
#include "products.hpp"
#include "inquiryservice.hpp"
#include "BondInquiryService.h"

class BondInquiryServiceListener : public ServiceListener<Inquiry<Bond>>
{
private:
	BondInquiryService *inquiry;
public:
	//default constructor
	BondInquiryServiceListener(){}
	BondInquiryServiceListener(BondInquiryService *source) {
		inquiry = source;
	}

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(Inquiry<Bond> &data) {
		inquiry->SendQuote(data.GetInquiryId(), 100.0);
	};

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(Inquiry<Bond> &data) {};

	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(Inquiry<Bond> &data) {};
};
#endif // !BONDINQUIRYSERVICELISTENER_HPP

