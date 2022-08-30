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
    ListNode* mergeNodes(ListNode* head) {
        ListNode *workingNode = nullptr;
        ListNode *returnList = nullptr;
        int result = 0;
        while(head != nullptr){
            if (head->val == 0 && result != 0){
                ListNode *n = new ListNode(result);
                if (workingNode == nullptr){
                    workingNode = n;
                    returnList = workingNode;
                } else {
                    workingNode->next = n;
                    workingNode = n;
                }
                result = 0;
            } else {
                result+= head->val;
            }
            head = head->next;
        }
        return returnList;
    }
};
