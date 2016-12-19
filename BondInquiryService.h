#ifndef BONDINQUIRYSERVICE_HPP
#define BONDINQUIRYSERVICE_HPP

#include "soa.hpp"
#include "products.hpp"
#include "inquiryservice.hpp"


class BondInquiryService : public InquiryService<Bond>
{
private:
	map<string, Inquiry<Bond> > inquirybook;
	vector<ServiceListener<Inquiry<Bond> >* > listener;
	Connector<Inquiry<Bond> > *inquiryconnector;
public:
	//default constructor
	BondInquiryService(){}

	//copy constructor
	BondInquiryService(BondInquiryService& source)
	{
		inquirybook = source.inquirybook;
		listener = source.listener;
		inquiryconnector = source.inquiryconnector;
	}

	// Get data on our service given a key
	virtual Inquiry<Bond>& GetData(string key) {
		return inquirybook[key];
	};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Inquiry<Bond> &data) {
		string key = data.GetInquiryId();
		if (data.GetState() == RECEIVED) {
			inquirybook.insert(make_pair(key, data));
			for (int i = 0; i < listener.size(); i++)
			{
				listener[i]->ProcessAdd(data);
			}
		}
		else if(data.GetState() == QUOTED){
			inquirybook[key].SetState(DONE);
		}
		
	};


	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<Inquiry<Bond> > *_listener) {
		listener.push_back(_listener);
	}

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<Inquiry<Bond> >* >& GetListeners() const {
		return listener;
	}

	// Send a quote back to the client
	void SendQuote(const string &inquiryId, double price);

	// Reject an inquiry from the client
	void RejectInquiry(const string &inquiryId);
};

void BondInquiryService::SendQuote(const string &inquiryId, double price)
{
	Inquiry<Bond> inqu(inquiryId, inquirybook[inquiryId].GetProduct(), inquirybook[inquiryId].GetSide(), inquirybook[inquiryId].GetQuantity(), price, inquirybook[inquiryId].GetState());
	inquiryconnector->Publish(inqu);
}

void BondInquiryService::RejectInquiry(const string &inquiryId) {
	inquirybook[inquiryId].SetState(REJECTED);
}

#endif // !BONDINQUIRYSERVICE_HPP

