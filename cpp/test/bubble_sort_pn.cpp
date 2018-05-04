#include <vector>
#include <list>
//#include <deque>
#include "algo/sort/bubble_sort.h"
#include "functors.h"
#include "utils.h"

int main()
{
    // Test on std::vector	
    std::vector<int> v { 10,9,8,7,6,5,4,3,2,1};
    pn::algo::bubbleSort(v.begin(),v.end(),pn::functors::less<int>());
    pn::utils::print<std::vector<int>::iterator> 
        (std::begin(v),std::end(v));
   
    // Test on std::list
    std::list<int> l{1,2,3,4,5,6,7,8,9,10};
    pn::algo::bubbleSort(l.begin(),l.end(),pn::functors::greater<int>());
    pn::utils::print<std::list<int>::iterator> 
        (std::begin(l),std::end(l));

    // TODO
    // Generic bubble sort doesn't work on std::queue , Find out why and fix 
    //std::deque<int> q1{1,2};
    //std::deque<int> q;
    //for (int i=0;i<10;++i) {
    //    q.emplace_back(i);
    //}
    //pn::algo::bubbleSort(q.front(),q.back(),pn::functors::less<int>());

    return 0;
}
