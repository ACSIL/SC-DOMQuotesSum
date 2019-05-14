#include "sierrachart.h"
SCDLLName("DOM POCET KOTACI")

// ok - vali jen realtime kdyz jede DOM (nebo na replayi kdyz je dom nahranej) - po rekalkulaci zmizi, je potreba vyresit zapis do souboru
SCSFExport scsf_pocet_kotaci_l4(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "DOM Bid/Ask Quotes Number (4 levels)";

		//asks
		sc.Subgraph[0].Arrays[0];
		sc.Subgraph[0].Arrays[1];
		sc.Subgraph[0].Arrays[2];
		sc.Subgraph[0].Arrays[3];

		sc.Subgraph[0].DrawStyle = DRAWSTYLE_IGNORE;

		//bids
		sc.Subgraph[1].Arrays[0];
		sc.Subgraph[1].Arrays[1];
		sc.Subgraph[1].Arrays[2];
		sc.Subgraph[1].Arrays[3];

		sc.Subgraph[1].DrawStyle = DRAWSTYLE_IGNORE;

		// asks/bids
		sc.Subgraph[10].Name = "Ask";
		sc.Subgraph[10].LineLabel |= LL_DISPLAY_NAME | LL_DISPLAY_VALUE;
		sc.Subgraph[10].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[10].PrimaryColor = RGB(0, 255, 0);

		sc.Subgraph[11].Name = "Bid";
		sc.Subgraph[11].LineLabel |= LL_DISPLAY_NAME | LL_DISPLAY_VALUE;
		sc.Subgraph[11].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[11].PrimaryColor = RGB(255, 0, 0);

		sc.UsesMarketDepthData = TRUE;

		sc.AutoLoop = 1;
		sc.FreeDLL = 1;

		return;
	}

	// define 4 references for 4 ask price levels
	s_MarketDepthEntry r_depth_entry_ask_l1;
	s_MarketDepthEntry r_depth_entry_ask_l2;
	s_MarketDepthEntry r_depth_entry_ask_l3;
	s_MarketDepthEntry r_depth_entry_ask_l4;

	//this is quite a tricky function sc.GetAskMarketDepthEntryAtLevel taking the reference to the struct s_MarketDepthEntry as a parametr and returning it back 
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l1, 0); // the values at the 1 ask level 
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l2, 1); // the values at the 2 ask level
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l3, 2); // the values at the 3 ask level
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l4, 3); // the values at the 4 ask level

															   // get the quantity (of ask) for particular levels
	sc.Subgraph[0].Arrays[0][sc.Index] = (float)r_depth_entry_ask_l1.Quantity;
	sc.Subgraph[0].Arrays[1][sc.Index] = (float)r_depth_entry_ask_l2.Quantity;
	sc.Subgraph[0].Arrays[2][sc.Index] = (float)r_depth_entry_ask_l3.Quantity;
	sc.Subgraph[0].Arrays[3][sc.Index] = (float)r_depth_entry_ask_l4.Quantity;

	// sum of the asks
	t_MarketDataQuantity sum_ask = r_depth_entry_ask_l1.Quantity + r_depth_entry_ask_l2.Quantity + r_depth_entry_ask_l3.Quantity + r_depth_entry_ask_l4.Quantity;
	sc.Subgraph[0][sc.Index] = (float)sum_ask;

	// do all the same for bids
	s_MarketDepthEntry r_depth_entry_bid_l1;
	s_MarketDepthEntry r_depth_entry_bid_l2;
	s_MarketDepthEntry r_depth_entry_bid_l3;
	s_MarketDepthEntry r_depth_entry_bid_l4;

	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l1, 0);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l2, 1);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l3, 2);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l4, 3);

	sc.Subgraph[1].Arrays[0][sc.Index] = (float)r_depth_entry_bid_l1.Quantity;
	sc.Subgraph[1].Arrays[1][sc.Index] = (float)r_depth_entry_bid_l2.Quantity;
	sc.Subgraph[1].Arrays[2][sc.Index] = (float)r_depth_entry_bid_l3.Quantity;
	sc.Subgraph[1].Arrays[3][sc.Index] = (float)r_depth_entry_bid_l4.Quantity;

	t_MarketDataQuantity sum_bid = r_depth_entry_bid_l1.Quantity + r_depth_entry_bid_l2.Quantity + r_depth_entry_bid_l3.Quantity + r_depth_entry_bid_l4.Quantity;
	sc.Subgraph[1][sc.Index] = (float)sum_bid;

	// make the average from the last 10 indexes for bids and asks
	float asks = sc.Subgraph[0][sc.Index];
	float bids = sc.Subgraph[1][sc.Index];

	for (int i = 0; i < 10; i++)
	{
		asks += sc.Subgraph[0][sc.Index - i];
		bids += sc.Subgraph[1][sc.Index - i];

		sc.Subgraph[10][sc.Index] = asks;
		sc.Subgraph[11][sc.Index] = bids;
	}
}

