#include <iostream>
#include <string>
#include <fstream>
#include "products.hpp"
#include <boost\date_time\gregorian\gregorian.hpp>

using namespace std;

vector<double> Linear_congruential_generator(const int N)
{
	long long int x0 = 1;
	const long long int a = 39373;
	const long long int c = 0;
	const long long int k = pow(2, 31) - 1;
	vector<double>ans;
	for (int i = 0; i < N; i++)
	{
		x0 = (a*x0) % k;
		ans.push_back(double(x0) / double(k));
	}
	return ans;
}

vector<string> price_generator(const int N)
{
	vector<double> ran = Linear_congruential_generator(N);
	int xy = 0;
	int z = 0;
	vector<string> ans;
	string price;
	for (int i = 0; i < N; i++)
	{
		price = "";
		if (ran[i] > 0.5) price += "100-";
		else price += "99-";
		xy = ran[i] * 32;
		if (xy < 10) {
			price += "0";
			price += static_cast<char>(xy+48);
		}
		else
		{
			price += static_cast<char>(48 + int(xy / 10));
			price += static_cast<char>(48 + xy % 10);
		}
		z = 8 * (ran[i] * 32 - xy);
		price += static_cast<char>(z+48);
		ans.push_back(price);
	}
	return ans;
}


void trade_generation()
{
	Bond b2("912828U40", CUSIP, "T", 100.0, 1.00, date(2018, Nov, 30));
	Bond b3("912828U32", CUSIP, "T", 100.0, 1.00, date(2019, Nov, 30));
	Bond b5("912828U65", CUSIP, "T", 100.0, 1.75, date(2021, Nov, 30));
	Bond b7("912828U57", CUSIP, "T", 100.0, 2.125, date(2023, Nov, 30));
	Bond b10("912828U24", CUSIP, "T", 100.0, 2.00, date(2026, Nov, 30));
	Bond b30("912810RU4", CUSIP, "T", 100.0, 2.875, date(2046, Nov, 30));
	vector<Bond> product = { b2,b3,b5,b7,b10,b30 };
	vector<string>price = price_generator(60);
	std::ofstream log("trades.txt", std::fstream::app);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			log << product[i].GetProductId() << "," << int(rand() * 1000) << "," << "TRSY1" << "," << price[10 * i + j] << "," << int(rand() * 1000) << "," << "BUY" << endl;
		}
	}
}
void price_generation(const int N)
{
	Bond b2("912828U40", CUSIP, "T", 100.0, 1.00, date(2018, Nov, 30));
	Bond b3("912828U32", CUSIP, "T", 100.0, 1.00, date(2019, Nov, 30));
	Bond b5("912828U65", CUSIP, "T", 100.0, 1.75, date(2021, Nov, 30));
	Bond b7("912828U57", CUSIP, "T", 100.0, 2.125, date(2023, Nov, 30));
	Bond b10("912828U24", CUSIP, "T", 100.0, 2.00, date(2026, Nov, 30));
	Bond b30("912810RU4", CUSIP, "T", 100.0, 2.875, date(2046, Nov, 30));
	vector<Bond> product = { b2,b3,b5,b7,b10,b30 };
	long long int x0 = 1;
	const long long int a = 39373;
	const long long int c = 0;
	const long long int k = pow(2, 31) - 1;
	double x = 0;
	int xy = 0;
	int z = 0;
	string price;
	std::ofstream log("price.txt", std::fstream::app);
	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < N; i++)
		{
			x0 = (a*x0) % k;
			x = double(x0) / double(k);
			price = "";
			if (x > 0.5) price += "100-";
			else price += "99-";
			xy = x * 32;
			if (xy < 10) {
				price += "0";
				price += static_cast<char>(xy + 48);
			}
			else
			{
				price += static_cast<char>(48 + int(xy / 10));
				price += static_cast<char>(48 + xy % 10);
			}
			z = 8 * (x * 32 - xy);
			price += static_cast<char>(z + 48);
			log << product[j].GetProductId() << "," << price << ",";
			if (x > 2.0 / 3) log << 1;
			else if (x > 1.0 / 3) log << 2;
			else log << 3;
			log << endl;
		}
	}
}

void OrderBook_generation(const int N)
{
	Bond b2("912828U40", CUSIP, "T", 100.0, 1.00, date(2018, Nov, 30));
	Bond b3("912828U32", CUSIP, "T", 100.0, 1.00, date(2019, Nov, 30));
	Bond b5("912828U65", CUSIP, "T", 100.0, 1.75, date(2021, Nov, 30));
	Bond b7("912828U57", CUSIP, "T", 100.0, 2.125, date(2023, Nov, 30));
	Bond b10("912828U24", CUSIP, "T", 100.0, 2.00, date(2026, Nov, 30));
	Bond b30("912810RU4", CUSIP, "T", 100.0, 2.875, date(2046, Nov, 30));
	vector<Bond> product = { b2,b3,b5,b7,b10,b30 };
	long long int x0 = 1;
	const long long int a = 39373;
	const long long int c = 0;
	const long long int k = pow(2, 31) - 1;
	double x = 0;
	int xy = 0;
	int z = 0;
	string price;
	std::ofstream log("marketdata.txt", std::fstream::app);
	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < N; i++)
		{
			x0 = (a*x0) % k;
			x = double(x0) / double(k);
			price = "";
			if (x > 0.5) price += "100-";
			else price += "99-";
			xy = x * 32;
			if (xy < 10) {
				price += "0";
				price += static_cast<char>(xy + 48);
			}
			else
			{
				price += static_cast<char>(48 + int(xy / 10));
				price += static_cast<char>(48 + xy % 10);
			}
			z = 8 * (x * 32 - xy);
			price += static_cast<char>(z + 48);
			log << product[j].GetProductId() << "," << price << ",";
			log << rand() * 10 << ",";
			if (x > 0.5) log << "BID";
			else log << "OFFER";
			log << endl;
		}
	}
}


void Inquiry_generation(const int N)
{
	Bond b2("912828U40", CUSIP, "T", 100.0, 1.00, date(2018, Nov, 30));
	Bond b3("912828U32", CUSIP, "T", 100.0, 1.00, date(2019, Nov, 30));
	Bond b5("912828U65", CUSIP, "T", 100.0, 1.75, date(2021, Nov, 30));
	Bond b7("912828U57", CUSIP, "T", 100.0, 2.125, date(2023, Nov, 30));
	Bond b10("912828U24", CUSIP, "T", 100.0, 2.00, date(2026, Nov, 30));
	Bond b30("912810RU4", CUSIP, "T", 100.0, 2.875, date(2046, Nov, 30));
	vector<Bond> product = { b2,b3,b5,b7,b10,b30 };
	vector<string>price = price_generator(60);
	std::ofstream log("inquirys.txt", std::fstream::app);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			log << int(rand() * 201)<<","<< product[i].GetProductId() << "," << "BUY" <<","<< int(rand() * 1000) << "," << price[10 * i + j] << "," << "RECEIVED" << endl;
		}
	}
}
int main()
{
	//OrderBook_generation(10);
	Inquiry_generation(10);
	return 0;
}