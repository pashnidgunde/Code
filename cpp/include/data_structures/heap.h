#ifndef PN_DATA_STRUCTURE_HEAP_HPP
#define PN_DATA_STRUCTURE_HEAP_HPP

#include <ostream>
#include <vector>
#include <iostream>

namespace pn
{
    namespace ds
    {
        template<typename T, typename Comp>
        class heap
        {
            std::vector<T> _heap;
            Comp _comp;
            int index = 0;
            public:
                heap() = default;
                void insert(int elem)
                {
                    _heap.push_back(elem);
                    _heapify_element_at_index(_heap.size()-1);
                    //print(std::cout);
                }

                // insert implementation with recursion
                void insert_recursive(int elem)
                {
                    _heap.push_back(elem);
                    _heapify_element_at_index_recusrsive(_heap.size()-1);
                }

                void print(std::ostream& os)
                {
                    for (const auto& elem : _heap)
                    {
                        os << elem << " " ;
                    }
                    os << std::endl;
                }

                // heap(const std::vector<T>& elements) : _heap(elements)
                // {
                //     _heapify();
                // }

                // void sort()
                // {
                //     for (size_t i = _heap.size()-1; i>0; --i)
                //     {
                //         _heapify_element_at_index(i);
                //         std::swap(_heap[0],_heap[i]);
                //         //print(std::cout);
                //     }
                // }

                const std::vector<int>& get() const { return _heap; }

            private:
                void _heapify_element_at_index(size_t index)
                {
                    while (index > 0)
                    {
                        auto parent_index = (index-1) / 2;
                        //if (_heap[parent_index] < _heap[index]) // max heap
                        //if (_heap[parent_index] > _heap[index]) // min heap
                        if (_comp(_heap[index],_heap[parent_index])){
                            std::swap(_heap[parent_index],_heap[index]);
                            index = parent_index;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                // recursive implementation of heapify at index
                void _heapify_element_at_index_recusrsive(size_t index)
                {
                    if (index == 0) return;
                    auto parent_index = (index - 1) / 2;
                    //if (_heap[parent_index] < _heap[index]) // max heap
                    //if (_heap[parent_index] > _heap[index]) // min heap
                    if (_comp(_heap[index],_heap[parent_index]))
                    {
                        std::swap(_heap[parent_index],_heap[index]);
                        _heapify_element_at_index_recusrsive(parent_index);
                    }
                }

                // void _heapify()
                // {
                //     for (size_t i = _heap.size()-1; i>0; --i)
                //     {
                //         _heapify_element_at_index(i);
                //         print(std::cout);
                //     }
                // }
        };

        template<typename T>
        using MaxHeap = struct heap<T,std::greater<int>>;

        template<typename T>
        using MinHeap = struct heap<T,std::less<int>>;
    }
}

#endif