#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;





int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    auto no_of_plants = 0; 
    std::cin >> no_of_plants;
    std::vector<int> v(no_of_plants);
    for (auto i =0; i<no_of_plants;i++)
        {
            std::cin >> v[i];
    }
    
    std::set<int> dead_plants;
    
    bool deaths = true;
    int days = 0;
    while (deaths)
        {
        deaths = false;
        for (int i=0;i<=(v.size()-2);i++)
            {
            int j=i+1;
            if (v[j] > v[i])
                {
                dead_plants.insert(v[j]);
                deaths = true;
            }
        }
        
        if (deaths)
            {
            for (const auto& plant : dead_plants)
                {
                auto iter = std::find(v.begin(),v.end(),plant);
                v.erase(iter);
            }
            dead_plants.clear();
            days++;
        }
        
        
        
    }
    
    
    std::cout << days;
    
    return 0;
}
