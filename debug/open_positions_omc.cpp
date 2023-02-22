#include <cstdint>
#include <random>
#include <vector>
#include <map>

using namespace std;

// Please disable before submitting.
constexpr bool kDebug = true;

struct order {
  uint64_t order_token;
  uint64_t shares;
  double price;
  bool side; // false = sell, true = buy
  uint64_t created_at;
  uint64_t cancelled_or_executed_at;
};

struct query {
  uint64_t query_time;
};

std::vector<uint64_t> your_solution(const vector<order> &orders,
                                    const vector<query> &queries) {
  std::map<uint64_t,std::vector<std::pair<uint64_t,uint64_t>>> order_map; 
  for (const auto& order : orders)
  {
    order_map[order.created_at].push_back({order.shares, order.cancelled_or_executed_at});
  }

  std::vector<uint64_t> result;
  auto open_shares = 0;
  for (const auto& query : queries)
  {
    open_shares = 0;
    for (const auto& order : order_map)
    {
      if (order.first > query.query_time)
      {
        result.emplace_back(open_shares);
        break;
      }
      auto & v = order.second;
      for (const auto & e : v)
      {
        if (e.second > query.query_time)
        {
          open_shares+= e.first;
        }
      }
    }
  }

  return result;
}

///////////////////////////////////////////////////////////////////////////////
// Please do not change any code below.                                      //
///////////////////////////////////////////////////////////////////////////////

std::pair<vector<order>, vector<query>> gen_input(int seed) {
  mt19937 gen(seed);

  const uint64_t order_len = 1 << (gen() % 20);
  const uint64_t time_len = 1 << (gen() % 20);

  vector<order> orders;
  for (uint64_t i = 0; i < order_len; ++i) {
    const double duration = std::max(1.0, time_len / std::log2(time_len));
    const uint64_t start = gen() % time_len;
    const uint64_t end = std::min<int>(start + duration, time_len);
    order o{
        .order_token = i,
        .shares = static_cast<uint64_t>(gen() % 10000),
        .price = static_cast<double>(gen() % 1000) / 10,
        .side = gen() % 2 ? false : true,
        .created_at = start,
        .cancelled_or_executed_at = end,
    };
    orders.emplace_back(o);
  }

  vector<query> queries;
  for (uint64_t i = 0; i < order_len; ++i) {
    query q{
        .query_time = static_cast<uint64_t>(gen() % time_len),
    };
    queries.emplace_back(q);
  }

  return {std::move(orders), std::move(queries)};
}

int hash_result(const std::vector<uint64_t> &answers) {
  std::hash<uint64_t> hasher;
  uint64_t result = 0;
  for (auto &a : answers) {
    result = hasher(a) ^ (result << 1);
  }
  return result;
}

// This test harness generates an input to and hashes the output from your
// solution. Please do not change any code below this line.
int solution(int seed) {
  auto input = gen_input(seed);
  bool debug = kDebug && input.first.size() < 100 && input.second.size() < 100;
  if (debug) {
    for (auto &o : input.first) {
      std::cerr << "O," << o.order_token << "," << o.price << "," << o.shares
                << "," << (o.side ? 'B' : 'S') << "," << o.created_at << ","
                << o.cancelled_or_executed_at << "\n";
    }
    for (auto &q : input.second) {
      std::cerr << 'Q' << "," << q.query_time << "\n";
    }
  }

  const auto answers = your_solution(input.first, input.second);

  if (debug) {
    for (auto &a : answers) {
      std::cerr << "R," << a << "\n";
    }
  }

  return hash_result(answers);
}

// Example test:   459
// Output (stderr):
// O,0,28.7,4041,S,0,4
// O,1,34.5,569,S,6,10
// O,2,17.1,6719,S,6,10
// O,3,24,2002,S,2,6
// Q,2
// Q,13
// Q,14
// Q,9
// R,6043
// WRONG ANSWER (got 6043 expected 41120)