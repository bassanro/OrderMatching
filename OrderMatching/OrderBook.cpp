#include "stdafx.h"
#include "OrderBook.h"
#include "Order.h"

#include <iostream> 
using namespace std;

void OrderBook::match_order(Order ord)
{
	bool side = ord.is_buy();
	int inQuantity = ord.get_qunatity();
	deque<Order> matchItems;
	int matchedQty = match_order_side(side, inQuantity, matchItems);

	if (matchItems.size() > 0)
	{
		// Notify the user in other thread
		for (deque<Order>::iterator itr = matchItems.begin(); itr != matchItems.end(); itr++)
		{
			cout << "Order matched for trader " << itr->get_TraderName() << " of stocks " << itr->get_StockName() << endl;

			// Remove matched orders from orderBook. (Constant time removal)
			if (itr->is_buy())
				Buy.pop_front();
			else
				Sell.pop_front();
		}
	}

	// Insert the order in OrderBook if it's not matched;
	if (matchedQty != inQuantity)
	{
		ord.set_Quantity(inQuantity - matchedQty);
		if (side)
			Buy.push_back(ord);
		else
			Sell.push_back(ord);
	}
	else
		cout << "Order matched for trader " << ord.get_TraderName() << " of stocks " << ord.get_StockName() << endl;
}

inline int OrderBook::match_order_side(bool isBuySide, int inQuantity, deque<Order> & matchItems)
{
	int matched_qty = 0;
	deque<Order>::iterator itr;

	if (isBuySide)
	{
		for (itr = Sell.begin(); itr != Sell.end(); itr++)
		{
			int exisingOrderQty = itr->get_qunatity();
			if (inQuantity <= exisingOrderQty)
			{
				matched_qty += inQuantity;
				// Complete match
				if (inQuantity == exisingOrderQty)
				{
					matchItems.push_back(*itr);
				}
				else
				{
					// Update the partial match quantity.
					itr->set_Quantity(exisingOrderQty - inQuantity);
				}
				break;
			}
			else
			{
				matched_qty += exisingOrderQty;
				inQuantity -= exisingOrderQty;
				matchItems.push_back(*itr);
			}
		}
	}
	else
	{
		for (itr = Buy.begin(); itr != Buy.end(); itr++)
		{
			int exisingOrderQty = itr->get_qunatity();
			if (inQuantity <= exisingOrderQty)
			{
				matched_qty += inQuantity;
				// Complete match
				if (inQuantity == exisingOrderQty)
				{
					matchItems.push_back(*itr);
				}
				else
				{
					// Update the partial match quantity.
					itr->set_Quantity(exisingOrderQty - inQuantity);
				}
				break;
			}
			else
			{
				matched_qty +=  exisingOrderQty;
				inQuantity -= exisingOrderQty;
				matchItems.push_back(*itr);
			}
		}
	}

	return matched_qty;
}
