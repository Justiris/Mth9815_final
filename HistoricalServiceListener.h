#ifndef HISTORICALSERVICELISTENER_HPP
#define HISTORICALSERVICELISTENER_HPP

#include "soa.hpp"
#include "products.hpp"
#include "BondHistoricalService.h"
#include "inquiryservice.hpp"

template<template<typename>class T>
class HistoricalServiceListener : public ServiceListener<T<Bond>>
{
private:
	BondHistoricalService<T> *historicaldata;
public:
	//default constructor
	HistoricalServiceListener(){}
	HistoricalServiceListener(BondHistoricalService<T> *source) {
		historicaldata = source;
	}

	void ProcessAdd(T<Bond> &data) {
		historicaldata->PersistData(data.GetProduct().GetProductId(), data);
	}
};
#endif // !HISTORICALSERVICELISTENER_HPP

