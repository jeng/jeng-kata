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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode *working = head;
        ListNode *prev = nullptr;
        while(working != nullptr){
            if (working->val == val){
                if (prev == nullptr){
                    head = working->next;
                    working = working->next;
                } else {
                    prev->next = working->next;
                    working = working->next;
                }
            } else {
                prev = working;
                working = working->next;
            }
        }
        return head;
    }
};