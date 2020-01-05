#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>

class StringUtils {
public:
  static void tokenize(const std::string &input_line,
                       std::vector<std::string> &tokens) {
    char *pch = strtok(const_cast<char *>(input_line.c_str()), " ");
    while (pch != NULL) {
      tokens.push_back(pch);
      pch = strtok(NULL, " ");
    }
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

struct Order {
  enum class ORDER_TYPE { GFD = 0, IOC = 1 };
  // Assumption that if str_order_type is not GFD , then its IOC
  static ORDER_TYPE toOrderType(const std::string &str_order_type) {
    return (str_order_type == "GFD" ? ORDER_TYPE::GFD : ORDER_TYPE::IOC);
  }

  static std::string toString(ORDER_TYPE order_type) {
    return (order_type == ORDER_TYPE::GFD ? "GFD" : "IOC");
  }

  enum class ORDER_SIDE { BUY = 0, SELL = 1 };

  static ORDER_SIDE toOrderSide(const std::string &str_order_side) {
    return (str_order_side == "BUY" ? ORDER_SIDE::BUY : ORDER_SIDE::SELL);
  }

  static std::string toString(ORDER_SIDE order_side) {
    return (order_side == ORDER_SIDE::BUY ? "BUY" : "SELL");
  }

  ORDER_TYPE order_type;
  QUANTITY quantity;
  ORDER_ID order_id;

  Order(const ORDER_TYPE t, const QUANTITY &q, const ORDER_ID &id)
      : order_type(t), quantity(q), order_id(id) {
    // Do nothing
  }
};

class OrderMatchingEngine {
public:
  void process(const std::string &input_line) {
    std::vector<std::string> tokens;
    StringUtils::tokenize(input_line, tokens);

    if ("BUY" == tokens[0]) {
      matchBuyOrder(Order::toOrderType(tokens[1]), std::stoi(tokens[2]),
                    std::stoi(tokens[3]), tokens[4]);
    }

    if ("SELL" == tokens[0]) {
      matchSellOrder(Order::toOrderType(tokens[1]), std::stoi(tokens[2]),
                     std::stoi(tokens[3]), tokens[4]);
    }

    if ("CANCEL" == tokens[0]) {
      cancelOrder(tokens[1]);
    }

    if ("MODIFY" == tokens[0]) {
      modifyOrder(tokens[1], Order::toOrderSide(tokens[2]),
                  std::stoi(tokens[3]), std::stoi(tokens[4]));
    }

    if ("PRINT" == tokens[0]) {
      printOutstandingOrders();
    }
  }

private:
  void printTrade(const ORDER_ID &order_id1, const PRICE &price1,
                  const QUANTITY &quantity1, const ORDER_ID &order_id2,
                  const PRICE &price2, const QUANTITY &quantity2) {
    std::cout << "TRADE"
              << " " << order_id1 << " " << price1 << " " << quantity1 << " "
              << order_id2 << " " << price2 << " " << quantity2 << std::endl;
  }

  void matchSellOrder(const Order::ORDER_TYPE order_type,
                      const PRICE &sell_price, const QUANTITY &sell_quantity,
                      const ORDER_ID &order_id) {
    auto total_sell_quantity = sell_quantity;

    for (auto buy_order_iterator = _buy_orders.begin();
         buy_order_iterator != _buy_orders.end() && (total_sell_quantity > 0);
         buy_order_iterator++) {
      PRICE buy_price = buy_order_iterator->first;
      std::unique_ptr<Order> &buy_order = buy_order_iterator->second;

      if (sell_price <= buy_price) {
        // exact match or buy quantity less
        if (buy_order->quantity <= total_sell_quantity) {
          this->printTrade(buy_order->order_id, buy_price, buy_order->quantity,
                           order_id, sell_price, buy_order->quantity);
          total_sell_quantity -= buy_order->quantity;

          _buy_orders.erase(buy_order_iterator);
        } else {
          this->printTrade(buy_order->order_id, buy_price, total_sell_quantity,
                           order_id, sell_price, total_sell_quantity);

          // Buy quantity more than sell quantity
          buy_order->quantity -= total_sell_quantity;
          total_sell_quantity = 0;
        }
      }
    }

    // Some or all quantity pending to match for the given price
    if (total_sell_quantity != 0 && order_type != Order::ORDER_TYPE::IOC) {
      _sell_orders.insert(std::pair<PRICE, std::unique_ptr<Order>>(
          sell_price, std::unique_ptr<Order>(new Order(
                          order_type, total_sell_quantity, order_id))));
    }
  }

  void matchBuyOrder(const Order::ORDER_TYPE order_type, const PRICE &buy_price,
                     const QUANTITY &buy_quantity, const ORDER_ID &order_id) {
    auto total_buy_quantity = buy_quantity;

    for (auto sell_order_iterator = _sell_orders.begin();
         sell_order_iterator != _sell_orders.end() && (total_buy_quantity > 0);
         sell_order_iterator++) {
      PRICE sell_price = sell_order_iterator->first;
      std::unique_ptr<Order> &sell_order = sell_order_iterator->second;

      if (buy_price >= sell_price) {
        // exact match or buy quantity less
        if (sell_order->quantity <= total_buy_quantity) {
          this->printTrade(sell_order->order_id, sell_price,
                           sell_order->quantity, order_id, buy_price,
                           sell_order->quantity);
          total_buy_quantity -= sell_order->quantity;

          _sell_orders.erase(sell_order_iterator);
        } else {
          this->printTrade(sell_order->order_id, sell_price, total_buy_quantity,
                           order_id, buy_price, total_buy_quantity);

          // Buy quantity more than sell quantity
          sell_order->quantity -= total_buy_quantity;
          total_buy_quantity = 0;
        }
      }
    }

    // Some or all quantity pending to match for the given price
    if (total_buy_quantity != 0 && order_type != Order::ORDER_TYPE::IOC) {
      _buy_orders.insert(std::pair<PRICE, std::unique_ptr<Order>>(
          buy_price, std::unique_ptr<Order>(
                         new Order(order_type, total_buy_quantity, order_id))));
    }
  }

  void cancelOrder(const ORDER_ID &order_id_to_cancel) {

    // Check buy side
    for (auto buy_order = _buy_orders.begin(); buy_order != _buy_orders.end();
         buy_order++) {
      if ((buy_order->second)->order_id == order_id_to_cancel) {
        _buy_orders.erase(buy_order);
        return;
      }
    }

    // Check sell side
    for (auto sell_order = _sell_orders.begin();
         sell_order != _sell_orders.end(); sell_order++) {
      if ((sell_order->second)->order_id == order_id_to_cancel) {
        _sell_orders.erase(sell_order);
        return;
      }
    }
  }

  void modifyOrder(const ORDER_ID &order_id_to_modify,
                   const Order::ORDER_SIDE order_side, const PRICE &new_price,
                   const QUANTITY &new_quantity)

  {
    // Cancel order so that it will loose its place
    cancelOrder(order_id_to_modify);

    // Create new order because its order of execution should be later than
    // existing orders
    (Order::ORDER_SIDE::BUY == order_side)
        ? matchBuyOrder(Order::ORDER_TYPE::GFD, new_price, new_quantity,
                        order_id_to_modify)
        : matchSellOrder(Order::ORDER_TYPE::GFD, new_price, new_quantity,
                         order_id_to_modify);
  }

  void printOutstandingOrders() {
    // print open orders of SELL side
    std::map<PRICE, QUANTITY> sell_side_open_orders;
    for (auto &sell_order : _sell_orders) {
      sell_side_open_orders[sell_order.first] += (sell_order.second)->quantity;
    }
    std::cout << "SELL:" << std::endl;
    for (auto &sell_order : sell_side_open_orders) {
      std::cout << sell_order.first << " " << sell_order.second << std::endl;
    }

    // print open orders of BUY side
    std::map<PRICE, QUANTITY, std::greater<int>> buy_side_open_orders;
    for (auto &buy_order : _buy_orders) {
      buy_side_open_orders[buy_order.first] += (buy_order.second)->quantity;
    }
    std::cout << "BUY:" << std::endl;
    for (auto &buy_order : buy_side_open_orders) {
      std::cout << buy_order.first << " " << buy_order.second << std::endl;
    }
  }

private:
  std::multimap<PRICE, std::unique_ptr<Order>, std::greater<int>> _buy_orders;
  std::multimap<PRICE, std::unique_ptr<Order>> _sell_orders;
};

int main() {
  std::string input_line;
  OrderMatchingEngine engine;

  while (std::getline(std::cin, input_line) && input_line.size()) {
    engine.process(input_line);
  }

  return 0;
}
