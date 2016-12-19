/**
 * positionservice.hpp
 * Defines the data types and Service for positions.
 *
 * @author Breman Thuraisingham
 */
#ifndef POSITION_SERVICE_HPP
#define POSITION_SERVICE_HPP

#include <string>
#include <map>
#include "soa.hpp"

using namespace std;

/**
 * Position class in a particular book.
 * Type T is the product type.
 */
template<typename T>
class Position
{

public:
	Position(){}
  // ctor for a position
  Position(const T &_product);

  // Get the product
  const T& GetProduct() const;

  // Get the position quantity
  long GetPosition(string &book);

  // Get the aggregate position
  long GetAggregatePosition();

  //Set the position
  void SetPosition(string &book, long amount);

  //output operator
  friend ostream& operator<< (ostream &os, const Position &source) {
	  os << source.product << ",";
	  for (auto iter = source.positions.begin(); iter != source.positions.end(); iter++)
	  {
		  os << (*iter).first << "," << (*iter).second;
	  }
	  //os << endl;
	  return os;
  }
private:
  T product;
  map<string,long> positions;

};

/**
 * Position Service to manage positions across multiple books and secruties.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class PositionService : public Service<string,Position <T> >
{

public:

  // Add a trade to the service
  virtual void AddTrade(const Trade<T> &trade) = 0;

};

template<typename T>
Position<T>::Position(const T &_product) :
  product(_product)
{
	map<string, long> positions;
}

template<typename T>
const T& Position<T>::GetProduct() const
{
  return product;
}

template<typename T>
long Position<T>::GetPosition(string &book)
{
  return positions[book];
}

template<typename T>
void Position<T>::SetPosition(string &book, long amount)
{
	positions[book] += amount;
}
template<typename T>
long Position<T>::GetAggregatePosition()
{
	long sum = 0;
	for (auto iter = positions.begin(); iter != positions.end(); iter++)
	{
		sum += (*iter).second;
	}
	return sum;
}

#endif
