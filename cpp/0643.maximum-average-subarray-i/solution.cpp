// Created by Po-Yeh Chen at 2025/01/13 14:06
// leetgo: 1.4.13
// https://leetcode.com/problems/maximum-average-subarray-i/

#include "LC_IO.h"
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

// @lc code=begin

class Solution {
  public:
    double findMaxAverage(vector<int>& nums, int k) {
        int sum = 0, n = nums.size();
        for (int i = 0; i < k; i++) {
            sum += nums[i];
        }

        double avg = (double)sum / (double)k;
        if (k == n) {
            return avg;
        }

        for (int i = k; i < n; i++) {
            sum = sum + nums[i] - nums[i - k];
            avg = max(avg, (double)sum / (double)k);
        }

        return avg;
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
    auto res = obj->findMaxAverage(nums, k);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
