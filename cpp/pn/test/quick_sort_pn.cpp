#include <list>
#include <vector>
//#include <deque>
#include "algorithm.h"
#include "functors.h"
#include "utils.h"

#include <thread>

int main() {
  // Test on std::vector
  std::vector<int> v{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  pn::algo::quickSort(v.begin(), v.end(), pn::functors::less<int>());
  pn::utils::print<std::vector<int>::iterator>(std::begin(v), std::end(v));

  // TODO : Fix Quick sort ASAP
  std::vector<int> v1{1, 0, 0, 0, 0, 1, 2, 0, 0, 0, 1, 0};
  pn::algo::quickSort(v1.begin(), v1.end(), pn::functors::less<int>());
  pn::utils::print<std::vector<int>::iterator>(std::begin(v1), std::end(v1));

  // Test on std::list
  // std::list<int> l{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  // pn::algo::quickSort(l.begin(), l.end(), pn::functors::greater<int>());
  // pn::utils::print<std::list<int>::iterator>(std::begin(l), std::end(l));

  // TODO
  // Generic bubble sort doesn't work on std::queue , Find out why and fix
  // std::deque<int> q1{1,2};
  // std::deque<int> q;
  // for (int i=0;i<10;++i) {
  //    q.emplace_back(i);
  //}
  // pn::algo::quickSort(q.front(),q.back(),pn::functors::less<int>());
  /*
      auto mid = v.size() / 2;
      std::thread t1(pn::algo::quickSort<std::vector<int>::iterator,
          pn::functors::greater<int>>,
          v.begin(),
          v.begin()+mid,
          pn::functors::greater<int>());
      std::thread t2(
          pn::algo::quickSort<
              std::vector<int>::iterator,
              pn::functors::greater<int>
          >,
          v.begin()+mid,
          v.end(),
          pn::functors::greater<int>());
      t1.join();
      t2.join();
      pn::utils::print<std::vector<int>::iterator>
          (std::begin(v),std::end(v));
    */
  return 0;
}
