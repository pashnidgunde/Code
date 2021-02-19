#include "data_structures/bst.h"
#include "gtest/gtest.h"

TEST(BST, testInsert) 
{
    pn::ds::Bst<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(11);

    EXPECT_EQ(bst.size(), 3);
}

    
