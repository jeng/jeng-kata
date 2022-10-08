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
    int getTwinIndex(int idx, int size){
        int twin = (size - 1 - idx);
        return twin;
    }
       vector<int> listToVector(ListNode* head){
        ListNode *worker = head;
        vector<int> result;
        while(worker != nullptr){
            result.push_back(worker->val);
            worker = worker->next;
        }
        return result;
    }
        int pairSum(ListNode* head) {
        int i = 0;
        vector<int> items = listToVector(head);
        int maxTwinSum = 0;
        for(int i = 0; i < items.size(); i++){
            int twinIdx = getTwinIndex(i, items.size());
            if (twinIdx >= i){
                maxTwinSum = max(items[i] + items[twinIdx], maxTwinSum);
            } else {
                return maxTwinSum;
            }
        }
        return maxTwinSum;
    }
};