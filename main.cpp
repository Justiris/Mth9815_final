#include "BondInquiryConnector.h"
#include "BondInquiryService.h"
#include "BondInquiryServiceListener.h"
#include "BondHistoricalConnector.h"
#include "BondHistoricalService.h"
#include "HistoricalServiceListener.h"
#include "BondPricingService.h"
#include "BondPricingConnector.h"
#include "Streaming_AlgoStreaming_ServiceListener.h"
#include "Pricing_AlgoStreaming_ServiceListener.h"
#include "AlgoStreamingService.h"
#include "BondStreamingService.h"
#include "AlgoExecutionService.h"
#include "BondExecutionService.h"
#include "BondMarketDataConnector.h"
#include "BondMarketDataService.h"
#include "Execution_AlgoExecution_ServiceListener.h"
#include "MarketData_AlgoExecution_ServiceListener.h"
#include "BondTradeBookingService.h"
#include "BondPositionService.h"
#include "BondRiskService.h"
#include "Position_tradebooking_listener.h"
#include "RiskPositionListener.h"
#include "TradebookingServiceConnector.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	// Init the BondTradeBookingService
	BondTradeBookingService b_tradebooking_s;

	// Init the BondPositionService
	BondPositionService b_position_s;

	// Init the BondRiskService
	BondRiskService b_risk_s;

	// Init the BondPricingService
	BondPricingService b_pricing_s;

	// Init the BondMarketDataService
	BondMarketDataService b_marketdata_s;

	// Init the BondAlgoExecutionService
	BondAlgoExecutionService b_algoexecution_s;

	// Init the BondExecutionService
	BondExecutionService b_execution_s;

	// Init the BondStreamingService
	BondStreamingService b_stream_s;

	// Init the BondAlgoStreamingService
	BondAlgoStreamingService b_algostream_s;

	// Init the BondInquiryService
	BondInquiryService b_inquiry_s;

	/****************************
	* Listener Register and Add *
	****************************/

	//tradebooking,position and risk
	//define servicelistener
	PositionTradebookingListener position_trading_listener(&b_position_s);
	RiskPositionListener risk_position_listener(&b_risk_s);

	//add servicelistener
	b_tradebooking_s.AddListener(&position_trading_listener);
	b_position_s.AddListener(&risk_position_listener);

	//set up historical service for position
	BondHistoricalService<Position> b_historicaldata_s_position("Position.txt");
	HistoricalServiceListener<Position> b_historicaldata_listener_position(&b_historicaldata_s_position);
	b_position_s.AddListener(&b_historicaldata_listener_position);

	//set up historical service for risk
	BondHistoricalService<PV01> b_historicaldata_s_risk("Risk.txt");
	HistoricalServiceListener<PV01> b_historicaldata_listener_risk(&b_historicaldata_s_risk);
	b_risk_s.AddListener(&b_historicaldata_listener_risk);


	//marketdata,algostreaming and bondstreaming
	//define servicelistener
	Pricing_AlgoStreamingServiceListener pricing_algostream_listener(&b_algostream_s);
	Streaming_AlgoStreaming_ServiceListener streaming_algostream_listener(&b_stream_s);

	//add servicelistener
	b_algostream_s.AddListener(&streaming_algostream_listener);
	b_pricing_s.AddListener(&pricing_algostream_listener);

	//set up historical service for BondStreaming
	BondHistoricalService<PriceStream> b_historicaldata_s_streaming("Streaming.txt");
	HistoricalServiceListener<PriceStream> b_historicaldata_listener_streaming(&b_historicaldata_s_streaming);
	b_stream_s.AddListener(&b_historicaldata_listener_streaming);


	//pricing, algoexecution and bondexecution
	//define servicelistener
	Execution_AlgoExecution_ServiceListener execution_algoexecution_listener(&b_execution_s);
	MarketData_AlgoExecutionServiceListener market_algoexecution_listener(&b_algoexecution_s);

	//add servicelistener
	b_marketdata_s.AddListener(&market_algoexecution_listener);
	b_algoexecution_s.AddListener(&execution_algoexecution_listener);

	//set up historical service for BondExecution
	BondHistoricalService<ExecutionOrder> b_historicaldata_s_execution("Execution.txt");
	HistoricalServiceListener<ExecutionOrder> b_historicaldata_listener_execution(&b_historicaldata_s_execution);
	b_execution_s.AddListener(&b_historicaldata_listener_execution);

	// Inquiry
	//set up historical service for inquiry
	BondHistoricalService<Inquiry> b_historicaldata_s_inquiry("AllInquiry.txt");
	HistoricalServiceListener<Inquiry> b_historicaldata_listener_inquiry(&b_historicaldata_s_inquiry);
	b_inquiry_s.AddListener(&b_historicaldata_listener_inquiry);

	/*************************************
	* Connector Register and flow in data*
	*************************************/

	// Init the BondTradebookingConnectorRead which can flow the tradebooking data
	// from trade.txt to the BondInquiryService

	string trading_file{ "trades.txt" };
	BondTradeBookingConnector b_tradebooking_connector(&b_tradebooking_s);
	b_tradebooking_connector.GetTradeFromFile(trading_file);


	// Init the BondmarketdataConnectorRead which can flow the marketdata data
	// from marketdata.txt to the BondInquiryService

	string marketdata_file{ "marketdata.txt" };
	BondMarketDataConnector b_marketdata_connector(&b_marketdata_s);
	b_marketdata_connector.GetMarketDataFromFile(marketdata_file);



	// Init the BondPricingConnectorRead which can flow the price data
	// from price.txt to the BondInquiryService
	string price_file{ "price.txt" };
	BondPricingConnector b_pricing_connector(&b_pricing_s);
	b_pricing_connector.GetPriceFromFile(price_file);


	// Init the BondInquiryConnectorWrite and add it to the BondInquiryService
	// So that the inquiries with QUOTED state will be dealed and sent back to
	// BondInquiryService with DONE state
	string inquiries_file{ "inquirys.txt" };
	BondInquiryConnector b_inquiry_connector(&b_inquiry_s);
	//b_inquiry_s.SetConnector(&b_inquiry_connector_write);

	// Init the BondInquiryConnectorRead which can flow the inquiry data
	// from inquiry.txt to the BondInquiryService


	b_inquiry_connector.GetInquiryFromFile(inquiries_file);
	return 0;
}