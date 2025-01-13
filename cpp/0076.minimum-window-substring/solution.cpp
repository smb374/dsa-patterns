// Created by Po-Yeh Chen at 2025/01/13 14:32
// leetgo: 1.4.13
// https://leetcode.com/problems/minimum-window-substring/

#include "LC_IO.h"
#include <bits/stdc++.h>
#include <limits>
using namespace std;

// @lc code=begin

class Solution {
  public:
    string minWindow(string s, string t) {
        // Early return cases.
        if (s.empty() || t.empty() || s.length() < t.length()) {
            return "";
        }

        // t_count: frequency table of t
        // window_count: frequency table of window
        int t_count[128] = {0}, window_count[128] = {0}, required = 0;

        for (const char c : t) {
            if (!t_count[c])
                required++; // check required unique chars.
            t_count[c]++;
        }

        // lo: window left bound
        // hi: window right bound
        int lo = 0, hi = 0, min_len = numeric_limits<int>::max(), base = 0;
        // formed: window has formed chars in t.
        int formed = 0;

        while (hi < s.length()) {
            char c = s[hi];
            // Push c to the window
            window_count[c]++;
            // If c is in t and window have the same frequency for c in t
            if (t_count[c] && window_count[c] == t_count[c]) {
                // Increase formed
                formed++;
            }

            while (lo <= hi && formed == required) {
                c = s[lo];
                // Update min_len
                if (hi - lo + 1 < min_len) {
                    min_len = hi - lo + 1;
                    base = lo;
                }
                // Pop c from the window
                window_count[c]--;
                // If c is in t and window have smaller frequency for c in t.
                if (t_count[c] && window_count[c] < t_count[c]) {
                    // Decrease formed
                    formed--;
                }

                lo++; // Advance lo ptr
            }
            hi++; // Advance hi ptr
        }

        return min_len == numeric_limits<int>::max() ? ""
                                                     : s.substr(base, min_len);
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    string s;
    LeetCodeIO::scan(cin, s);
    string t;
    LeetCodeIO::scan(cin, t);

    Solution* obj = new Solution();
    auto res = obj->minWindow(s, t);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
