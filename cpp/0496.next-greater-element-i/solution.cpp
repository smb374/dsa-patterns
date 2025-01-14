// Created by Po-Yeh Chen at 2025/01/13 17:28
// leetgo: 1.4.13
// https://leetcode.com/problems/next-greater-element-i/

#include "LC_IO.h"
#include <bits/stdc++.h>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

// @lc code=begin

class Solution {
  public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> s;
        unordered_map<int, int> table;
        // Preprocess nums2 with a monotonic stack
        // and store stack top's next greater value in the table.
        for (int num : nums2) {
            while (!s.empty() && num > s.top()) {
                table[s.top()] = num;
                s.pop();
            }
            s.push(num);
        }

        while (!s.empty()) {
            table[s.top()] = -1;
            s.pop();
        }

        vector<int> res;

        for (int num : nums1) {
            res.push_back(table[num]);
        }

        return res;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<int> nums1;
    LeetCodeIO::scan(cin, nums1);
    vector<int> nums2;
    LeetCodeIO::scan(cin, nums2);

    Solution* obj = new Solution();
    auto res = obj->nextGreaterElement(nums1, nums2);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
