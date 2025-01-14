// Created by Po-Yeh Chen at 2025/01/13 17:59
// leetgo: 1.4.13
// https://leetcode.com/problems/largest-rectangle-in-histogram/

#include "LC_IO.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <limits>
#include <stack>
using namespace std;

// @lc code=begin

class Solution {
  public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> s;
        s.push(-1);
        int amax = 0;

        for (int i = 0; i < heights.size(); i++) {
            while (s.top() != -1 && heights[i] < heights[s.top()]) {
                int height = heights[s.top()];
                s.pop();
                int width = i - s.top() - 1;
                amax = max(amax, width * height);
            }
            s.push(i);
        }

        while (s.top() != -1) {
            int height = heights[s.top()];
            s.pop();
            int width = heights.size() - s.top() - 1;
            amax = max(amax, width * height);
        }

        return amax;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<int> heights;
    LeetCodeIO::scan(cin, heights);

    Solution* obj = new Solution();
    auto res = obj->largestRectangleArea(heights);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
