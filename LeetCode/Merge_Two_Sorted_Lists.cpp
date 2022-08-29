/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void assign(ListNode **head, ListNode **lst, ListNode **result){
        if (*head == nullptr){
            *result = new ListNode((*lst)->val);
            *head = *result;
            (*lst) = (*lst)->next;
        } else {
            (*result)->next = new ListNode((*lst)->val);
            (*lst) = (*lst)->next;
            *result = (*result)->next;
        }
    }
        ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *result = nullptr;
        ListNode *head = result;        
        while(list1 != nullptr || list2 != nullptr){            
            if (list1 == nullptr){
                assign(&head, &list2, &result);
            } else if (list2 == nullptr){
                assign(&head, &list1, &result);
            } else if (list1->val < list2->val){
                assign(&head, &list1, &result);
            } else {
                assign(&head, &list2, &result);
            }
        }
        return head;
    }
};