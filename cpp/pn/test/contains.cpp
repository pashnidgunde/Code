#include "../include/contains.h"
#include<iostream>
#include<string>
#include <cassert>

int main()
{
    std::string s = "This is not funny";
    std::string s1 = "not";
    std::string s2 = "really";
    std::string s3 = "This";
    assert(pn::algorithm::contains(s.begin(),s.end(),s1.begin(),s1.end()).first);
    assert(pn::algorithm::contains(s.begin(),s.end(),s1.begin(),s1.end()).second == 8);
    assert(!pn::algorithm::contains(s.begin(),s.end(),s2.begin(),s2.end()).first);
    assert(pn::algorithm::contains(s.begin(),s.end(),s3.begin(),s3.end()).first);
    assert(pn::algorithm::contains(s.begin(),s.end(),s3.begin(),s3.end()).second == 0);
}