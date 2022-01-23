#include "data_structures/sll.h"
#include "gtest/gtest.h"

TEST(SingleLinkedList, testInsert) 
{
    pn::ds::Sll<int> sll;
    sll.append(10);
    sll.append(5);
    sll.append(11);

    EXPECT_EQ(sll.size(), 3);
}

    
