//https://leetcode.com/problems/palindrome-number/
#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;
struct TreeNode {
      int val;
      TreeNode* left;
      TreeNode* right;
      bool visited = false;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
 
class Solution {
public:

    void inOrderTraversal(TreeNode* root, std::vector<int>& r)
    {
        if (!root) return;
        if (root->left) inOrderTraversal(root->left,r);
        r.push_back(root->val);
        if (root ->right) inOrderTraversal(root->right,r);
    }

    vector<int> inorderTraversal(TreeNode* root) {
        if (!root) return std::vector<int>();

        std::vector<int> r;
        inOrderTraversal(root,r);
        return r;
    }

    vector<int> inorderTraversalNonRec(TreeNode* root) {
        if (!root) return std::vector<int>();

        std::stack<TreeNode*> s;
        s.push(root);

        std::vector<int> r;
        while(!s.empty())
        {
            TreeNode* top = s.top();
            if (top->left && !top->left->visited)
            {
                s.push(top->left);
                continue;
            }

            r.push_back(top->val);
            s.pop();
            top->visited = true;

            if (top->right && !top->right->visited)
            {
                s.push(top->right);
            }
        }
        return r;
    }

    vector<int> inorderTraversalNonRec1(TreeNode* root) {
        if (!root) return std::vector<int>();

        std::stack<TreeNode*> s;
        s.push(root);
        std::unordered_set<TreeNode*> visited;

        std::vector<int> r;
        while(!s.empty())
        {
            TreeNode* top = s.top();
            if (top->left && visited.find(top->left) == visited.end())
            {
                s.push(top->left);
                continue;
            }

            r.push_back(top->val);
            s.pop();
            visited.emplace(top);
            
            if (top->right && visited.find(top->right) == visited.end())
            {
                s.push(top->right);
            }
        }
        return r;
    }

    vector<int> inorderTraversalNonRec_most_efficient(TreeNode* root) {
        if (!root) return std::vector<int>();

        std::stack<TreeNode*> s;
        std::vector<int> r;
        auto curr = root;
        while(curr || !s.empty())
        {
            while(curr)
            {
                s.push(curr);
                curr = curr->left;
            }
            auto top = s.top();
            r.push_back(top->val);
            s.pop();
            
            curr = top->right;
        }
        return r;
    }

};
int main()
{
    Solution s;
    TreeNode *root = new TreeNode(1,nullptr, new TreeNode(2, new TreeNode(3), nullptr));
    std::vector<int> r = s.inorderTraversal(root);
    std::vector<int> r1 = s.inorderTraversalNonRec(root);
    std::vector<int> r2 = s.inorderTraversalNonRec1(root);
    std::vector<int> r3 = s.inorderTraversalNonRec_most_efficient(root);
    auto print_v = [](const std::vector<int>& v)
    {
        for (const auto& elem: v)
        {
            std::cout << elem << " ,";
        }
        std::cout << std::endl;
    };
    
    print_v(r);
    print_v(r1);
    print_v(r2);
    print_v(r3);

    return 0;
}