#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

// https : // en.cppreference.com/w/cpp/utility/exchange
// exchange exchanges old value with new value and return the old value
// possible implementation from standard
template <class T, class U = T> T exchange(T &obj, U &&new_value) {
  T old_value = std::move(obj);
  obj = std::forward<U>(new_value);
  return old_value;
}

namespace pn {

enum class MachineState {
  STARTING = 0,
  STARTED,
  MOVING,
  STOPPED,
};

std::ostream &operator<<(std::ostream &ostream, const MachineState &state) {
  // TO DO : to use enum to str conversion theory
  ostream << static_cast<int>(state);
  return ostream;
}

class StateMachine {
  MachineState _status = MachineState::STARTING;

public:
  void setStatus(const MachineState &status) { _status = status; }
  MachineState exchangeStatus(const MachineState &new_status) {
    return std::exchange(_status, new_status);
  }
  MachineState getState() { return _status; }
};
} // namespace pn

void func_hello() { std::cout << "Hello" << std::endl; }

class MoveDemo {
public:
  MoveDemo() = default;
  MoveDemo(int *ptr, double d) : _ptr(ptr), _d(d) {}

  // Move constructor
  MoveDemo(MoveDemo &&other)
      : _ptr(std::exchange(other._ptr, nullptr)),
        _d(std::exchange(other._d, std::numeric_limits<double>::quiet_NaN())) {}

  // Move asignment operator
  MoveDemo &operator=(MoveDemo &&other) {
    if (this != &other) {
      // move ptr, while leaving nullptr in other.p
      _ptr = std::exchange(other._ptr, nullptr);
      // move d, while leaving zero  in other.n
      _d = std::exchange(other._d, std::numeric_limits<double>::quiet_NaN());
    }
    return *this;
  }

  int *get_ptr() { return _ptr; }
  double get_d() { return _d; }

private:
  int *_ptr = nullptr;
  double _d = std::numeric_limits<double>::quiet_NaN();
};

int main() {
  // exchange simple example
  pn::StateMachine machine;
  machine.setStatus(pn::MachineState::STARTED);
  std::cout << "Order status : " << machine.getState() << std::endl;
  auto new_status = pn::MachineState::MOVING;
  auto old_status = machine.exchangeStatus(new_status);
  std::cout << "Old status : " << old_status << ", new status : " << new_status
            << std::endl;

  // Since the second template parameter has a default value, it is possible
  // to use a braced-init-list as second argument. The expression below
  // is equivalent to std::exchange(v, std::vector<int>{1,2,3,4});
  std::vector<int> v;
  std::exchange(v, {1, 2, 3, 4});
  std::copy(begin(v), end(v), std::ostream_iterator<int>(std::cout, ", "));

  std::cout << "\n\n";

  // the default value of template parameter also makes possible to use a
  // normal function as second argument. The expression below is equivalent to
  // std::exchange(fun, static_cast<void(*)()>(f))
  void (*fun)();
  std::exchange(fun, func_hello);
  fun();

  // use of std::exchange for move assignement and move constructors
  MoveDemo x(MoveDemo(new int(10), 5.0));
  std::cout << ((x.get_ptr() != nullptr) ? *(x.get_ptr()) : 0) << std::endl;
  std::cout << x.get_d() << std::endl;

  MoveDemo x1;
  MoveDemo x2 = std::move(x1);
  std::cout << ((x2.get_ptr() != nullptr) ? std::to_string(*(x2.get_ptr()))
                                          : "nullptr")
            << std::endl;

  return 0;
}
