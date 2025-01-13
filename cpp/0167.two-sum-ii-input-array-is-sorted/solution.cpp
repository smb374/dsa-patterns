// Created by Po-Yeh Chen at 2025/01/13 13:39
// leetgo: 1.4.13
// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/

#include "LC_IO.h"
#include <bits/stdc++.h>
using namespace std;

// @lc code=begin

class Solution {
  public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int n = numbers.size();
        int i = 0, j = n - 1;
        while (i < j) {
            int sum = numbers[i] + numbers[j];
            if (sum > target) {
                j--;
            } else if (sum < target) {
                i++;
            } else {
                return {i + 1, j + 1};
            }
        }

        return {-1, -1};
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<int> numbers;
    LeetCodeIO::scan(cin, numbers);
    int target;
    LeetCodeIO::scan(cin, target);

    Solution* obj = new Solution();
    auto res = obj->twoSum(numbers, target);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
