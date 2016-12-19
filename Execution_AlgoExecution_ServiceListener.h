#ifndef EXECUTIONALGOEXECUTIONSERVICELISTENER_HPP
#define EXECUTIONALGOEXECUTIONSERVICELISTENER_HPP

#include "soa.hpp"
#include "products.hpp"
#include "BondExecutionService.h"
#include "AlgoExecutionService.h"

class Execution_AlgoExecution_ServiceListener : public ServiceListener<AlgoExecution<Bond>>
{
private:
	BondExecutionService *bondexecutionservice;
public:
	Execution_AlgoExecution_ServiceListener() {};
	Execution_AlgoExecution_ServiceListener(BondExecutionService *source) {
		bondexecutionservice = source;
	}

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(AlgoExecution<Bond> &data) {
		ExecutionOrder<Bond> order = data.GetExecutionOrder();
		bondexecutionservice->ExecuteOrder(order,BROKERTEC);
		bondexecutionservice->ExecuteOrder(order, ESPEED);
		bondexecutionservice->ExecuteOrder(order, CME);
	};

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(AlgoExecution<Bond> &data) {};

	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(AlgoExecution<Bond> &data) {};
};


#endif
