/*
 * unique_ptr.cpp
 *
 *  Created on: 18-Aug-2016
 *      Author: rupa
 */

/* This is to demo that you can't create vector of unique_pointers
 * This will not compile
 */

#include <memory>
#include <string>
#include <vector>

class X {};

// std::vector<std::unique_ptr<X>> vec = { unique_ptr<X> { new X{} } };

std::vector<std::unique_ptr<std::string>> vs{
    std::unique_ptr<std::string>{new std::string{"Doug"}},
    std::unique_ptr<std::string>{new std::string{"Adams"}}};

int main() {}
