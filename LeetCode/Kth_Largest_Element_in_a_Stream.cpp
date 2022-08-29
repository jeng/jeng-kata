class KthLargest {
private:
    multiset<int> *myset;
    int myk;
public:
    KthLargest(int k, vector<int>& nums) {
        myk = k;
        myset = new multiset<int>(nums.begin(), nums.end());
    }
        int add(int val) {        
        myset->insert(myset->begin(), val);
        std::multiset<int>::reverse_iterator it = myset->rbegin();
        std::advance(it, myk-1);
        return *it;
    }
};
/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */