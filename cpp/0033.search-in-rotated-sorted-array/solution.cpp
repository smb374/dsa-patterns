// Created by Po-Yeh Chen at 2025/01/13 21:21
// leetgo: 1.4.13
// https://leetcode.com/problems/search-in-rotated-sorted-array/

#include "LC_IO.h"
#include <bits/stdc++.h>
using namespace std;

// @lc code=begin

class Solution {
  public:
    int search(vector<int>& nums, int target) {
        int i = 0, j = nums.size() - 1;
        // rotate sorted: s[0] > s[n-1], s[pivot] is the highest point
        while (i <= j) {
            int mid = i + ((j - i) / 2);
            if (nums[mid] == target) {
                // Case 1: Found target
                return mid;
            } else if (nums[mid] >= nums[i]) {
                // Case 2: mid's left is sorted.
                if (target >= nums[i] && target < nums[mid]) {
                    // target is on left subarray
                    j = mid - 1;
                } else {
                    // target is on right subarray
                    i = mid + 1;
                }
            } else {
                // Case 3: mid's right is sorted.
                if (target <= nums[j] && target > nums[mid]) {
                    // target is on right subarray
                    i = mid + 1;
                } else {
                    // target is on left subarray
                    j = mid - 1;
                }
            }
        }

        return -1;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<int> nums;
    LeetCodeIO::scan(cin, nums);
    int target;
    LeetCodeIO::scan(cin, target);

    Solution* obj = new Solution();
    auto res = obj->search(nums, target);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
