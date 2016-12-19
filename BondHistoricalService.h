#ifndef BONDHISTORICALSERVICE_HPP
#define BONDHISTORICALSERVICE_HPP

#include "soa.hpp"
#include "products.hpp"
#include "historicaldataservice.hpp"


template<template<typename>class T>
class BondHistoricalService : public HistoricalDataService<T<Bond>>
{
private:
	BondHistoricalConnector<T> historicalconnector;
	map<string, T<Bond>> book;
	vector<ServiceListener<T<Bond>>*> listener;
public:
	BondHistoricalService(){}
	BondHistoricalService(string address):historicalconnector(address) {}
	BondHistoricalService(const BondHistoricalService<T>& source) {
		historicalconnector = source.historicalconnector;
	}

	// Get data on our service given a key
	virtual T<Bond>& GetData(string key) { return book[key]; };

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(T<Bond> &data) {};

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<T<Bond>> *_listener) {};

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<T<Bond>>* >& GetListeners() const { return listener; };

	//publish data to txt file
	void PersistData(string persistKey, T<Bond>& data) {
		historicalconnector.Publish(data);
	}
};

#endif // !BONDHISTORICALSERVICE_HPP
