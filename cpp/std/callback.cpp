#include <functional>
#include <iostream>
#include <limits>
#include <memory>

struct MarketData {
  int request_id = 0;
  double bid = std::numeric_limits<double>::quiet_NaN();
  double ask = std::numeric_limits<double>::quiet_NaN();
  double mid = std::numeric_limits<double>::quiet_NaN();
};

using CallbackFunction = std::function<void(const MarketData &market_data)>;

template <typename T> class TestConnection {
public:
  TestConnection(T *requestor) : m_requestor(requestor) {}
  void getMesomething(CallbackFunction func) {
    m_requestor->getMesomething(func);
  }

private:
  T *m_requestor;
};

template <typename T> struct MarketDataProvider {
  void getLatestSnapshot(int request_id, T *requestor) {
    MarketData data;
    data.request_id = request_id;
    data.bid = std::rand() % request_id;
    data.ask = std::rand() % request_id;
    data.mid = std::rand() % request_id;
    requestor->onMessage(data);
  }
};

class MarketDataRequester {
public:
  MarketDataRequester() {}
  void getMesomething(CallbackFunction func) {
    static int x = 0;
    m_request_2_callback_map[++x] = func;
    m_provider.getLatestSnapshot(x, this);
  }

  void onMessage(const MarketData &market_data) {
    m_request_2_callback_map[market_data.request_id](market_data);
    m_request_2_callback_map.erase(market_data.request_id);
  }

private:
  MarketDataProvider<MarketDataRequester> m_provider;
  std::unordered_map<int, CallbackFunction> m_request_2_callback_map;
};

struct CallbackHandler {
  void onMarketData(const MarketData &data) {
    std::cout << "received market data"
              << " mid : " << data.mid << ", bid : " << data.bid
              << ", ask : " << data.ask << std::endl;
  }
};

int main() {
  auto market_data_requestor = std::make_unique<MarketDataRequester>();
  auto test_connection =
      TestConnection<MarketDataRequester>(market_data_requestor.get());

  CallbackHandler call_back_handler;

  test_connection.getMesomething([&](const MarketData &market_data) {
    call_back_handler.onMarketData(market_data);
  });

  return 0;
}