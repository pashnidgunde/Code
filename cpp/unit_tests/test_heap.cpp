#include "data_structures/heap.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(MaxHeap, testInsert) 
{
    pn::ds::MaxHeap<int> max_heap;
    
    max_heap.insert(29);
    ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(29));

    max_heap.insert(37);
    ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(37, 29));
    
    max_heap.insert(18);
    ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(37, 29, 18));
    
    max_heap.insert(46);
    ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(46, 37, 18, 29));
    
    max_heap.insert(1);
    ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(46, 37, 18, 29, 1));
}

TEST(MaxHeap, testInsertRecursive) 
{
    pn::ds::MaxHeap<int> max_heap;
    
    max_heap.insert_recursive(29);
    ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(29));

    max_heap.insert_recursive(37);
    ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(37, 29));
    
    max_heap.insert_recursive(18);
    ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(37, 29, 18));
    
    max_heap.insert_recursive(46);
    ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(46, 37, 18, 29));
    
    max_heap.insert_recursive(1);
    ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(46, 37, 18, 29, 1));
}




// TEST(MaxHeap, testConstructor) 
// {
//     std::vector<int> random_n{29, 37, 18, 46, 1};
//     pn::ds::MaxHeap<int> max_heap(random_n);
//     //EXPECT_THAT(test1, ::testing::ContainerEq(test2));
//     ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(46, 37, 18, 29, 1));
// }

// TEST(MaxHeap, testSort) 
// {
//     std::vector<int> random_n{29, 37, 18, 46, 1};
//     pn::ds::MaxHeap<int> max_heap(random_n);
//     //EXPECT_THAT(test1, ::testing::ContainerEq(test2));
//     ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(46, 37, 18, 29, 1));
//     max_heap.sort();
//     //EXPECT_THAT(test1, ::testing::ContainerEq(test2));
//     ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(1, 18, 29, 37, 46));
// }

// TEST(MinHeap, testInsert) 
// {
//     pn::ds::MinHeap<int> max_heap;
//     std::vector<int> random_n{29, 37, 18, 46, 1};
//     for (const auto& elem : random_n)
//     {
//         max_heap.insert(elem);
//     }
    
//     ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(1, 18, 29, 46, 37));
// }

TEST(MinHeap, testConstructor) 
{
    // std::vector<int> random_n{29, 37, 18, 46, 1};
    // pn::ds::MinHeap<int> max_heap(random_n);
    // //EXPECT_THAT(test1, ::testing::ContainerEq(test2));
    // //ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(46, 37, 18, 29, 1));
}

// TEST(MinHeap, testSort) 
// {
//     std::vector<int> random_n{29, 37, 18, 46, 1};
//     pn::ds::MaxHeap<int> max_heap(random_n);
//     //EXPECT_THAT(test1, ::testing::ContainerEq(test2));
//     ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(46, 37, 18, 29, 1));
//     max_heap.sort();
//     //EXPECT_THAT(test1, ::testing::ContainerEq(test2));
//     ASSERT_THAT(max_heap.get(), ::testing::ElementsAre(1, 18, 29, 37, 46));
// }

