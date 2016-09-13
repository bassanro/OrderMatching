#ifndef ORDER_BOOK_HEADER
#define ORDER_BOOK_HEADER

#include "stdafx.h"
#include <deque>
#include "Order.h"
using namespace std;


class OrderBook
{
public:
	OrderBook(string stkName) : stockName(stockName) {};
	void match_order(Order ord);

private :
	// Bid Orders
	deque<Order> Buy;
	// Sell Order
	deque<Order> Sell;

	string stockName;

	int OrderBook::match_order_side(bool isBuySide, int inQuantity, deque<Order> & matchItems);
};

#endif