// ok - stejne jako predchozi ale pro 12 levelu
SCSFExport scsf_pocet_kotaci_l12(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "DOM Bid/Ask Quotes Number (12 levels)";

		//asks
		sc.Subgraph[0].Arrays[0];
		sc.Subgraph[0].Arrays[1];
		sc.Subgraph[0].Arrays[2];
		sc.Subgraph[0].Arrays[3];
		sc.Subgraph[0].Arrays[4];
		sc.Subgraph[0].Arrays[5];
		sc.Subgraph[0].Arrays[6];
		sc.Subgraph[0].Arrays[7];
		sc.Subgraph[0].Arrays[8];
		sc.Subgraph[0].Arrays[9];
		sc.Subgraph[0].Arrays[10];
		sc.Subgraph[0].Arrays[11];
		sc.Subgraph[0].Arrays[12];
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_IGNORE;

		//bids
		sc.Subgraph[1].Arrays[0];
		sc.Subgraph[1].Arrays[1];
		sc.Subgraph[1].Arrays[2];
		sc.Subgraph[1].Arrays[3];
		sc.Subgraph[1].Arrays[4];
		sc.Subgraph[1].Arrays[5];
		sc.Subgraph[1].Arrays[6];
		sc.Subgraph[1].Arrays[7];
		sc.Subgraph[1].Arrays[8];
		sc.Subgraph[1].Arrays[9];
		sc.Subgraph[1].Arrays[10];
		sc.Subgraph[1].Arrays[11];
		sc.Subgraph[1].Arrays[12];
		sc.Subgraph[1].DrawStyle = DRAWSTYLE_IGNORE;

		// cumulative asks/bids
		sc.Subgraph[10].Name = "Ask";
		sc.Subgraph[10].LineLabel |= LL_DISPLAY_NAME | LL_DISPLAY_VALUE;
		sc.Subgraph[10].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[10].PrimaryColor = RGB(0, 255, 0);

		sc.Subgraph[11].Name = "Bid";
		sc.Subgraph[11].LineLabel |= LL_DISPLAY_NAME | LL_DISPLAY_VALUE;
		sc.Subgraph[11].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[11].PrimaryColor = RGB(255, 0, 0);

		sc.UsesMarketDepthData = TRUE;

		sc.AutoLoop = 1;
		sc.FreeDLL = 1;

		return;
	}

	s_MarketDepthEntry r_depth_entry_ask_l1;
	s_MarketDepthEntry r_depth_entry_ask_l2;
	s_MarketDepthEntry r_depth_entry_ask_l3;
	s_MarketDepthEntry r_depth_entry_ask_l4;
	s_MarketDepthEntry r_depth_entry_ask_l5;
	s_MarketDepthEntry r_depth_entry_ask_l6;
	s_MarketDepthEntry r_depth_entry_ask_l7;
	s_MarketDepthEntry r_depth_entry_ask_l8;
	s_MarketDepthEntry r_depth_entry_ask_l9;
	s_MarketDepthEntry r_depth_entry_ask_l10;
	s_MarketDepthEntry r_depth_entry_ask_l11;
	s_MarketDepthEntry r_depth_entry_ask_l12;

	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l1, 0); 
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l2, 1); 
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l3, 2);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l4, 3); 
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l5, 4); 
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l6, 5); 
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l7, 6); 
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l8, 7); 
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l9, 8);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l10, 9);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l11, 10);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l12, 11);

	sc.Subgraph[0].Arrays[0][sc.Index] = (float)r_depth_entry_ask_l1.Quantity;
	sc.Subgraph[0].Arrays[1][sc.Index] = (float)r_depth_entry_ask_l2.Quantity;
	sc.Subgraph[0].Arrays[2][sc.Index] = (float)r_depth_entry_ask_l3.Quantity;
	sc.Subgraph[0].Arrays[3][sc.Index] = (float)r_depth_entry_ask_l4.Quantity;
	sc.Subgraph[0].Arrays[4][sc.Index] = (float)r_depth_entry_ask_l5.Quantity;
	sc.Subgraph[0].Arrays[5][sc.Index] = (float)r_depth_entry_ask_l6.Quantity;
	sc.Subgraph[0].Arrays[6][sc.Index] = (float)r_depth_entry_ask_l7.Quantity;
	sc.Subgraph[0].Arrays[7][sc.Index] = (float)r_depth_entry_ask_l8.Quantity;
	sc.Subgraph[0].Arrays[8][sc.Index] = (float)r_depth_entry_ask_l9.Quantity;
	sc.Subgraph[0].Arrays[9][sc.Index] = (float)r_depth_entry_ask_l10.Quantity;
	sc.Subgraph[0].Arrays[10][sc.Index] = (float)r_depth_entry_ask_l11.Quantity;
	sc.Subgraph[0].Arrays[11][sc.Index] = (float)r_depth_entry_ask_l12.Quantity;

	t_MarketDataQuantity sum_ask =  r_depth_entry_ask_l1.Quantity +
									r_depth_entry_ask_l2.Quantity +
									r_depth_entry_ask_l3.Quantity +
									r_depth_entry_ask_l4.Quantity +
									r_depth_entry_ask_l5.Quantity +
									r_depth_entry_ask_l6.Quantity +
									r_depth_entry_ask_l7.Quantity +
									r_depth_entry_ask_l8.Quantity +
									r_depth_entry_ask_l9.Quantity +
									r_depth_entry_ask_l10.Quantity +
									r_depth_entry_ask_l11.Quantity +
									r_depth_entry_ask_l12.Quantity;

	sc.Subgraph[0][sc.Index] = (float)sum_ask;

	//bids
	s_MarketDepthEntry r_depth_entry_bid_l1;
	s_MarketDepthEntry r_depth_entry_bid_l2;
	s_MarketDepthEntry r_depth_entry_bid_l3;
	s_MarketDepthEntry r_depth_entry_bid_l4;
	s_MarketDepthEntry r_depth_entry_bid_l5;
	s_MarketDepthEntry r_depth_entry_bid_l6;
	s_MarketDepthEntry r_depth_entry_bid_l7;
	s_MarketDepthEntry r_depth_entry_bid_l8;
	s_MarketDepthEntry r_depth_entry_bid_l9;
	s_MarketDepthEntry r_depth_entry_bid_l10;
	s_MarketDepthEntry r_depth_entry_bid_l11;
	s_MarketDepthEntry r_depth_entry_bid_l12;

	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l1, 0);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l2, 1);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l3, 2);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l4, 3);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l5, 4);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l6, 5);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l7, 6);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l8, 7);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l9, 8);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l10, 9);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l11, 10);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l12, 11);

	sc.Subgraph[1].Arrays[0][sc.Index] = (float)r_depth_entry_bid_l1.Quantity;
	sc.Subgraph[1].Arrays[1][sc.Index] = (float)r_depth_entry_bid_l2.Quantity;
	sc.Subgraph[1].Arrays[2][sc.Index] = (float)r_depth_entry_bid_l3.Quantity;
	sc.Subgraph[1].Arrays[3][sc.Index] = (float)r_depth_entry_bid_l4.Quantity;
	sc.Subgraph[1].Arrays[4][sc.Index] = (float)r_depth_entry_bid_l5.Quantity;
	sc.Subgraph[1].Arrays[5][sc.Index] = (float)r_depth_entry_bid_l6.Quantity;
	sc.Subgraph[1].Arrays[6][sc.Index] = (float)r_depth_entry_bid_l7.Quantity;
	sc.Subgraph[1].Arrays[7][sc.Index] = (float)r_depth_entry_bid_l8.Quantity;
	sc.Subgraph[1].Arrays[8][sc.Index] = (float)r_depth_entry_bid_l9.Quantity;
	sc.Subgraph[1].Arrays[9][sc.Index] = (float)r_depth_entry_bid_l10.Quantity;
	sc.Subgraph[1].Arrays[10][sc.Index] = (float)r_depth_entry_bid_l11.Quantity;
	sc.Subgraph[1].Arrays[11][sc.Index] = (float)r_depth_entry_bid_l12.Quantity;

	t_MarketDataQuantity sum_bid =  r_depth_entry_bid_l1.Quantity +
									r_depth_entry_bid_l2.Quantity +
									r_depth_entry_bid_l3.Quantity +
									r_depth_entry_bid_l4.Quantity +
									r_depth_entry_bid_l5.Quantity +
									r_depth_entry_bid_l6.Quantity +
									r_depth_entry_bid_l7.Quantity +
									r_depth_entry_bid_l8.Quantity +
									r_depth_entry_bid_l9.Quantity +
									r_depth_entry_bid_l10.Quantity +
									r_depth_entry_bid_l11.Quantity +
									r_depth_entry_bid_l12.Quantity;

	sc.Subgraph[1][sc.Index] = (float)sum_bid;

	// make the average from the last 10 indexes for bids and asks
	float asks = sc.Subgraph[0][sc.Index];
	float bids = sc.Subgraph[1][sc.Index];

	for (int i = 0; i < 10; i++)
	{
		asks += sc.Subgraph[0][sc.Index - i];
		bids += sc.Subgraph[1][sc.Index - i];

		sc.Subgraph[10][sc.Index] = asks;
		sc.Subgraph[11][sc.Index] = bids;
	}
}

