#ifndef BONDHISTORICALCONNECTOR_HPP
#define BONDHISTORICALCONNECTOR_HPP

#include "soa.hpp"
#include "products.hpp"
#include "historicaldataservice.hpp"
#include <fstream>

template<template<typename>class T>
class BondHistoricalConnector : public Connector<T<Bond>>
{
private:
	string address;
public:
	//default constructor
	BondHistoricalConnector() {}
	BondHistoricalConnector(string _address) {
		address = _address;
	}

	virtual void Publish(T<Bond> &data) {
		std::ofstream log(address, std::fstream::app);
		log << data << std::endl;
	}

	BondHistoricalConnector<T>& operator=(const BondHistoricalConnector<T>& source);
};

template<template<typename>class T>
BondHistoricalConnector<T>& BondHistoricalConnector<T>::operator=(const BondHistoricalConnector<T>& source)
{
	address = source.address;
	return *this;
}
#endif // !BONDHISTORICALCONNECTOR_HPP
