// Created by Po-Yeh Chen at 2025/01/13 16:13
// leetgo: 1.4.13
// https://leetcode.com/problems/find-the-duplicate-number/

#include "LC_IO.h"
#include <bits/stdc++.h>
using namespace std;

// @lc code=begin

int next(int i, const int& n) { return (i + 1) % n; }

class Solution {
  public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0];
        int fast = nums[0];

        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        slow = nums[0];

        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }

        return fast;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<int> nums;
    LeetCodeIO::scan(cin, nums);

    Solution* obj = new Solution();
    auto res = obj->findDuplicate(nums);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