// ok - vali jen realtime kdyz jede DOM (nebo na replayi kdyz je dom nahranej) - po rekalkulaci zmizi, je potreba vyresit zapis do souboru
SCSFExport scsf_pocet_kotaci_bidask_rozdil(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "DOM Bid/Ask Quotes Number & Difference (4 levels)";

		//asks
		sc.Subgraph[0].Arrays[0];
		sc.Subgraph[0].Arrays[1];
		sc.Subgraph[0].Arrays[2];
		sc.Subgraph[0].Arrays[3];

		sc.Subgraph[0].DrawStyle = DRAWSTYLE_IGNORE;

		//bids
		sc.Subgraph[1].Arrays[0];
		sc.Subgraph[1].Arrays[1];
		sc.Subgraph[1].Arrays[2];
		sc.Subgraph[1].Arrays[3];

		sc.Subgraph[1].DrawStyle = DRAWSTYLE_IGNORE;

		// sum asks/bids
		sc.Subgraph[10].Name = "Ask quotes";
		sc.Subgraph[10].DrawStyle = DRAWSTYLE_IGNORE;

		sc.Subgraph[11].Name = "Bid quotes";
		sc.Subgraph[11].DrawStyle = DRAWSTYLE_IGNORE;

		// bid/ask diff
		sc.Subgraph[12].Name = "Ask-Bid difference";
		sc.Subgraph[12].DrawStyle = DRAWSTYLE_BAR;
		sc.Subgraph[12].PrimaryColor = RGB(0, 255, 0);
		sc.Subgraph[12].DrawZeros = TRUE;

		sc.Subgraph[13].Name = "Bid-Ask difference";
		sc.Subgraph[13].DrawStyle = DRAWSTYLE_BAR;
		sc.Subgraph[13].PrimaryColor = RGB(255, 0, 0);
		sc.Subgraph[13].DrawZeros = TRUE;
		
		sc.UsesMarketDepthData = TRUE;

		sc.AutoLoop = 1;
		sc.FreeDLL = 1;

		return;
	}

	// define 4 references for 4 ask price levels
	s_MarketDepthEntry r_depth_entry_ask_l1;
	s_MarketDepthEntry r_depth_entry_ask_l2;
	s_MarketDepthEntry r_depth_entry_ask_l3;
	s_MarketDepthEntry r_depth_entry_ask_l4;

	//this is quite a tricky function sc.GetAskMarketDepthEntryAtLevel taking the reference to the struct s_MarketDepthEntry as a parametr and returning it back 
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l1, 0); // the values at the 1 ask level 
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l2, 1); // the values at the 2 ask level
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l3, 2); // the values at the 3 ask level
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l4, 3); // the values at the 4 ask level

	// get the quantity (of ask) for particular levels
	sc.Subgraph[0].Arrays[0][sc.Index] = (float)r_depth_entry_ask_l1.Quantity;
	sc.Subgraph[0].Arrays[1][sc.Index] = (float)r_depth_entry_ask_l2.Quantity;
	sc.Subgraph[0].Arrays[2][sc.Index] = (float)r_depth_entry_ask_l3.Quantity;
	sc.Subgraph[0].Arrays[3][sc.Index] = (float)r_depth_entry_ask_l4.Quantity;

	// sum of the asks
	t_MarketDataQuantity sum_ask = r_depth_entry_ask_l1.Quantity + r_depth_entry_ask_l2.Quantity + r_depth_entry_ask_l3.Quantity + r_depth_entry_ask_l4.Quantity;
	sc.Subgraph[0][sc.Index] = (float)sum_ask;

	// do all the same for bids
	s_MarketDepthEntry r_depth_entry_bid_l1;
	s_MarketDepthEntry r_depth_entry_bid_l2;
	s_MarketDepthEntry r_depth_entry_bid_l3;
	s_MarketDepthEntry r_depth_entry_bid_l4;

	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l1, 0);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l2, 1);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l3, 2);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l4, 3);

	sc.Subgraph[1].Arrays[0][sc.Index] = (float)r_depth_entry_bid_l1.Quantity;
	sc.Subgraph[1].Arrays[1][sc.Index] = (float)r_depth_entry_bid_l2.Quantity;
	sc.Subgraph[1].Arrays[2][sc.Index] = (float)r_depth_entry_bid_l3.Quantity;
	sc.Subgraph[1].Arrays[3][sc.Index] = (float)r_depth_entry_bid_l4.Quantity;

	t_MarketDataQuantity sum_bid = r_depth_entry_bid_l1.Quantity + r_depth_entry_bid_l2.Quantity + r_depth_entry_bid_l3.Quantity + r_depth_entry_bid_l4.Quantity;
	sc.Subgraph[1][sc.Index] = (float)sum_bid;

	// make the sum from the last 11 indexes for bids and asks
	float asks = sc.Subgraph[0][sc.Index];
	float bids = sc.Subgraph[1][sc.Index];

	for (int i = 0; i < 10; i++)
	{
		asks += sc.Subgraph[0][sc.Index - i];
		bids += sc.Subgraph[1][sc.Index - i];
			
	}
	
	sc.Subgraph[10][sc.Index] = asks;
	sc.Subgraph[11][sc.Index] = bids;

	float ask_diff = asks - bids;
	float bid_diff = bids - asks;

	if (asks - bids > 0) 
		sc.Subgraph[12][sc.Index] = ask_diff;
	else
		sc.Subgraph[13][sc.Index] = - bid_diff;
	
}

