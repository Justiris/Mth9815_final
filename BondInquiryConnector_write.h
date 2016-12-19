#ifndef BONDINQUIRYCONNECTOR_HPP
#define BONDINQUIRYCONNECTOR_HPP

#include "soa.hpp"
#include "products.hpp"
#include "inquiryservice.hpp"
#include "BondInquiryService.h"

class BondInquiryConnector_write : public Connector<Inquiry<Bond>>
{
private:
	Bond
public:
	//default Constructor
	BondInquiryConnector_write(){}

	// Publish data to the Connector
	virtual void Publish(Inquiry<Bond> &data) {
		data.SetState(QUOTED);
		inquiry->OnMessage(data);
	}

};
#endif // !BONDINQUIRYCONNECTORWRITE_HPP

