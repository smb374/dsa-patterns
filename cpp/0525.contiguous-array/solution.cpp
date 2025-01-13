// Created by Po-Yeh Chen at 2025/01/13 11:24
// leetgo: 1.4.13
// https://leetcode.com/problems/contiguous-array/

#include "LC_IO.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;

// @lc code=begin

class Solution {
  public:
    int findMaxLength(vector<int>& nums) {
        int n = nums.size(), sum = 0, len = 0;
        unordered_map<int, int> table;

        for (int i = 0; i < n; i++) {
            // prefix sum for nums until i
            // 0 -> -1 such that equal numbers of 0 and 1 will have a sum of 0
            sum += nums[i] ? 1 : -1;
            if (!sum) {
                // Case 1: found equal numbers at i
                len = i + 1;
            } else if (table.count(sum)) {
                // Case 2: repeated sum happend at i and j = table[sum]
                // means the sum is 0 between i and j -> equal number of 0
                // and 1.
                len = max(len, i - table[sum]);
            } else {
                // Case 3: record seen sum to index pair.
                table[sum] = i;
            }
        }

        return len;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<int> nums;
    LeetCodeIO::scan(cin, nums);

    Solution* obj = new Solution();
    auto res = obj->findMaxLength(nums);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