// ok - stejne jako predchozi ale pro 12 levelu
SCSFExport scsf_pocet_kotaci_l12_rozdil(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "DOM Bid/Ask Quotes Number & Difference (12 levels)";

		//asks
		sc.Subgraph[0].Arrays[0];
		sc.Subgraph[0].Arrays[1];
		sc.Subgraph[0].Arrays[2];
		sc.Subgraph[0].Arrays[3];
		sc.Subgraph[0].Arrays[4];
		sc.Subgraph[0].Arrays[5];
		sc.Subgraph[0].Arrays[6];
		sc.Subgraph[0].Arrays[7];
		sc.Subgraph[0].Arrays[8];
		sc.Subgraph[0].Arrays[9];
		sc.Subgraph[0].Arrays[10];
		sc.Subgraph[0].Arrays[11];
		sc.Subgraph[0].Arrays[12];

		sc.Subgraph[0].DrawStyle = DRAWSTYLE_IGNORE;

		//bids
		sc.Subgraph[1].Arrays[0];
		sc.Subgraph[1].Arrays[1];
		sc.Subgraph[1].Arrays[2];
		sc.Subgraph[1].Arrays[3];
		sc.Subgraph[1].Arrays[4];
		sc.Subgraph[1].Arrays[5];
		sc.Subgraph[1].Arrays[6];
		sc.Subgraph[1].Arrays[7];
		sc.Subgraph[1].Arrays[8];
		sc.Subgraph[1].Arrays[9];
		sc.Subgraph[1].Arrays[10];
		sc.Subgraph[1].Arrays[11];
		sc.Subgraph[1].Arrays[12];

		sc.Subgraph[1].DrawStyle = DRAWSTYLE_IGNORE;

		// cumulative asks/bids
		sc.Subgraph[10].Name = "Ask";
		sc.Subgraph[10].DrawStyle = DRAWSTYLE_IGNORE;

		sc.Subgraph[11].Name = "Bid";
		sc.Subgraph[10].DrawStyle = DRAWSTYLE_IGNORE;

		// bid/ask diff
		sc.Subgraph[12].Name = "Ask-Bid difference";
		sc.Subgraph[12].DrawStyle = DRAWSTYLE_BAR;
		sc.Subgraph[12].PrimaryColor = RGB(0, 255, 0);
		sc.Subgraph[12].DrawZeros = TRUE;

		sc.Subgraph[13].Name = "Bid-Ask difference";
		sc.Subgraph[13].DrawStyle = DRAWSTYLE_BAR;
		sc.Subgraph[13].PrimaryColor = RGB(255, 0, 0);
		sc.Subgraph[13].DrawZeros = TRUE;

		sc.UsesMarketDepthData = TRUE;

		sc.AutoLoop = 1;
		sc.FreeDLL = 1;

		return;
	}

	s_MarketDepthEntry r_depth_entry_ask_l1;
	s_MarketDepthEntry r_depth_entry_ask_l2;
	s_MarketDepthEntry r_depth_entry_ask_l3;
	s_MarketDepthEntry r_depth_entry_ask_l4;
	s_MarketDepthEntry r_depth_entry_ask_l5;
	s_MarketDepthEntry r_depth_entry_ask_l6;
	s_MarketDepthEntry r_depth_entry_ask_l7;
	s_MarketDepthEntry r_depth_entry_ask_l8;
	s_MarketDepthEntry r_depth_entry_ask_l9;
	s_MarketDepthEntry r_depth_entry_ask_l10;
	s_MarketDepthEntry r_depth_entry_ask_l11;
	s_MarketDepthEntry r_depth_entry_ask_l12;

	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l1, 0);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l2, 1);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l3, 2);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l4, 3);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l5, 4);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l6, 5);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l7, 6);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l8, 7);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l9, 8);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l10, 9);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l11, 10);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l12, 11);

	sc.Subgraph[0].Arrays[0][sc.Index] = (float)r_depth_entry_ask_l1.Quantity;
	sc.Subgraph[0].Arrays[1][sc.Index] = (float)r_depth_entry_ask_l2.Quantity;
	sc.Subgraph[0].Arrays[2][sc.Index] = (float)r_depth_entry_ask_l3.Quantity;
	sc.Subgraph[0].Arrays[3][sc.Index] = (float)r_depth_entry_ask_l4.Quantity;
	sc.Subgraph[0].Arrays[4][sc.Index] = (float)r_depth_entry_ask_l5.Quantity;
	sc.Subgraph[0].Arrays[5][sc.Index] = (float)r_depth_entry_ask_l6.Quantity;
	sc.Subgraph[0].Arrays[6][sc.Index] = (float)r_depth_entry_ask_l7.Quantity;
	sc.Subgraph[0].Arrays[7][sc.Index] = (float)r_depth_entry_ask_l8.Quantity;
	sc.Subgraph[0].Arrays[8][sc.Index] = (float)r_depth_entry_ask_l9.Quantity;
	sc.Subgraph[0].Arrays[9][sc.Index] = (float)r_depth_entry_ask_l10.Quantity;
	sc.Subgraph[0].Arrays[10][sc.Index] = (float)r_depth_entry_ask_l11.Quantity;
	sc.Subgraph[0].Arrays[11][sc.Index] = (float)r_depth_entry_ask_l12.Quantity;

	t_MarketDataQuantity sum_ask = r_depth_entry_ask_l1.Quantity +
		r_depth_entry_ask_l2.Quantity +
		r_depth_entry_ask_l3.Quantity +
		r_depth_entry_ask_l4.Quantity +
		r_depth_entry_ask_l5.Quantity +
		r_depth_entry_ask_l6.Quantity +
		r_depth_entry_ask_l7.Quantity +
		r_depth_entry_ask_l8.Quantity +
		r_depth_entry_ask_l9.Quantity +
		r_depth_entry_ask_l10.Quantity +
		r_depth_entry_ask_l11.Quantity +
		r_depth_entry_ask_l12.Quantity;

	sc.Subgraph[0][sc.Index] = (float)sum_ask;

	//bids
	s_MarketDepthEntry r_depth_entry_bid_l1;
	s_MarketDepthEntry r_depth_entry_bid_l2;
	s_MarketDepthEntry r_depth_entry_bid_l3;
	s_MarketDepthEntry r_depth_entry_bid_l4;
	s_MarketDepthEntry r_depth_entry_bid_l5;
	s_MarketDepthEntry r_depth_entry_bid_l6;
	s_MarketDepthEntry r_depth_entry_bid_l7;
	s_MarketDepthEntry r_depth_entry_bid_l8;
	s_MarketDepthEntry r_depth_entry_bid_l9;
	s_MarketDepthEntry r_depth_entry_bid_l10;
	s_MarketDepthEntry r_depth_entry_bid_l11;
	s_MarketDepthEntry r_depth_entry_bid_l12;

	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l1, 0);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l2, 1);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l3, 2);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l4, 3);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l5, 4);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l6, 5);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l7, 6);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l8, 7);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l9, 8);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l10, 9);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l11, 10);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l12, 11);

	sc.Subgraph[1].Arrays[0][sc.Index] = (float)r_depth_entry_bid_l1.Quantity;
	sc.Subgraph[1].Arrays[1][sc.Index] = (float)r_depth_entry_bid_l2.Quantity;
	sc.Subgraph[1].Arrays[2][sc.Index] = (float)r_depth_entry_bid_l3.Quantity;
	sc.Subgraph[1].Arrays[3][sc.Index] = (float)r_depth_entry_bid_l4.Quantity;
	sc.Subgraph[1].Arrays[4][sc.Index] = (float)r_depth_entry_bid_l5.Quantity;
	sc.Subgraph[1].Arrays[5][sc.Index] = (float)r_depth_entry_bid_l6.Quantity;
	sc.Subgraph[1].Arrays[6][sc.Index] = (float)r_depth_entry_bid_l7.Quantity;
	sc.Subgraph[1].Arrays[7][sc.Index] = (float)r_depth_entry_bid_l8.Quantity;
	sc.Subgraph[1].Arrays[8][sc.Index] = (float)r_depth_entry_bid_l9.Quantity;
	sc.Subgraph[1].Arrays[9][sc.Index] = (float)r_depth_entry_bid_l10.Quantity;
	sc.Subgraph[1].Arrays[10][sc.Index] = (float)r_depth_entry_bid_l11.Quantity;
	sc.Subgraph[1].Arrays[11][sc.Index] = (float)r_depth_entry_bid_l12.Quantity;

	t_MarketDataQuantity sum_bid = r_depth_entry_bid_l1.Quantity +
		r_depth_entry_bid_l2.Quantity +
		r_depth_entry_bid_l3.Quantity +
		r_depth_entry_bid_l4.Quantity +
		r_depth_entry_bid_l5.Quantity +
		r_depth_entry_bid_l6.Quantity +
		r_depth_entry_bid_l7.Quantity +
		r_depth_entry_bid_l8.Quantity +
		r_depth_entry_bid_l9.Quantity +
		r_depth_entry_bid_l10.Quantity +
		r_depth_entry_bid_l11.Quantity +
		r_depth_entry_bid_l12.Quantity;

	sc.Subgraph[1][sc.Index] = (float)sum_bid;

	// make the average from the last 10 indexes for bids and asks
	float asks = sc.Subgraph[0][sc.Index];
	float bids = sc.Subgraph[1][sc.Index];

	for (int i = 0; i < 10; i++)
	{
		asks += sc.Subgraph[0][sc.Index - i];
		bids += sc.Subgraph[1][sc.Index - i];

		sc.Subgraph[10][sc.Index] = asks;
		sc.Subgraph[11][sc.Index] = bids;
	}


	float ask_diff = asks - bids;
	float bid_diff = bids - asks;

	if (asks - bids > 0)
		sc.Subgraph[12][sc.Index] = ask_diff;
	else
		sc.Subgraph[13][sc.Index] = -bid_diff;

}

