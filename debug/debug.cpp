// Let's say N number of employees with number of available days for work
// Find two employees which can be available most for a project
// Extend the same problem for 3 or N

#include <vector>
#include <cassert>
#include <iostream>
#include <type_traits>
#include <set>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <bitset>

// ON(N * N)
template<typename Iter>
auto intersection(Iter begin1, Iter end1, Iter begin2, Iter end2)
{
    using Typename = typename std::iterator_traits<Iter>::value_type;
    std::unordered_set<Typename> result;
    auto distance1 = std::distance(begin1,end1);
    auto distance2 = std::distance(begin2,end2);
    auto begin_from = begin1, end_from = end1;
    auto begin_to = begin2, end_to = end2;

    if (distance2 > distance1)
    {
        std::swap(begin_from, begin_to);
        std::swap(end_from, end_to);
    }

    for(;begin_from != end_from;++begin_from)
    {
       if (std::find(begin_to,end_to,*begin_from) != end_to)
       {
           result.emplace(*begin_from);
       }
    }

    return result;
}

template<typename Iter>
auto bitset_intersection_count(Iter begin1, Iter end1, Iter begin2, Iter end2)
{
    using Typename = typename std::iterator_traits<Iter>::value_type;
    std::bitset<31> first;
    std::bitset<31> second;
    while(begin1 != end1)
    {
        first = first | std::bitset<31>(*begin1);
        *begin1++;
    }
    
    while(begin2 != end2)
    {
        second = second | std::bitset<31>(*begin2);
        *begin2++;
    }

    return (first & second).count();
}


struct PairHasher {
  template <typename T1, typename T2>
  size_t operator()(const std::pair<T1, T2> &pair) const {
    return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
  }
};

using EmployeeScheule = std::vector<std::vector<size_t>>; 

auto getIntersectionForAllDays(EmployeeScheule& employeeSchedule)
{   
    std::unordered_map<size_t,std::unordered_set<std::pair<size_t,size_t>,PairHasher>> days_to_intersection_map;
    for (size_t row=0; row<employeeSchedule.size();++row)
    {
        for (size_t row1= row+1; row1 < employeeSchedule.size(); ++ row1)
        {
            auto days = intersection(employeeSchedule[row].begin(),employeeSchedule[row].end(),
                            employeeSchedule[row1].begin(), employeeSchedule[row1].end()).size();

            auto &set = days_to_intersection_map[days];
            set.insert(std::make_pair<int,int>(row,row1));
        }
    }

    return days_to_intersection_map;
}

// N = number of employees
size_t getMaxIntersectionForNDays(EmployeeScheule& employeeSchedule, size_t N)
{   
    auto max_intersection_for_all_days = getIntersectionForAllDays(employeeSchedule);
    return (max_intersection_for_all_days.find(N) == max_intersection_for_all_days.end()) ? 0 : max_intersection_for_all_days[N].size();
}

int main()
{
    EmployeeScheule employeeSchedule {
        {2,3,5,6,8,9},
        {2,3,5},
        {2,3,5,6,8,9}
     };
    std::set<std::set<int>> result;
    
    assert(getMaxIntersectionForNDays(employeeSchedule,3) == 2);
    assert(getMaxIntersectionForNDays(employeeSchedule,2) == 0);
    assert(getMaxIntersectionForNDays(employeeSchedule,6) == 1);

    assert(bitset_intersection_count(employeeSchedule[0].begin(),employeeSchedule[0].end(),employeeSchedule[1].begin(),employeeSchedule[1].end()) == 3);

    return 0;
    
}

