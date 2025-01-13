// Created by Po-Yeh Chen at 2025/01/13 13:53
// leetgo: 1.4.13
// https://leetcode.com/problems/container-with-most-water/

#include "LC_IO.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <limits>
using namespace std;

// @lc code=begin

class Solution {
  public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int i = 0, j = n - 1, area = numeric_limits<int>::min();

        while (i < j) {
            int hl = height[i], hr = height[j], width = j - i;

            if (hl < hr) {
                area = max(area, hl * width);
                i++;
            } else {
                area = max(area, hr * width);
                j--;
            }
        }

        return area;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<int> height;
    LeetCodeIO::scan(cin, height);

    Solution* obj = new Solution();
    auto res = obj->maxArea(height);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
