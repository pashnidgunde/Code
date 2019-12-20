#ifndef _functors_h_
#define _functors_h_

namespace pn {
namespace functors {
template <typename T>
struct less {
  bool operator()(const T& lhs, const T& rhs) { return lhs < rhs; }
};

template <typename T>
struct greater {
  bool operator()(const T& lhs, const T& rhs) { return lhs > rhs; }
};

template <typename T>
struct lessEqual {
  bool operator()(const T& lhs, const T& rhs) { return lhs <= rhs; }
};

template <typename T>
struct greaterEqual {
  bool operator()(const T& lhs, const T& rhs) { return lhs >= rhs; }
};

template <typename T = void>
struct equal {
  bool operator()(const T& lhs, const T& rhs) { return lhs == rhs; }
};

}  // namespace functors
}  // namespace pn

#endif