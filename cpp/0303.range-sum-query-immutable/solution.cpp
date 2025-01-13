// Created by Po-Yeh Chen at 2025/01/13 11:15
// leetgo: 1.4.13
// https://leetcode.com/problems/range-sum-query-immutable/

#include "LC_IO.h"
#include <bits/stdc++.h>
#include <vector>
using namespace std;

// @lc code=begin

class NumArray {
  private:
    vector<int> prefix_sum;

  public:
    NumArray(vector<int>& nums) : prefix_sum(nums.size(), 0) {
        prefix_sum[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            prefix_sum[i] = prefix_sum[i - 1] + nums[i];
        }
    }

    int sumRange(int left, int right) {
        if (!left) {
            return prefix_sum[right];
        } else {
            return prefix_sum[right] - prefix_sum[left - 1];
        }
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<string> method_names;
    LeetCodeIO::scan(cin, method_names);

    NumArray* obj;
    const unordered_map<string, function<void()>> methods = {
        {"NumArray",
         [&]() {
             vector<int> nums;
             LeetCodeIO::scan(cin, nums);
             cin.ignore();
             int numsSize;
             LeetCodeIO::scan(cin, numsSize);
             cin.ignore();
             obj = new NumArray(nums, numsSize);
             out_stream << "null,";
         }},
        {"sumRange",
         [&]() {
             int left;
             LeetCodeIO::scan(cin, left);
             cin.ignore();
             int right;
             LeetCodeIO::scan(cin, right);
             cin.ignore();
             LeetCodeIO::print(out_stream, obj->sumRange(left, right));
             out_stream << ',';
         }},
    };
    cin >> ws;
    out_stream << '[';
    for (auto&& method_name : method_names) {
        cin.ignore(2);
        methods.at(method_name)();
    }
    cin.ignore();
    out_stream.seekp(-1, ios_base::end);
    out_stream << ']';
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
