/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        //kinda stupid.  If you were given the previous node, or a doubly linked list
            , this would be O(1) instead of O(n)
        ListNode *working = node;
        ListNode *next = working->next;    
        while(next != nullptr){
            working->val = next->val;            
            next = next->next;
            if (next == nullptr)
                working->next = nullptr;
            else
                working = working->next;
        }    
    }
};