//https://leetcode.com/problems/palindrome-number/
#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
struct TreeNode {
      int val;
      TreeNode* left;
      TreeNode* right;
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
        if (!root) return;

        std::vector<int> r;
        inOrderTraversal(root,r);
        return r;
    }
};
int main()
{
    Solution s;
    TreeNode *root = new TreeNode(1,nullptr, new TreeNode(2, new TreeNode(3), nullptr));
    std::vector<int> r = s.inorderTraversal(root);
    return 0;
}