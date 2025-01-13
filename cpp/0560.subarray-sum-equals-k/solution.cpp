// Created by Po-Yeh Chen at 2025/01/13 11:49
// leetgo: 1.4.13
// https://leetcode.com/problems/subarray-sum-equals-k/

#include "LC_IO.h"
#include <bits/stdc++.h>
#include <cstdio>
#include <unordered_map>
#include <vector>
using namespace std;

// @lc code=begin

class Solution {
  public:
    int subarraySum(vector<int>& nums, int k) {
        int sum = 0, n = nums.size(), count = 0;
        unordered_map<int, int> table;
        // means k = sum[0, i], always unique so table[0] = 1.
        table[0] = 1;

        // sum[i, j] = k
        // -> sum[0, j] - sum[0, i] = k
        // -> sum[0, j] - k = sum[0, i]
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            if (table.count(sum - k)) {
                count += table[sum - k];
            }
            table[sum]++;
        }

        return count;
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
    auto res = obj->subarraySum(nums, k);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
