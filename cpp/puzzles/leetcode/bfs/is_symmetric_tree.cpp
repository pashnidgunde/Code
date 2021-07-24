// https://leetcode.com/problems/symmetric-tree/
#include <iostream>
#include <cassert>
#include <list>

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
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return isSymmetric(root->left,root->right);
    }
    
    bool isSymmetric(TreeNode* l, TreeNode* r)
    {
        if (!l && !r) return true;
        if ((l && !r) || (!l && r) || (l->val != r->val)) return false;
        return isSymmetric(l->left, r->right) && isSymmetric(l->right, r->left);
    }
    

    // Non recursive, using queue
    // remember the front and pop go together to retrive a element.
    bool isSymmetricNR(TreeNode* root) {
        std::list<TreeNode*> arr;
        if (!root) return true;
        
        arr.push_back(root->left);
        arr.push_back(root->right);

        while(!arr.empty())
        {
            auto l = arr.front();
            arr.pop_front();

            auto r = arr.front();
            arr.pop_front();

            if (!l && !r) continue;
            if ((l && !r) || (!l && r) || (l->val != r->val)) return false;

            arr.push_back(l->left);
            arr.push_back(r->right);
            arr.push_back(l->right);
            arr.push_back(r->left);
        }

        return true;

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
        assert(s.isSymmetric(&t1));
        assert(s.isSymmetricNR(&t1));
    }

    {
        TreeNode t1(1,new TreeNode(2, new TreeNode(3), new TreeNode(4)), new TreeNode(2, new TreeNode(3), new TreeNode(4)));
        Solution s;
        assert(s.isSymmetric(&t1) == false);
        assert(s.isSymmetricNR(&t1) == false);
    }
}