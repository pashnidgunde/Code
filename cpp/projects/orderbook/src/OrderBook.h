#pragma once

class OrderBook {
  std::map<int, int> bids, asks;

public:
  bool is_empty() const { return bids.empty() && asks.emtpy(); }
};