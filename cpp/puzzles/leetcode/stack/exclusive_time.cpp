//https://leetcode.com/problems/exclusive-time-of-functions/
#include <stack>
#include <algorithm>
#include <cassert>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:

    // Algorithm
    // id --> if stack not empty, top of stack else current id
    // s1,s2 --> s1[id] += t(s2)-t(s1);
    // s1,e1 --> s1[id] += t(e1)-t(s1) + 1;
    // e1,s2 --> pr on stack [id] += t(s2)-t(e1)-1
    // e1,e2 --> e2[id] += t(e2) - t(e1)
    
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        std::vector<int> result;
        result.resize(n);

        auto pid = 0;
        auto previous_time = 0;
        char previous_op = 's';
        std::stack<int> previous_ids_stack;
        previous_ids_stack.push(0);

        auto index_of_first_quolon = 0;
        auto current_id = 0;
        auto current_time = 0;
        auto current_op = 's';
        auto previous_id = 0;
        
        for (auto it = logs.begin() + 1; it != logs.end(); ++it)
        {
            auto &log = *it;
            index_of_first_quolon = log.find_first_of(":");
            current_id = atoi(log.substr(0,index_of_first_quolon).c_str());
            current_time = atoi(log.substr(log.find_last_of(":")+1).c_str());
            current_op = log[index_of_first_quolon+1];
            previous_id = !previous_ids_stack.empty() ? previous_ids_stack.top() : current_id;
            
            if (current_op == 's')
            {
                /*
                if (previous_op == 's')
                {
                    result[previous_id] += current_time - previous_time;
                }
                else
                {
                    result[previous_id] += current_time - previous_time - 1;
                }*/

                result[previous_id] += current_time - previous_time;
                if (previous_op != 's') result[previous_id]--;
                previous_ids_stack.push(current_id);
            }
            else
            {
                /*
                if (previous_op == 's')
                {
                    result[previous_id] += current_time - previous_time + 1;
                }
                else
                {
                    result[previous_id] += current_time - previous_time;
                }*/

                result[previous_id] += current_time - previous_time;
                if (previous_op == 's') result[previous_id]++;
                previous_ids_stack.pop();
            }
                        
            previous_time = current_time;
            previous_op = current_op;
        }
        
        return result;
    }
};

int main()
{
    {
        Solution s;
        std::vector<std::string> i{"0:start:0","1:start:2","1:end:5","0:end:6"};
        auto a = s.exclusiveTime(2,i);
        std::vector<int>e {3,4};
        assert(a == e);
    }

    {
        Solution s;
        std::vector<std::string> i{"0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"};
        auto a = s.exclusiveTime(1,i);
        std::vector<int>e {8};
        assert(a == e);
    }

    {
        Solution s;
        std::vector<std::string> i{"0:start:0","0:start:2","0:end:5","1:start:6","1:end:6","0:end:7"};
        auto a = s.exclusiveTime(2,i);
        std::vector<int>e {7,1};
        assert(a == e);
    }

    {
        Solution s;
        std::vector<std::string> i{"0:start:0","0:start:2","0:end:5","1:start:7","1:end:7","0:end:8"};
        auto a = s.exclusiveTime(2,i);
        std::vector<int>e {8,1};
        assert(a == e);
    }

    {
        Solution s;
        std::vector<std::string> i{"0:start:0","0:end:0","1:start:1","1:end:1","2:start:2","2:end:2","2:start:3","2:end:3"};
        auto a = s.exclusiveTime(3,i);
        std::vector<int>e {1,1,2};
        assert(a == e);
    }

    return 0;
}