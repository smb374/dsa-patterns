// Created by Po-Yeh Chen at 2025/01/13 20:17
// leetgo: 1.4.13
// https://leetcode.com/problems/merge-intervals/

#include "LC_IO.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

// @lc code=begin

class Solution {
  public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[0] < b[0];
             });
        vector<vector<int>> res;

        for (vector<int>& i : intervals) {
            if (res.empty() || i[0] > res.back()[1]) {
                res.emplace_back(i);
            } else {
                int end = max(res.back()[1], i[1]);
                res.back()[1] = end;
            }
        }

        return res;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<vector<int>> intervals;
    LeetCodeIO::scan(cin, intervals);

    Solution* obj = new Solution();
    auto res = obj->merge(intervals);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