SCSFExport scsf_pocet_kotaci_l12_rozdil_filtr(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "DOM Bid/Ask Quotes Number & Difference (12 levels) (filtr)";

		//asks
		sc.Subgraph[0].Arrays[0];
		sc.Subgraph[0].Arrays[1];
		sc.Subgraph[0].Arrays[2];
		sc.Subgraph[0].Arrays[3];
		sc.Subgraph[0].Arrays[4];
		sc.Subgraph[0].Arrays[5];
		sc.Subgraph[0].Arrays[6];
		sc.Subgraph[0].Arrays[7];
		sc.Subgraph[0].Arrays[8];
		sc.Subgraph[0].Arrays[9];
		sc.Subgraph[0].Arrays[10];
		sc.Subgraph[0].Arrays[11];
		sc.Subgraph[0].Arrays[12];

		sc.Subgraph[0].DrawStyle = DRAWSTYLE_IGNORE;

		//bids
		sc.Subgraph[1].Arrays[0];
		sc.Subgraph[1].Arrays[1];
		sc.Subgraph[1].Arrays[2];
		sc.Subgraph[1].Arrays[3];
		sc.Subgraph[1].Arrays[4];
		sc.Subgraph[1].Arrays[5];
		sc.Subgraph[1].Arrays[6];
		sc.Subgraph[1].Arrays[7];
		sc.Subgraph[1].Arrays[8];
		sc.Subgraph[1].Arrays[9];
		sc.Subgraph[1].Arrays[10];
		sc.Subgraph[1].Arrays[11];
		sc.Subgraph[1].Arrays[12];

		sc.Subgraph[1].DrawStyle = DRAWSTYLE_IGNORE;

		// cumulative asks/bids
		sc.Subgraph[10].Name = "Ask";
		sc.Subgraph[10].DrawStyle = DRAWSTYLE_IGNORE;

		sc.Subgraph[11].Name = "Bid";
		sc.Subgraph[10].DrawStyle = DRAWSTYLE_IGNORE;

		// bid/ask diff
		sc.Subgraph[12].Name = "Ask-Bid difference";
		sc.Subgraph[12].DrawStyle = DRAWSTYLE_BAR;
		sc.Subgraph[12].PrimaryColor = RGB(0, 255, 0);
		sc.Subgraph[12].DrawZeros = TRUE;

		sc.Subgraph[13].Name = "Bid-Ask difference";
		sc.Subgraph[13].DrawStyle = DRAWSTYLE_BAR;
		sc.Subgraph[13].PrimaryColor = RGB(255, 0, 0);
		sc.Subgraph[13].DrawZeros = TRUE;

		sc.UsesMarketDepthData = TRUE;

		sc.AutoLoop = 1;
		sc.FreeDLL = 1;

		return;
	}

	s_MarketDepthEntry r_depth_entry_ask_l1;
	s_MarketDepthEntry r_depth_entry_ask_l2;
	s_MarketDepthEntry r_depth_entry_ask_l3;
	s_MarketDepthEntry r_depth_entry_ask_l4;
	s_MarketDepthEntry r_depth_entry_ask_l5;
	s_MarketDepthEntry r_depth_entry_ask_l6;
	s_MarketDepthEntry r_depth_entry_ask_l7;
	s_MarketDepthEntry r_depth_entry_ask_l8;
	s_MarketDepthEntry r_depth_entry_ask_l9;
	s_MarketDepthEntry r_depth_entry_ask_l10;
	s_MarketDepthEntry r_depth_entry_ask_l11;
	s_MarketDepthEntry r_depth_entry_ask_l12;

	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l1, 0);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l2, 1);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l3, 2);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l4, 3);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l5, 4);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l6, 5);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l7, 6);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l8, 7);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l9, 8);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l10, 9);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l11, 10);
	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_l12, 11);

	sc.Subgraph[0].Arrays[0][sc.Index] = (float)r_depth_entry_ask_l1.Quantity;
	sc.Subgraph[0].Arrays[1][sc.Index] = (float)r_depth_entry_ask_l2.Quantity;
	sc.Subgraph[0].Arrays[2][sc.Index] = (float)r_depth_entry_ask_l3.Quantity;
	sc.Subgraph[0].Arrays[3][sc.Index] = (float)r_depth_entry_ask_l4.Quantity;
	sc.Subgraph[0].Arrays[4][sc.Index] = (float)r_depth_entry_ask_l5.Quantity;
	sc.Subgraph[0].Arrays[5][sc.Index] = (float)r_depth_entry_ask_l6.Quantity;
	sc.Subgraph[0].Arrays[6][sc.Index] = (float)r_depth_entry_ask_l7.Quantity;
	sc.Subgraph[0].Arrays[7][sc.Index] = (float)r_depth_entry_ask_l8.Quantity;
	sc.Subgraph[0].Arrays[8][sc.Index] = (float)r_depth_entry_ask_l9.Quantity;
	sc.Subgraph[0].Arrays[9][sc.Index] = (float)r_depth_entry_ask_l10.Quantity;
	sc.Subgraph[0].Arrays[10][sc.Index] = (float)r_depth_entry_ask_l11.Quantity;
	sc.Subgraph[0].Arrays[11][sc.Index] = (float)r_depth_entry_ask_l12.Quantity;

	t_MarketDataQuantity sum_ask =  r_depth_entry_ask_l1.Quantity +
									r_depth_entry_ask_l2.Quantity +
									r_depth_entry_ask_l3.Quantity +
									r_depth_entry_ask_l4.Quantity +
									r_depth_entry_ask_l5.Quantity +
									r_depth_entry_ask_l6.Quantity +
									r_depth_entry_ask_l7.Quantity +
									r_depth_entry_ask_l8.Quantity +
									r_depth_entry_ask_l9.Quantity +
									r_depth_entry_ask_l10.Quantity +
									r_depth_entry_ask_l11.Quantity +
									r_depth_entry_ask_l12.Quantity;

	sc.Subgraph[0][sc.Index] = (float)sum_ask;

	//bids
	s_MarketDepthEntry r_depth_entry_bid_l1;
	s_MarketDepthEntry r_depth_entry_bid_l2;
	s_MarketDepthEntry r_depth_entry_bid_l3;
	s_MarketDepthEntry r_depth_entry_bid_l4;
	s_MarketDepthEntry r_depth_entry_bid_l5;
	s_MarketDepthEntry r_depth_entry_bid_l6;
	s_MarketDepthEntry r_depth_entry_bid_l7;
	s_MarketDepthEntry r_depth_entry_bid_l8;
	s_MarketDepthEntry r_depth_entry_bid_l9;
	s_MarketDepthEntry r_depth_entry_bid_l10;
	s_MarketDepthEntry r_depth_entry_bid_l11;
	s_MarketDepthEntry r_depth_entry_bid_l12;

	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l1, 0);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l2, 1);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l3, 2);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l4, 3);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l5, 4);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l6, 5);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l7, 6);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l8, 7);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l9, 8);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l10, 9);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l11, 10);
	sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_l12, 11);

	sc.Subgraph[1].Arrays[0][sc.Index] = (float)r_depth_entry_bid_l1.Quantity;
	sc.Subgraph[1].Arrays[1][sc.Index] = (float)r_depth_entry_bid_l2.Quantity;
	sc.Subgraph[1].Arrays[2][sc.Index] = (float)r_depth_entry_bid_l3.Quantity;
	sc.Subgraph[1].Arrays[3][sc.Index] = (float)r_depth_entry_bid_l4.Quantity;
	sc.Subgraph[1].Arrays[4][sc.Index] = (float)r_depth_entry_bid_l5.Quantity;
	sc.Subgraph[1].Arrays[5][sc.Index] = (float)r_depth_entry_bid_l6.Quantity;
	sc.Subgraph[1].Arrays[6][sc.Index] = (float)r_depth_entry_bid_l7.Quantity;
	sc.Subgraph[1].Arrays[7][sc.Index] = (float)r_depth_entry_bid_l8.Quantity;
	sc.Subgraph[1].Arrays[8][sc.Index] = (float)r_depth_entry_bid_l9.Quantity;
	sc.Subgraph[1].Arrays[9][sc.Index] = (float)r_depth_entry_bid_l10.Quantity;
	sc.Subgraph[1].Arrays[10][sc.Index] = (float)r_depth_entry_bid_l11.Quantity;
	sc.Subgraph[1].Arrays[11][sc.Index] = (float)r_depth_entry_bid_l12.Quantity;

	t_MarketDataQuantity sum_bid =  r_depth_entry_bid_l1.Quantity +
									r_depth_entry_bid_l2.Quantity +
									r_depth_entry_bid_l3.Quantity +
									r_depth_entry_bid_l4.Quantity +
									r_depth_entry_bid_l4.Quantity +
									r_depth_entry_bid_l6.Quantity +
									r_depth_entry_bid_l7.Quantity +
									r_depth_entry_bid_l8.Quantity +
									r_depth_entry_bid_l9.Quantity +
									r_depth_entry_bid_l10.Quantity +
									r_depth_entry_bid_l11.Quantity +
									r_depth_entry_bid_l12.Quantity;

	sc.Subgraph[1][sc.Index] = (float)sum_bid;

	// make the sum from the last 10 indexes for bids and asks
	float asks = sc.Subgraph[0][sc.Index];
	float bids = sc.Subgraph[1][sc.Index];

	for (int i = 0; i < 10; i++)
	{
		asks += sc.Subgraph[0][sc.Index - i];
		bids += sc.Subgraph[1][sc.Index - i];

		sc.Subgraph[10][sc.Index] = asks;
		sc.Subgraph[11][sc.Index] = bids;
	}

	// calculate the difference
	float ask_diff = asks - bids;
	float bid_diff = bids - asks;

	if (asks - bids > 0)
		sc.Subgraph[12][sc.Index] = ask_diff;
	else
		sc.Subgraph[13][sc.Index] = -bid_diff;




}

