#include<iostream>
#include<vector>
#include<cassert>

class MaxHeap
{
    private:
        std::vector<int> s;
        int index = 0;
        int max_index = 0;
    public:
        MaxHeap(size_t size)
        {
            assert(size > 0);
            s.reserve(size+1);
            max_index = size;
        }
        void insert(int e);
    

};

void MaxHeap::insert(int e)
{
    s[max_index] = e;
}


int main()
{
    MaxHeap h;

    return 0;
}