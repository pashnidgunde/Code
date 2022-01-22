//https://leetcode.com/problems/add-two-numbers/

#include <iostream>
#include <cassert>
#include <string>
#include <sstream>

using namespace std;

// linked list
// fake node

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
    // ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    //     if (!list1) return list2;
    //     if (!list2) return list1;
        
    //     ListNode* head = nullptr;
    //     ListNode* prev = nullptr;
    //     ListNode* result = nullptr;
    //     while(list1 != nullptr && list2 != nullptr)
    //     {
    //         if (list1->val < list2->val)
    //         {
    //             prev = list1;
    //             list1 = list1->next;
    //         }
    //         else
    //         {
    //             prev = list2;
    //             list2 = list2->next;
    //         }

    //         if (!head) 
    //         {
    //             head = prev;
    //             result = head;
    //         }
    //         else
    //         {
    //             head->next = prev;
    //             head = head->next;
    //         }
    //     }

    //     head->next = (list1 == nullptr) ? list2 : list1;
                        
    //     return result;
    // }

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // Create a fake node to avoid duplicate code. Smart !!!
        ListNode fake(-1);
        ListNode* head = &fake;
        while(list1 && list2)
        {
            if (list1->val < list2->val)
            {
                head->next = list1;
                head = list1;
                list1 = list1->next;
            }
            else
            {
                head->next = list2;
                head = list2;
                list2 = list2->next;
            }
        }

        head->next = (list1 == nullptr) ? list2 : list1;
                        
        return fake.next;
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
        ListNode t1(1,new ListNode(2, new ListNode(4)));
        ListNode t2(1,new ListNode(3, new ListNode(4)));
        Solution s;
        ListNode *t3 = s.mergeTwoLists(&t1,&t2);
        assert(s.toString(t3) == "112344");
    }

    {
        ListNode t1;
        ListNode t2;
        Solution s;
        ListNode *t3 = s.mergeTwoLists(&t1,&t2);
        assert(s.toString(t3) == "00");
    }

    {
        ListNode t1;
        ListNode t2{1};
        Solution s;
        ListNode *t3 = s.mergeTwoLists(&t1,&t2);
        assert(s.toString(t3) == "01");
    }

    {
        ListNode* t1 = nullptr;
        ListNode* t2 = nullptr;
        Solution s;
        ListNode *t3 = s.mergeTwoLists(t1,t2);
        assert(s.toString(t3) == "");
    }
}