// ok - vali jen realtime kdyz jede DOM (nebo na replayi kdyz je dom nahranej) - po rekalkulaci zmizi, je potreba vyresit zapis do souboru
SCSFExport scsf_BidAskDomQuotesNumber_toxa_refined(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "DOM Bid/Ask Quotes Number (4 levels) - toxa refined";

		//asks
		sc.Subgraph[0].Arrays[0];
		sc.Subgraph[0].Arrays[1];
		sc.Subgraph[0].Arrays[2];
		sc.Subgraph[0].Arrays[3];

		sc.Subgraph[0].DrawStyle = DRAWSTYLE_IGNORE;

		//bids
		sc.Subgraph[1].Arrays[0];
		sc.Subgraph[1].Arrays[1];
		sc.Subgraph[1].Arrays[2];
		sc.Subgraph[1].Arrays[3];

		sc.Subgraph[1].DrawStyle = DRAWSTYLE_IGNORE;

		// asks/bids
		sc.Subgraph[10].Name = "Ask";
		sc.Subgraph[10].LineLabel |= LL_DISPLAY_NAME | LL_DISPLAY_VALUE;
		sc.Subgraph[10].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[10].PrimaryColor = RGB(0, 255, 0);

		sc.Subgraph[11].Name = "Bid";
		sc.Subgraph[11].LineLabel |= LL_DISPLAY_NAME | LL_DISPLAY_VALUE;
		sc.Subgraph[11].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[11].PrimaryColor = RGB(255, 0, 0);

		sc.UsesMarketDepthData = TRUE;

		sc.AutoLoop = 1;
		sc.FreeDLL = 1;

		return;
	}
		
	s_MarketDepthEntry r_depth_entry_ask_array[4];
	s_MarketDepthEntry r_depth_entry_bid_array[4];

	for (int i = 0; i < 4; i++)	sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_array[i], i); 
	for (int i = 0; i < 4; i++) sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_array[i], i); 
	
	float sum_ask = 0;
	float sum_bid = 0;
	for (int i = 0; i < 4; i++)
	{
		float qa = (float)r_depth_entry_ask_array[i].Quantity;
		float qb = (float)r_depth_entry_bid_array[i].Quantity;
		sum_bid += qa;
		sum_ask += qb;
	}

	sc.Subgraph[0][sc.Index] = (float)sum_ask;
	sc.Subgraph[1][sc.Index] = (float)sum_bid;

	// make sum from the last 10 indexes for bids and asks
	float asks = sc.Subgraph[0][sc.Index];
	float bids = sc.Subgraph[1][sc.Index];

	for (int i = 0; i < 10; i++)
	{
		asks += sc.Subgraph[0][sc.Index - i];
		bids += sc.Subgraph[1][sc.Index - i];
	}

	sc.Subgraph[10][sc.Index] = asks;
	sc.Subgraph[11][sc.Index] = bids;
}

