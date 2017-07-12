
namespace pn {
namespace functors {
template <typename T> struct less {
  bool operator()(const T &lhs, const T &rhs) { return lhs < rhs; }
};

template <typename T> struct greater {
  bool operator()(const T &lhs, const T &rhs) { return lhs > rhs; }
};

template <typename T> struct less_equal {
  bool operator(const T &lhs, const T &rhs) { return lhs <= rhs; }
};

template <typename T> struct greater_equal {
  bool operator(const T &lhs, const T &rhs) { return lhs >= rhs; }
};
}
}
