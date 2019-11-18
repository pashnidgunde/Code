#ifndef _functors_h_
#define _functors_h_

namespace pn {
namespace functors {
template <typename T> struct less {
  bool operator()(const T &lhs, const T &rhs) { return lhs < rhs; }
};

template <typename T> struct less<T *> {
  bool operator()(const T *a, const T *b) { return *a < *b; }
}

template <typename T>
struct greater {
  bool operator()(const T &lhs, const T &rhs) { return lhs > rhs; }
};

template <typename T> struct greater<T *> {
  bool operator()(const T *a, const T *b) { return *a > *b; }
}

template <typename T>
struct lessEqual {
  bool operator()(const T &lhs, const T &rhs) { return lhs <= rhs; }
};

template <typename T> struct lessEqual<T *> {
  bool operator()(const T *a, const T *b) { return *a <= *b; }
}

template <typename T>
struct greaterEqual {
  bool operator()(const T &lhs, const T &rhs) { return lhs >= rhs; }
};

template <typename T> struct greaterEqual<T *> {
  bool operator()(const T *a, const T *b) { return *a >= *b; }
}

template <typename T>
struct equal {
  bool operator()(const T &lhs, const T &rhs) { return lhs == rhs; }
};

template <typename T> struct equal<T *> {
  bool operator()(const T *a, const T *b) { return *a == *b; }
}
}
}

#endif