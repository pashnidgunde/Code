#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

template<typename T, typename Op>
class Heap
{
    public:
        void insert(const T& elem)
        {
            _heap.emplace_back(elem);
            heapify_up(_heap.size()-1);
        }

        const T& top() const
        {
            if (_heap.empty()) { throw "Empty heap" ;}
            return _heap[0];
        }

        void pop()
        {
            if (_heap.empty()) { throw "Empty heap" ;}
            std::swap(_heap[0],_heap[_heap.size()-1]);
            _heap.pop_back();
            heapify_down(0);
        }

    private:
        void heapify_up(int index)
        {
            if (index <= 0) return;
            int parent_index = parent(index);
            if (_op(_heap[index], _heap[parent_index]))
            {
                std::swap(_heap[parent_index], _heap[index]);
                heapify_up(parent_index);
            }
        }

        void heapify_down(int index)
        {
            int swap_index = index;
            int li = left_index(index);
            if (li >= _heap.size()) return;
            if (_op(_heap[li], _heap[index]))
            {
                swap_index = li;
            }

            int ri = right_index(index);
            if (ri < _heap.size() && (_op(_heap[ri], _heap[swap_index])))
            {
                swap_index = ri;
            }

            std::swap(_heap[index], _heap[swap_index]);
            heapify_down(swap_index);
        }

        int parent(int index)
        {
            return (index - 1) / 2;
        }

        int left_index(int index)
        {
            return 2 * index + 1;
        }

        int right_index(int index)
        {
            return 2 * index + 2;
            //return left_index(index) + 1;
        }

    private:
        Op _op;
        std::vector<T> _heap;
};


template <typename T>
class MaxHeap : public Heap<T,std::greater<T>>
{
};

template<typename T>
class MinHeap : public Heap<T, std::less<int>>
{
};

template<typename T, typename Op>
class BoundedHeap
{
    public:
        BoundedHeap(int max_capacity)
        {
            _heap.reserve(max_capacity);
            _max_capacity = max_capacity;
            _filled_and_sorted = false;
        }
            
        void insert(const T& elem)
        {
            if (!_filled_and_sorted)
            {
                _heap.push_back(elem);
                if (_heap.size() == _max_capacity)
                {
                    std::sort(_heap.begin(), _heap.begin() + _max_capacity , _op);
                    _filled_and_sorted = true;
                }
                return;
            }
            if (!_op(_heap[0],elem)) return;
            _heap[0] = elem;
            heapify_down(0);
        }

    private:
        void heapify_down(int index)
        {
            int swap_index = index;
            int li = left_index(index);
            if (li >= _heap.size()) return;
            if (_op(_heap[li], _heap[index]))
            {
                swap_index = li;
            }

            int ri = right_index(index);
            if (ri < _heap.size() && (_op(_heap[ri], _heap[swap_index])))
            {
                swap_index = ri;
            }

            std::swap(_heap[index], _heap[swap_index]);
            heapify_down(swap_index);
        }

        int parent(int index)
        {
            return (index - 1) / 2;
        }

        int left_index(int index)
        {
            return 2 * index + 1;
        }

        int right_index(int index)
        {
            return 2 * index + 2;
            //return left_index(index) + 1;
        }
    private:
        Op _op;
        std::vector<T> _heap;
        int _max_capacity = 0;
        bool _filled_and_sorted = false;
};


int main()
{
    {
        MinHeap<int> h;
        h.insert(-4);
        h.insert(-1);
        h.insert(0);
        h.insert(3);
        h.insert(10);

        assert(h.top() == -4);
        h.pop();
        assert(h.top() == -1);
    }
    
    {
        BoundedHeap<int, std::less<int>> h(5);
        std::vector<int> i{1,2,3,4,5,6,7,8,9,10};
        for (const auto& elem : i)
        {
            h.insert(elem);
        }
    }

    
    return 0;
}