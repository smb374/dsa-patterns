// Created by Po-Yeh Chen at 2025/01/13 20:23
// leetgo: 1.4.13
// https://leetcode.com/problems/insert-interval/

#include "LC_IO.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

// @lc code=begin

class Solution {
  public:
    vector<vector<int>> insert(vector<vector<int>>& intervals,
                               vector<int>& newInterval) {
        intervals.emplace_back(newInterval);
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
                int start = min(res.back()[0], i[0]);

                res.back()[0] = start;
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
    vector<int> newInterval;
    LeetCodeIO::scan(cin, newInterval);

    Solution* obj = new Solution();
    auto res = obj->insert(intervals, newInterval);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
