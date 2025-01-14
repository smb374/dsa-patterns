// Created by Po-Yeh Chen at 2025/01/13 21:29
// leetgo: 1.4.13
// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

#include "LC_IO.h"
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

// @lc code=begin

class Solution {
  public:
    int findMin(vector<int>& nums) {
        // Search the center
        int i = 1, j = nums.size() - 2;

        while (i <= j) {
            int mid = i + ((j - i) / 2);
            if (nums[mid - 1] > nums[mid] && nums[mid + 1] > nums[mid]) {
                // Case 1: found minimal
                return nums[mid];
            } else if (nums[mid] > nums[0]) {
                // Case 2: mid is at the left of pivot
                i = mid + 1;
            } else {
                // Case 3: mid is at the right of pivot.
                j = mid - 1;
            }
        }
        // Not rotate sorted.
        return min(nums[0], nums[nums.size() - 1]);
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<int> nums;
    LeetCodeIO::scan(cin, nums);

    Solution* obj = new Solution();
    auto res = obj->findMin(nums);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
