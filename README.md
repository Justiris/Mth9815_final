# Mth9815_final

used inquirys.txt, price.txt, marketdata.txt, trades.txt as input.
price_sample.txt and marketdata_sample.txt both contains 6000000 data for orderbook and price;

the file has a format as below:
allinquirys: inquiryId,product,side,quantity,price
position: product,position for trsy1, position for trsy2, position for trsy3
risk: product,pv01,quantity
execution: product,Bid/offer,price,visibleQuantity,hiddenQuantity
streaming: product,price,visibleQuantity,hiddenQuantity,Bid/offer
and product will output: ProductId,,Price,ticker,MaturityDate

the output can be find in Allinquiry.txt, Position.txt, Risk.txt, execution.txt and streaming.txt

tested under ubuntu g++ 5.x

please use g++ main.cpp -o main -std=c++11 -I <path of boost> to run code
please notify there are two test function, test_1() to test tradebooking,position and risk service; test_rest() to test rest of service.
It's weird to seperate it into two parts, but I'' get a string initiation error when I test them together, which I have no idea about.

Qinkai

