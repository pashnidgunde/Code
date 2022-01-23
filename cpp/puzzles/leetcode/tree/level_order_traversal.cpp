//https://leetcode.com/problems/binary-tree-level-order-traversal/

#include <iostream>
#include <cassert>
#include <list>
#include <vector>
#include <cmath>

using namespace std;
//
 //Definition for a binary tree node.
 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 
class Solution {
public:
    vector<vector<int>> levelOrderNR(TreeNode* root) {
        std::vector<vector<int>> r;
        if (!root) return r;
        
        std::list<TreeNode*> nl;
        nl.emplace_back(root);
        
        auto level = 0;
        while(!nl.empty())
        {
            std::vector<int> v;
            auto c = pow(2,level); 
            while(c > 0) 
            {
                auto n = nl.front();
                nl.pop_front();

                if (n) { 
                    v.push_back(n->val);
                    nl.push_back(n->left);
                    nl.push_back(n->right);
                }

                c--;
            }
            r.push_back(v);
            level++;
        }
        return r;
    }

    void print(std::vector<std::vector<int>> v)
    {
        std::cout << "[";
        for (auto oe : v)
        {
            std::cout << "[";
            for ( auto e : oe)
            {
                std::cout << e << ","        ;
            }
            
            std::cout << "],";
        }
        std::cout << "]" << std::endl;
    }

    void level_order(TreeNode*node, int level, std::vector<vector<int>>& r)
    {
        if (!node) return;

        if (r.size() <= level) { r.push_back({node->val}); }
        else r[level].emplace_back(node->val);
        
        level_order(node->left,level + 1, r);
        level_order(node->right,level + 1, r);
    }

    vector<vector<int>> levelOrder(TreeNode* root) {
        std::vector<vector<int>> r;
        if (!root) return r;
        level_order(root,0,r);
        return r;
    }
};


int main()
{
    {
        //      1
        //    2   2
        //  3  4 4  3
        TreeNode t1(1,new TreeNode(2, new TreeNode(3), new TreeNode(4)), new TreeNode(2, new TreeNode(4), new TreeNode(3)));
        Solution s;
        auto v = s.levelOrderNR(&t1);
        auto v1 = s.levelOrder(&t1);
        s.print(v);
        s.print(v1);
    }

    {
        TreeNode t1(1,new TreeNode(2, new TreeNode(3), new TreeNode(4)), new TreeNode(2, new TreeNode(3), new TreeNode(4)));
        Solution s;
        auto v = s.levelOrderNR(&t1);
        auto v1 = s.levelOrder(&t1);
        s.print(v);
        s.print(v1);
     }

     {
        TreeNode t1(1,new TreeNode(2, new TreeNode(4), nullptr), new TreeNode(3, new TreeNode(5), nullptr));
        Solution s;
        auto v = s.levelOrderNR(&t1);
        auto v1 = s.levelOrder(&t1);
        s.print(v);
        s.print(v1);
     }
}