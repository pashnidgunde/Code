//https://leetcode.com/problems/add-two-numbers/

#include <iostream>
#include <cassert>
#include <string>
#include <sstream>

using namespace std;


/**
 * Definition for singly-linked list. */
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
class Solution {
public:
// 243 + 564
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = nullptr;
        ListNode* head_to_return =  nullptr;
        auto carry = 0;
        auto sum = 0;
        while(l1 || l2)
        {
            sum  = (l1 ? l1->val : 0)  +
                (l2  ? l2->val : 0)  + carry;
            
            carry = (sum >= 10) ? 1 : 0;
            sum = (sum >=10) ? sum - 10  : sum;

            if (l1)
                l1 = l1->next;
            
            if (l2)
                l2 = l2->next;
            
            if (!head) 
            {
                head = new ListNode(sum);
                head_to_return = head;
                continue;
            }
            
            head->next =  new ListNode(sum) ;
            head = head->next;
        }
        
        if (carry == 1) 
            head->next = new ListNode(1);
        
        
        return head_to_return;
    }

    std::string toString(ListNode* node)
    {
        if (!node) return "";

        std::stringstream ss;
        while (node != nullptr)
        {
            ss << node->val;
            node = node-> next;
        }

        auto s = ss.str();
        std::cout << "output string : " << s << std::endl;
        return s;
    }
};

int main()
{
    {
        ListNode t1(2,new ListNode(4, new ListNode(3)));
        ListNode t2(5,new ListNode(6, new ListNode(4)));
        Solution s;
        ListNode *t3 = s.addTwoNumbers(&t1,&t2);
        assert(s.toString(t3) == "708");
    }

    {
        ListNode t1(9,new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9,new ListNode(9, new ListNode(9)))))));
        ListNode t2(9,new ListNode(9, new ListNode(9, new ListNode(9))));
        Solution s;
        ListNode *t3 = s.addTwoNumbers(&t1,&t2);
        assert(s.toString(t3) == "89990001");
    }
}