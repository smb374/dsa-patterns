// Created by Po-Yeh Chen at 2025/01/13 16:09
// leetgo: 1.4.13
// https://leetcode.com/problems/happy-number/

#include "LC_IO.h"
#include <bits/stdc++.h>
using namespace std;

// @lc code=begin

int next(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }

    return sum;
}

class Solution {
  public:
    bool isHappy(int n) {
        if (n == 1) {
            return true;
        } else if (!n) {
            return false;
        }

        int slow = n, fast = n;

        while (fast != 1) {
            slow = next(slow);
            fast = next(next(fast));
            if (slow == fast && slow != 1) {
                return false;
            }
        }

        return true;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    int n;
    LeetCodeIO::scan(cin, n);

    Solution* obj = new Solution();
    auto res = obj->isHappy(n);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
