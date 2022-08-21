#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <list>

auto adj_matrix(std::vector<int>& data, std::vector<std::pair<int,int>>& edges)
{
    std::vector<std::vector<int>> am(data.size(), std::vector<int>(data.size(), 0));
    
    for (const auto& edge : edges)
    {
        am[edge.first-1][edge.second-1] = 1;
        am[edge.second-1][edge.first-1] = 1;
    }
    return am;
}

void print_am(std::vector<std::vector<int>>& am)
{
    for (int i =0; i < am.size(); i++)
    {
        for  (int j = 0; j < am[i].size(); j++)
        {
            std::cout << am[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

auto adj_list(std::vector<int>& data, std::vector<std::pair<int,int>>& edges)
{
    std::vector<std::list<int>> al;
    al.resize(data.size() + 1);
    
    for (const auto& edge : edges)
    {
        al[edge.first].push_back({edge.second});
    }
    return al;
}

void print_al(std::vector<std::list<int>>& al)
{
    for (int i =0; i < al.size(); i++)
    {
        std::cout << "[" << i << "] - > " ; 
        for  (const auto elem : al[i])
        {
            std::cout << elem << ", ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::vector<int> data = {1,2,3,4,5,6};
    std::vector<std::pair<int,int>> edges {{1,2},{1,3},{2,6},{3,4},{3,5}};
    //auto am = adj_matrix(data,edges);
    //print_am(am);
    auto al = adj_list(data,edges);
    print_al(al);
    
    std::stack<int> s;
    s.push(data[0]);
    std::vector<int> sum(data.size() + 1,0);
    std::vector<bool> v(data.size() + 1,false);
    
    bool done=true;

    while(!s.empty())
    {
        auto curr = s.top();
        done = true;
        for (auto elem : al[curr])
        {
            if (!v[elem])
            {
                s.push(elem);
                done = false;
                v[elem] = true;
                break;
            }
        }

        if (done)
        {
            int total = curr;
            for(auto elem : al[curr])
            {
                total += sum[elem];
            }
            sum[curr] = total;
            s.pop();
        }
    }

    
    for (size_t i = 0; i< sum.size(); i++)
    {
          std::cout << i << " -> " << sum[i] << " , ";
          
    }

    int running_min = INT_MAX;
    for (auto& edge : edges)
    {
        running_min = std::min(std::min(abs(sum[edge.first] - sum[edge.second]), sum[edge.second]), running_min);
    }

    std::cout << running_min << std::endl;
}

