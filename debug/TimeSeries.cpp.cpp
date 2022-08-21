#include <unordered_map>
#include <algorithm>
#include <time.h>
#include <vector>
#include <assert.h>
#include <cmath>
#include <math.h>

class TimeSeries
{
    public:
    TimeSeries(size_t window) : m_window(window)
    {
    }

    double getValue(time_t t)
    {
        if (last - t > m_window) return NAN;

        if (m.find(t) != m.end()) return m[t];
        
        auto begin = v.begin() + search_start_index;
        auto it = std::lower_bound(begin, v.end(), t);
        if (it == begin) return 0;
        it--;
        return *it;
    }

    void insert(time_t t, double val)
    {
        m[t] = val;
        v.push_back(t);
        while(t - v[search_start_index] > m_window) search_start_index++;
        last = t;
    }

    private:
        std::unordered_map<time_t, double> m;
        std::vector<time_t> v;
        time_t last = 0;
        size_t m_window = 0;
        size_t search_start_index = 0;

};

void test1()
{
    TimeSeries t(5000);
    t.insert(10, 10);
    t.insert(11, 11);
    t.insert(14, 14);
    t.insert(15, 15);
    
    assert(t.getValue(0) == 0);
    assert(t.getValue(1) == 0);
    assert(t.getValue(9) == 0);
    assert(t.getValue(10) == 10);
    assert(t.getValue(11) == 11);
    assert(t.getValue(12) == 11);
    assert(t.getValue(13) == 11);
    assert(t.getValue(14) == 14);
    assert(t.getValue(15) == 15);

    t.insert(5000, 5000);
    assert(t.getValue(0) == 0);
    assert(t.getValue(1) == 0);
    assert(t.getValue(9) == 0);
    assert(t.getValue(10) == 10);
    assert(t.getValue(11) == 11);
    assert(t.getValue(12) == 11);
    assert(t.getValue(13) == 11);
    assert(t.getValue(14) == 14);
    assert(t.getValue(15) == 15);
    assert(t.getValue(100) == 15);
    assert(t.getValue(5000) == 5000);

    t.insert(5010, 5010);
    assert((isnan(t.getValue(0))));
    assert((isnan(t.getValue(1))));
    assert((isnan(t.getValue(9))));
    assert(t.getValue(10) == 10);
    assert(t.getValue(15) == 15);
    assert(t.getValue(100) == 15);
    assert(t.getValue(5009) == 5000);

    t.insert(99000, 99000);
    assert((isnan(t.getValue(0))));
    assert((isnan(t.getValue(1000))));
    assert((isnan(t.getValue(9000))));
    assert((isnan(t.getValue(90000))));
    assert((isnan(t.getValue(93999))));
    assert(t.getValue(94000) == 0);
    t.insert(100000, 100000);
    assert((isnan(t.getValue(94000))));
    assert(t.getValue(95000) == 0);
    assert(t.getValue(96000) == 0);
    assert(t.getValue(97000) == 0);
    assert(t.getValue(98000) == 0);
    assert(t.getValue(99000) == 99000);
    assert(t.getValue(99999) == 99000);

}

int main()
{
    test1();
    
    return 0;
}