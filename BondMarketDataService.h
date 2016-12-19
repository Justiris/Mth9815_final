#ifndef BONDMARKETDATASERVICE_HPP
#define BONDMARKETDATASERVICE_HPP

#include "soa.hpp"
#include "products.hpp"
#include "marketdataservice.hpp"


class BondMarketDataService : public MarketDataService<Bond>
{
private:
	map<string, OrderBook<Bond>> orderbook;
	vector<ServiceListener<OrderBook<Bond>>*> listener;
public:
	//default constructor
	BondMarketDataService() {};

	//copy constructor
	BondMarketDataService(const BondMarketDataService& source) {
		orderbook = source.orderbook;
		listener = source.listener;
	}

	//get the market order data
	OrderBook<Bond>& GetData(string key) { return orderbook[key]; };


	void OnMessage(OrderBook<Bond>& data);

	//add a service listener
	void AddListener(ServiceListener<OrderBook<Bond>> *_listener) {
		listener.push_back(_listener);
	}
	//get the service listeners
	const vector< ServiceListener<OrderBook<Bond>>*>& GetListeners() const { return listener; };
	//get the best bidoffer for a specific product
	const BidOffer GetBestBidOffer(const string &productId);
	//combine all orders and get a aggregae orderbook
	const OrderBook<Bond> AggregateDepth(const string &productId);

	//assignment operator
	BondMarketDataService& operator=(const BondMarketDataService& source) {
		orderbook = source.orderbook;
		listener = source.listener;
		return *this;
	}
};
void BondMarketDataService::OnMessage(OrderBook<Bond>& data)
{
	string key = data.GetProduct().GetProductId();
	if(orderbook.find(key)!=orderbook.end()) orderbook[key] = data;
	else orderbook.insert(make_pair(data.GetProduct().GetProductId(), data));
	for (int i = 0; i < listener.size(); i++)
	{
		listener[i]->ProcessAdd(data);
	}
}


const BidOffer BondMarketDataService::GetBestBidOffer(const string& productId)
{
	double price = orderbook[productId].GetBidStack(0).GetPrice();
	int count_bid = 0;
	for (int i = 0; i < orderbook[productId].GetBidStack().size(); i++)
	{
		if (price < orderbook[productId].GetBidStack(i).GetPrice()) count_bid = i;
	}
	int count_offer = 0;
	price = orderbook[productId].GetOfferStack(0).GetPrice();
	for (int i = 0; i < orderbook[productId].GetOfferStack().size(); i++)
	{
		if (price < orderbook[productId].GetOfferStack(i).GetPrice()) count_offer = i;
	}
	BidOffer bidoffer(orderbook[productId].GetBidStack(count_bid), orderbook[productId].GetOfferStack(count_offer));
	return bidoffer;
}

const OrderBook<Bond> BondMarketDataService::AggregateDepth(const string &productId)
{
	map<double, Order> bid_orderbook;
	double price;
	for (int i = 0; i < orderbook[productId].GetBidStack().size(); i++)
	{
		price = orderbook[productId].GetBidStack(i).GetPrice();
		if (bid_orderbook.find(price) != bid_orderbook.end()) bid_orderbook[price].SetQuantity(bid_orderbook[price].GetQuantity() + orderbook[productId].GetBidStack(i).GetQuantity());
		else bid_orderbook.insert(make_pair(price, orderbook[productId].GetBidStack(i)));
	}
	map<double, Order> offer_orderbook;
	for (int i = 0; i < orderbook[productId].GetOfferStack().size(); i++)
	{
		price = orderbook[productId].GetOfferStack(i).GetPrice();
		if (offer_orderbook.find(price) != offer_orderbook.end()) offer_orderbook[price].SetQuantity(offer_orderbook[price].GetQuantity() + orderbook[productId].GetOfferStack(i).GetQuantity());
		else offer_orderbook.insert(make_pair(price, orderbook[productId].GetOfferStack(i)));
	}
	vector<Order> bidstack;
	for (auto iter = bid_orderbook.begin(); iter != bid_orderbook.end(); iter++) bidstack.push_back((*iter).second);
	vector<Order> offerstack;
	for (auto iter = offer_orderbook.begin(); iter != offer_orderbook.end(); iter++) offerstack.push_back((*iter).second);
	OrderBook<Bond> orders(orderbook[productId].GetProduct(), bidstack, offerstack);
	return orders;
}
#endif
