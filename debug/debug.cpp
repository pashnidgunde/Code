#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <string.h>

struct JobNode
{
    int id = 0;
    int runtime = 0;
    int next_id = 0;
    JobNode(int i, int r, int nid) : 
        id(i), runtime(r), next_id(nid)
        {}
        
};

class JobRunner
{
    private:
        std::vector<std::shared_ptr<JobNode>> job_nodes;
        std::map<int,std::vector<int>,std::greater<int>> ordered_job_chain;
        
    public:
        void addJobNode(const std::shared_ptr<JobNode>& node)
        {
            job_nodes.push_back(node);
        }
        
        void generate_job_chain()
        {
            std::vector<bool> in_chain(job_nodes.size(),false);

            int sum = 0;
            std::vector<int> chain;
            for (size_t i=0; i<job_nodes.size(); i++)
            {
                // node already in chain ?
                if (in_chain[i]) continue;
                
                in_chain[i] = true;
                
                // add node to chain
                const auto& node = job_nodes[i];
                sum += node->runtime;
                chain.push_back(node->id);
                
                // end of chain
                if (node->next_id == 0)
                {
                    ordered_job_chain[sum] = chain;
                    chain.clear();
                    sum = 0;
                }
            }
        }
        void print_job_chain()
        {
            std::cout << "Runtime  "  << "  Chain" << std::endl;
            for (const auto& e : ordered_job_chain)
            {
                std::cout << e.first << "     : " ;
                for (const auto& ve : e.second)
                {
                    std::cout << ve << " -> ";
                }
                
                std::cout << " END " << std::endl;
            }
        }

        void print_size()
        {
            std::cout << job_nodes.size();
        }
};

using namespace std;
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    std::string line;
    bool skipped_header = false;
    JobRunner jr;
   
    // Read all jobs except header 
    while(std::getline(std::cin,line))
    {
        if (!skipped_header) 
        {
            skipped_header = true;
            continue;
        }
        
        std::vector<std::string> tokens;
        stringstream check1(line);
        string intermediate;
        while(getline(check1, intermediate, ','))
        {
            tokens.push_back(intermediate);
        }
        
        auto job_node = std::make_shared<JobNode>
                            (std::atoi(tokens[0].c_str()),
                             std::atoi(tokens[1].c_str()),
                             std::atoi(tokens[2].c_str()));
        jr.addJobNode(job_node);
    }
    
    // Generate Job chain by runtime
    jr.generate_job_chain();
    jr.print_size();
    
    // print
    jr.print_job_chain();
    return 0;
}