// - ok - FINALNI VERZE DLL 0. ukazuje historicky obraz rozdilu bidask kotaci na stanovenym poctu levelu 
SCSFExport scsf_BidAskDomQuotesNumberVariableLevels(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		
		sc.GraphName = "DOM Bid/Ask Quotes Sum - Var Levels";
		sc.StudyDescription = "DOM Bid/Ask Quotes Sum - Var Levels (dll 0)";

		//asks
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_IGNORE;

		//bids
		sc.Subgraph[1].DrawStyle = DRAWSTYLE_IGNORE;

		// asks/bids
		sc.Subgraph[10].Name = "Ask";
		sc.Subgraph[10].LineLabel |= LL_DISPLAY_NAME | LL_DISPLAY_VALUE;
		sc.Subgraph[10].DrawStyle = DRAWSTYLE_IGNORE;
		sc.Subgraph[10].PrimaryColor = RGB(0, 255, 0);

		sc.Subgraph[11].Name = "Bid";
		sc.Subgraph[11].LineLabel |= LL_DISPLAY_NAME | LL_DISPLAY_VALUE;
		sc.Subgraph[11].DrawStyle = DRAWSTYLE_IGNORE;
		sc.Subgraph[11].PrimaryColor = RGB(255, 0, 0);

		// bid/ask diff
		sc.Subgraph[12].Name = "Ask-Bid Diff";
		sc.Subgraph[12].DrawStyle = DRAWSTYLE_BAR;
		sc.Subgraph[12].PrimaryColor = RGB(0, 255, 0);
		sc.Subgraph[12].DrawZeros = TRUE;

		sc.Subgraph[13].Name = "Bid-Ask Diff";
		sc.Subgraph[13].DrawStyle = DRAWSTYLE_BAR;
		sc.Subgraph[13].PrimaryColor = RGB(255, 0, 0);
		sc.Subgraph[13].DrawZeros = TRUE;

		sc.Input[0].Name = "Number of levels";
		sc.Input[0].SetInt(12);

		sc.UsesMarketDepthData = TRUE;

		sc.AutoLoop = 1;
		sc.FreeDLL = 0;

		return;
	}

	//int x = sc.Input[0].GetInt();

	s_MarketDepthEntry r_depth_entry_ask_array[99]; // nejde pouzit variabilni x - musi tam bejt konstanta - zadavam nesmyslne velky cislo 99 (vic levlu urcite hodnotit nebudu)
	s_MarketDepthEntry r_depth_entry_bid_array[99];

	for (int i = 0; i <= sc.Input[0].GetInt(); i++) sc.GetAskMarketDepthEntryAtLevel(r_depth_entry_ask_array[i], i);
	for (int i = 0; i <= sc.Input[0].GetInt(); i++) sc.GetBidMarketDepthEntryAtLevel(r_depth_entry_bid_array[i], i);

	float sum_ask = 0;
	float sum_bid = 0;
	for (int i = 0; i <= sc.Input[0].GetInt(); i++)
	{
		float qa = (float)r_depth_entry_ask_array[i].Quantity;
		float qb = (float)r_depth_entry_bid_array[i].Quantity;
		sum_ask += qa;
		sum_bid += qb;
	}

	sc.Subgraph[0][sc.Index] = (float)sum_ask;
	sc.Subgraph[1][sc.Index] = (float)sum_bid;

	//make sum from the last 10 indexes for bids and asks
	float asks = sc.Subgraph[0][sc.Index];
	float bids = sc.Subgraph[1][sc.Index];

	for (int i = 0; i < 10; i++)
	{
		asks += sc.Subgraph[0][sc.Index - i];
		bids += sc.Subgraph[1][sc.Index - i];
	}

	//draw the sum
	sc.Subgraph[10][sc.Index] = asks;
	sc.Subgraph[11][sc.Index] = bids;

	float ask_diff = asks - bids;
	float bid_diff = bids - asks;

	if (asks - bids > 0)
		sc.Subgraph[12][sc.Index] = ask_diff;
	else
		sc.Subgraph[13][sc.Index] = -bid_diff;
}








