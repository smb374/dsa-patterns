// Created by Po-Yeh Chen at 2025/01/13 19:42
// leetgo: 1.4.13
// https://leetcode.com/problems/kth-largest-element-in-an-array/

#include "LC_IO.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <functional>
using namespace std;

// @lc code=begin

class Solution {
  public:
    int findKthLargest(vector<int>& nums, int k) {
        // O(n) selecttion algorithm
        nth_element(nums.begin(), nums.begin() + k - 1, nums.end(),
                    std::greater<>{});

        return nums[k - 1];
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<int> nums;
    LeetCodeIO::scan(cin, nums);
    int k;
    LeetCodeIO::scan(cin, k);

    Solution* obj = new Solution();
    auto res = obj->findKthLargest(nums, k);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
