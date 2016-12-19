#ifndef POSITION_TRADEBOOKING_LISTENER_HPP
#define POSITION_TRADEBOOKING_LISTENER_HPP

#include "soa.hpp"
#include "tradebookingservice.hpp"
#include "BondPositionService.h"

class PositionTradebookingListener :public ServiceListener<Trade<Bond>>
{
private:
	BondPositionService *positions;
public:
	//default constrcutor
	PositionTradebookingListener();
	PositionTradebookingListener(BondPositionService *source)
	{
		positions = source;
	}
	void ProcessAdd(Trade<Bond>& data);

};

PositionTradebookingListener::PositionTradebookingListener()
{
	BondPositionService positions();
}

void PositionTradebookingListener::ProcessAdd(Trade<Bond>& data)
{
	positions->AddTrade(data);
}


#endif