/*=========== test zapisu do souboru=================================================================*/
SCSFExport scsf_WriteBarAndStudyDataToFile(SCStudyInterfaceRef sc)
{
	SCInputRef IncludeHiddenStudies = sc.Input[0];
	SCInputRef UseGMTTime = sc.Input[1];
	SCInputRef IncludeHiddenSubgraphs = sc.Input[2];

	if (sc.SetDefaults)
	{
		sc.GraphName = "__Write Bar and Study Data To File";

		sc.GraphRegion = 0;

		IncludeHiddenStudies.Name = "Include Hidden Studies";
		IncludeHiddenStudies.SetYesNo(true);

		//UseGMTTime.Name = "Use GMT Time";
		//UseGMTTime.SetYesNo(0);

		IncludeHiddenSubgraphs.Name = "Include Hidden Subgraphs";
		IncludeHiddenSubgraphs.SetYesNo(true);

		sc.TextInputName = "Path and File Name";

		sc.CalculationPrecedence = VERY_LOW_PREC_LEVEL;

		sc.AutoLoop = 0; //manual looping required
		sc.FreeDLL = 1;
		return;
	}

	if (sc.LastCallToFunction)
		return;

	SCString OutputPathAndFileName;
	if (sc.TextInput.GetLength() > 0)
	{
		OutputPathAndFileName = sc.TextInput;
	}
	else
	{
		OutputPathAndFileName.Format("%s-BarStudyData.csv", sc.Symbol.GetChars());
	}

	sc.WriteBarAndStudyDataToFile(sc.UpdateStartIndex, OutputPathAndFileName, IncludeHiddenStudies.GetYesNo(), IncludeHiddenSubgraphs.GetYesNo());

	return;
}