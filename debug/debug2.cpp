//https://leetcode.com/problems/maximum-width-of-binary-tree/
#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <algorithm>
#include <cmath>

struct TreeNode {
      int val;
      TreeNode* left;
      TreeNode* right;
      bool visited = false;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

using namespace std;
class Solution {
public:
    int heightOfTree(TreeNode *node) 
    {
        if (node != nullptr) 
        {
            int hl = heightOfTree(node->left);
            int hr = heightOfTree(node->right);

            if (hl > hr) 
            {
                return hl + 1;
            } 
            else 
            {
                return hr + 1;
            }
        }
        return 0;
    }

    int widthOfBinaryTree(TreeNode* root) {
        std::vector<TreeNode*> nodes;
        nodes.resize(std::pow(2,heightOfTree(root)) -1, nullptr);
        nodes[0] = root;
        for (int i = 0 ; i < nodes.size(); i++)
        {
            auto node = nodes[i];
            if (node)
            {
                nodes[2*i+1] = node->left;
                nodes[2*i+2] = node->right;
            }
        }
        
        int begin = 1;
        auto end = 0;
        int level = 0;
        int max_max = 1;
        int mid = 0;
        int node_count = 0;
        
        while (begin < nodes.size())
        {
            int max = 0;
            node_count = std::pow(2,level);
            begin = begin + node_count - 1;
            mid = begin + node_count / 2;
            end = begin + node_count - 1;
            
            if (std::any_of(nodes.begin()+begin, nodes.begin()+mid+1, [](TreeNode* node) { return node != nullptr; } ))
            {
               max += node_count / 2; 
            }
            
            if (std::any_of(nodes.begin()+mid, nodes.begin()+end+1, [](TreeNode* node) { return node != nullptr; } ))
            {
               max += node_count / 2; 
            }
            
            max_max = std::max(max_max,max);
        }
        
        return max_max;
    }
};

int main()
{
    Solution s;
    TreeNode *root = new TreeNode(1,new TreeNode(3,new TreeNode(5), new TreeNode(3)),new TreeNode(2, nullptr, new TreeNode(9)));
    s.widthOfBinaryTree(root);
    
    return 0;
}