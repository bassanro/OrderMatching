#ifndef ORDER_HEADER
#define ORDER_HEADER

#include <string>
using namespace std;


class Order
{
public:
	// Constructor
	Order(string traderName, bool is_buy, int quantity, string stockName)
		: m_traderName(traderName),
		m_is_buy(is_buy),
		m_order_qty(quantity),
		m_stockName(stockName)
	{
	}


	// Copy Constructor
	Order(const Order &obj)
	{
		this->m_is_buy = obj.m_is_buy;
		this->m_order_qty = obj.m_order_qty;
		this->m_stockName = obj.m_stockName;
		this->m_traderName = obj.m_traderName;
	}

	// Assignment opeartor
	void operator=(const Order &obj)
	{
		this->m_is_buy = obj.m_is_buy;
		this->m_order_qty = obj.m_order_qty;
		this->m_stockName = obj.m_stockName;
		this->m_traderName = obj.m_traderName;
	}

	void reset() 
	{
		this->m_is_buy = 0;
		this->m_order_qty = 0;
		this->m_stockName.clear();
		this->m_traderName.clear();
	}

	//Getter functions.
	bool is_buy() const { return m_is_buy; }
	int get_qunatity() const { return m_order_qty; }
	string get_StockName() const { return m_stockName; }
	string get_TraderName() const { return m_traderName; }


	//Setter function.
	void set_Quantity(int qty) { this->m_order_qty = qty; }

private:
	bool m_is_buy;
	int m_order_qty;
	string m_stockName;
	string m_traderName;
};

#endif