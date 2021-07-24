//https://leetcode.com/problems/same-tree/
// Find if two trees are same

#include <iostream>
#include <cassert>

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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if ( !p && !q ) return true;
        if ( (p && !q) || (q && !p) || p->val != q->val ) return false;
        return isSameTree(p->left,q->left) && isSameTree(p->right,q->right);
    }
};


int main()
{
    {
        TreeNode t1(1,new TreeNode(2), new TreeNode(3));
        TreeNode t2(1,new TreeNode(2), new TreeNode(3));
        Solution s;
        assert(s.isSameTree(&t1,&t2));
    }

    {
        TreeNode t1(1,new TreeNode(2), new TreeNode(3));
        TreeNode t2(1,new TreeNode(3), new TreeNode(3));
        Solution s;
        assert(s.isSameTree(&t1,&t2) == false);
    }
}