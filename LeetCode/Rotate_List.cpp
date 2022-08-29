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
    ListNode* rotateRight(ListNode* head, int k) {                    
        ListNode *working = head;
        ListNode *last = head;
        int size = 0;
                //get list size
        //get last element
        while(working != nullptr){
            last = working;
            size++;
            working = working->next;
        }
                if (size == 0)
            return head;
                //do k mod size rotations
        int rotations = k % size;        
                if (rotations == 0)
            return head;
                //create circular list
        last->next = head;
                //unlink
        working = head;
        for(int i = 0; i < size - rotations; i++)
            working = working->next;
        head = working;        
        for(int i = 0; i < size-1; i++)
            working = working->next;
        working->next = nullptr;
                return head;
    }
};