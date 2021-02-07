#include<iostream>
#include<string>

namespace pn
{
    namespace algorithm
    {
        template<typename Iter>
        bool contains(Iter begin1,Iter end1,Iter begin2, Iter end2)
        {
            auto search_iter = begin1;
            auto substring_iter = begin2;
            bool match = false;
            while(search_iter != end1 && substring_iter != end2)
            {
                match = (*substring_iter == *search_iter);
                substring_iter = match ? substring_iter++ : begin2;
                search_iter++;
            }

            return match && (substring_iter == end2);
        }
    }
}


int main()
{
    std::string s = "This is not funny";
    std::string s1 = "not";

    if (pn::algorithm::contains(s.begin(),s.end(),s1.begin(),s1.end()))
    {
        std::cout << "has substring" << std::endl;
    }

    return 0;
}