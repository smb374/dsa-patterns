// Created by Po-Yeh Chen at 2025/01/13 17:36
// leetgo: 1.4.13
// https://leetcode.com/problems/daily-temperatures/

#include "LC_IO.h"
#include <bits/stdc++.h>
#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

// @lc code=begin

class Solution {
  public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> s;
        int n = temperatures.size();
        vector<int> res(n, 0);

        for (int i = 0; i < n; i++) {
            int t = temperatures[i];
            while (!s.empty() && t > temperatures[s.top()]) {
                res[s.top()] = i - s.top();
                s.pop();
            }
            s.push(i);
        }

        return res;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<int> temperatures;
    LeetCodeIO::scan(cin, temperatures);

    Solution* obj = new Solution();
    auto res = obj->dailyTemperatures(temperatures);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
