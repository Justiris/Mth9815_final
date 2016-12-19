#ifndef RISKPOSITIONLISTENER_HPP
#define RISKPOSITIONLISTENER_HPP

#include "soa.hpp"
#include "products.hpp"
#include "BondRiskService.h"
#include "positionservice.hpp"

class RiskPositionListener : public ServiceListener<Position<Bond>>
{
private:
	BondRiskService *bondriskservice;
public:
	//default constructor
	RiskPositionListener();
	RiskPositionListener(BondRiskService* source) {
		bondriskservice = source;
	}
	void ProcessAdd(Position<Bond> &position);
};

RiskPositionListener::RiskPositionListener()
{}

void RiskPositionListener::ProcessAdd(Position<Bond> &position)
{
	bondriskservice->AddPosition(position);
}

#endif
