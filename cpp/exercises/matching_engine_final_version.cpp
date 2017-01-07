#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <memory>

class StringUtils
{
	public:
		static void tokenize(const std::string& input_line,
				  std::vector<std::string>& tokens)
		{
			char *pch = strtok (const_cast<char*>(input_line.c_str())," ");
			while (pch != NULL)
			{
				tokens.push_back(pch);
				pch = strtok (NULL, " ");
			}
		}
};

struct OrderType
{
	enum class ORDER_TYPE
	{
		GFD = 0,
		IOC = 1
	};

public:
	// Assumption that if str_order_type is not GFD , then its IOC
	static ORDER_TYPE toOrderType(const std::string& str_order_type)
	{
		return (str_order_type == "GFD" ? ORDER_TYPE::GFD : ORDER_TYPE::IOC);
	}

	static std::string toString(ORDER_TYPE order_type)
	{
		return ( order_type == ORDER_TYPE::GFD ? "GFD" : "IOC");
	}
};


struct OrderSide
{
	enum class ORDER_SIDE
	{
		BUY = 0,
		SELL = 1
	};

public:

	static ORDER_SIDE toOrderSide(const std::string& str_order_side)
	{
		return (str_order_side == "BUY" ? ORDER_SIDE::BUY : ORDER_SIDE::SELL);
	}

	static std::string toString(ORDER_SIDE order_side)
	{
		return ( order_side == ORDER_SIDE::BUY ? "BUY" : "SELL");
	}

};

/*
 * They are type defined for readability
 * If type of price changes to float or some class
 * change here , reflects everywhere
 */

typedef int PRICE;
typedef int QUANTITY;
typedef std::string ORDER_ID;

struct Order
{
	//OrderSide::ORDER_SIDE order_side;
	OrderType::ORDER_TYPE order_type;
	QUANTITY quantity;
	ORDER_ID order_id;

	Order(/*const OrderSide::ORDER_SIDE& s, */const OrderType::ORDER_TYPE t,const QUANTITY& q,const ORDER_ID& id):
				 order_type(t),
				 //order_side(s),
				 quantity(q),
				 order_id(id)
	{
		// Do nothing
	}
};

class OrderMatchingEngine
{
public:
	void process(const std::string& input_line)
	{
		std::vector<std::string> tokens;
		StringUtils::tokenize(input_line,tokens);


		if ("BUY" == tokens[0])
		{
			matchBuyOrder(/*OrderSide::toOrderSide(tokens[0]),*/
						  OrderType::toOrderType(tokens[1]),
						  std::stoi(tokens[2]),
					      std::stoi(tokens[3]),
					      tokens[4]);
		}

		if ( "SELL" == tokens[0])
		{
			matchSellOrder(/*OrderSide::toOrderSide(tokens[0]),*/
						  OrderType::toOrderType(tokens[1]),
						  std::stoi(tokens[2]),
						  std::stoi(tokens[3]),
						  tokens[4]);
		}

		if ( "CANCEL" == tokens[0])
		{
			cancelOrder(tokens[1]);
		}

		if ( "MODIFY" ==  tokens[0])
		{
			modifyOrder(tokens[1],
						OrderSide::toOrderSide(tokens[2]),
						std::stoi(tokens[3]),
						std::stoi(tokens[4]));
		}

		if ( "PRINT" == tokens[0])
		{
			printOutstandingOrders();
		}
	}




private:
	void matchSellOrder(/*const OrderSide::ORDER_SIDE order_side,*/
					   const OrderType::ORDER_TYPE order_type,
					   const PRICE & sell_price,
					   const QUANTITY & sell_quantity,
					   const ORDER_ID & order_id)
	{
		auto total_sell_quantity = sell_quantity;

		for ( auto buy_order_iterator = buy_orders.begin();
				buy_order_iterator != buy_orders.end() && (total_sell_quantity > 0);
				buy_order_iterator++ )
		{
			PRICE buy_price = buy_order_iterator->first;
			Order * buy_order = buy_order_iterator->second;

			if ( sell_price <= buy_price )
			{
				// exact match or buy quantity less
				if ( buy_order->quantity <= total_sell_quantity )
				{
					std::cout << "TRADE" << " "
								<< buy_order->order_id << " "
								<< buy_price << " "
								<< buy_order->quantity << " "
								<< order_id << " "
								<< sell_price << " "
								<< buy_order->quantity
								<< std::endl;

					total_sell_quantity -= buy_order->quantity;

					delete buy_order;
					buy_orders.erase(buy_order_iterator);
				}
				else
				{
					std::cout << "TRADE" << " "
							<< buy_order->order_id << " "
							<< buy_price << " "
							<< total_sell_quantity << " "
							<< order_id << " "
							<< sell_price << " "
							<< total_sell_quantity
							<< std::endl;

					// Buy quantity more than sell quantity
					buy_order->quantity -= total_sell_quantity;
					total_sell_quantity = 0;
				}
			}
		}

		// Some or all quantity pending to match for the given price
		if (total_sell_quantity != 0 &&
			order_type != OrderType::ORDER_TYPE::IOC)
		{
			Order * new_sell_order = new Order(/*order_side,*/order_type,total_sell_quantity,order_id);
			sell_orders.insert(std::pair < PRICE , Order*> (sell_price, new_sell_order));
		}
	}

