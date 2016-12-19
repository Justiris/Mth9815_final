#ifndef BONDRISKSERVICE_HPP
#define BONDRISKSERVICE_HPP

#include "riskservice.hpp"
#include "soa.hpp"
#include "products.hpp"
#include "positionservice.hpp"

class BondRiskService : public RiskService<Bond>
{
private:
	map<string, PV01<Bond>> riskbook;
	vector<ServiceListener<PV01<Bond>>*> listener;
public:
	//default constructor
	BondRiskService() {
		Bond b2("912828U40", CUSIP, "T", 100.0, 1.00, date(2018, Nov, 30));
		Bond b3("912828U32", CUSIP, "T", 100.0, 1.00, date(2019, Nov, 30));
		Bond b5("912828U65", CUSIP, "T", 100.0, 1.75, date(2021, Nov, 30));
		Bond b7("912828U57", CUSIP, "T", 100.0, 2.125, date(2023, Nov, 30));
		Bond b10("912828U24", CUSIP, "T", 100.0, 2.00, date(2026, Nov, 30));
		Bond b30("912810RU4", CUSIP, "T", 100.0, 2.875, date(2046, Nov, 30));
		PV01<Bond> p1(b2, 1.02, 0);
		PV01<Bond> p2(b3, 1.02, 0);
		PV01<Bond> p3(b5, 1.02, 0);
		PV01<Bond> p4(b7, 1.02, 0);
		PV01<Bond> p5(b10, 1.02, 0);
		PV01<Bond> p6(b30, 1.02, 0);
		riskbook.insert(make_pair("912828U40", p1));
		riskbook.insert(make_pair("912828U32", p2));
		riskbook.insert(make_pair("912828U65", p3));
		riskbook.insert(make_pair("912828U57", p4));
		riskbook.insert(make_pair("912828U24", p5));
		riskbook.insert(make_pair("912828RU4", p6));
	}
	BondRiskService(const BondRiskService& source);
	~BondRiskService() {}

	// Get data on our service given a key
	virtual PV01<Bond>& GetData(string key) {
		return riskbook[key];
	};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(PV01<Bond> &data) {};

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<PV01<Bond>> *_listener) {
		listener.push_back(_listener);
	};

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<PV01<Bond>>* >& GetListeners() const {
		return listener;
	};
	
	//update position to riskbook
	void AddPosition(Position<Bond> &position);

	//return pv01 of given sector
	double GetBucketedRisk(const BucketedSector<Bond>& sector);

	//assignment operator
	BondRiskService& operator=(const BondRiskService& source) {
		riskbook = source.riskbook;
		listener = source.listener;
		return *this;
	}
};
BondRiskService::BondRiskService(const BondRiskService& source)
{
	riskbook = source.riskbook;
	listener = source.listener;
}

//update position to riskbook
void BondRiskService::AddPosition(Position<Bond>& position)
{
	string key = position.GetProduct().GetProductId();
	long posi = position.GetAggregatePosition()+riskbook[key].GetQuantity();
	riskbook[key].SetQuantity(posi);
	for (int i = 0; i < listener.size(); i++)
	{
		listener[i]->ProcessAdd(riskbook[key]);
	}
}

//return pv01 of given sector
double BondRiskService::GetBucketedRisk(const BucketedSector<Bond>& sector)
{
	double sum = 0;
	for (auto iter = sector.GetProducts().begin(); iter != sector.GetProducts().end(); iter++)
	{
		string key = (*iter).GetProductId();
		sum += riskbook[key].GetPV01()*riskbook[key].GetQuantity();
	}
	return sum;
}

#endif
