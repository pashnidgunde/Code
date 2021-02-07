#include <cassert>
#include <iostream>
#include "data_structures/bst.h"

int main()
{
    pn::ds::Bst<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(11);
    return 0;
}