	void matchBuyOrder(/*const OrderSide::ORDER_SIDE order_side,*/
			   const OrderType::ORDER_TYPE order_type,
			   const PRICE & buy_price,
			   const QUANTITY & buy_quantity,
			   const ORDER_ID & order_id)
	{
		auto total_buy_quantity = buy_quantity;

		for ( auto sell_order_iterator = sell_orders.begin();
				sell_order_iterator != sell_orders.end() && (total_buy_quantity > 0);
				sell_order_iterator++ )
		{
			PRICE sell_price = sell_order_iterator->first;
			Order * sell_order = sell_order_iterator->second;

			if ( buy_price >= sell_price )
			{


				// exact match or buy quantity less
				if ( sell_order->quantity <= total_buy_quantity )
				{
					std::cout << "TRADE" << " "
							<< sell_order->order_id << " "
							<< sell_price << " "
							<< sell_order->quantity << " "
							<< order_id << " "
							<< buy_price << " "
							<< sell_order->quantity
							<< std::endl;
					total_buy_quantity -= sell_order->quantity;

					delete sell_order_iterator->second;
					sell_orders.erase(sell_order_iterator);
				}
				else
				{
					std::cout << "TRADE" << " "
							<< sell_order->order_id << " "
							<< sell_price << " "
							<< total_buy_quantity << " "
							<< order_id << " "
							<< buy_price << " "
							<< total_buy_quantity
							<< std::endl;

					// Buy quantity more than sell quantity
					sell_order->quantity -= total_buy_quantity;
					total_buy_quantity = 0;
				}
			}
		}

		// Some or all quantity pending to match for the given price
		if (total_buy_quantity != 0 &&
			order_type != OrderType::ORDER_TYPE::IOC)
		{
			Order * new_buy_order = new Order(/*order_side,*/order_type,total_buy_quantity,order_id);
			buy_orders.insert(std::pair < PRICE , Order*> (buy_price, new_buy_order));
		}
	}

	void cancelOrder(const ORDER_ID & order_id_to_cancel)
	{
		// Check buy side
		for (auto buy_order = buy_orders.begin(); buy_order != buy_orders.end(); buy_order++)
		{
			if ( (buy_order->second)->order_id == order_id_to_cancel )
			{
				delete buy_order->second;
				buy_orders.erase(buy_order);
				return;
			}
		}

		// Check sell side
		for (auto sell_order = sell_orders.begin(); sell_order != sell_orders.end(); sell_order++)
		{
			if ( (sell_order->second)->order_id == order_id_to_cancel )
			{
				delete sell_order->second;
				sell_orders.erase(sell_order);
				return;
			}
		}

		// just ignore
	}

	void modifyOrder(const ORDER_ID & order_id_to_modify,
					 const OrderSide::ORDER_SIDE order_side,
					 const PRICE& new_price ,
					 const QUANTITY& new_quantity)

	{
		// Cancel order so that it will loose its place
		cancelOrder(order_id_to_modify);

		// Create new order because its order of execution should be later than existing orders
		(OrderSide::ORDER_SIDE::BUY == order_side ) ?
				matchBuyOrder(/*OrderSide::ORDER_SIDE::BUY,*/OrderType::ORDER_TYPE::GFD,new_price,new_quantity,order_id_to_modify) :
				matchSellOrder(/*OrderSide::ORDER_SIDE::SELL,*/OrderType::ORDER_TYPE::GFD,new_price,new_quantity,order_id_to_modify);
	}

	void printOutstandingOrders()
	{
		std::map<PRICE , QUANTITY , std::greater<int>> buy_side_open_orders;
		std::map<PRICE , QUANTITY> sell_side_open_orders;

		// Check buy side
		for (auto& buy_order : buy_orders)
		{
			buy_side_open_orders[buy_order.first] += (buy_order.second)->quantity;
		}

		// Check buy side
		for (auto sell_order : sell_orders)
		{
			sell_side_open_orders[sell_order.first] += (sell_order.second)->quantity;
		}

		std::cout << "SELL:" << std::endl;
		for (auto& sell_order : sell_side_open_orders)
		{
			std::cout << sell_order.first << " " << sell_order.second << std::endl;
		}

		std::cout << "BUY:" << std::endl;
		for (auto& buy_order : buy_side_open_orders)
		{
			std::cout << buy_order.first << " " << buy_order.second <<std::endl;
		}
	}

private:
	std::multimap< PRICE,Order *,std::greater<int> > buy_orders;
	std::multimap< PRICE,Order * > sell_orders;
};

int main()
{
	std::string input_line;
	OrderMatchingEngine engine;

	while (std::getline(std::cin, input_line) && input_line.size())
	{
		engine.process(input_line);
	}

	return 0;
}

