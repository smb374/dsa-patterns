// Created by Po-Yeh Chen at 2025/01/13 19:46
// leetgo: 1.4.13
// https://leetcode.com/problems/top-k-frequent-elements/

#include "LC_IO.h"
#include <bits/stdc++.h>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

// @lc code=begin

struct element {
    int val, freq;

    element(int val, int freq) : val(val), freq(freq) {}
};

class Solution {
  public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        auto cmp = [](const element& a, const element& b) {
            return a.freq < b.freq;
        };
        priority_queue<element, std::vector<element>, decltype(cmp)> pq(cmp);
        unordered_map<int, int> freq;
        vector<int> res(k, 0);

        for (int num : nums) {
            freq[num]++;
        }

        for (auto& p : freq) {
            pq.emplace(p.first, p.second);
        }

        for (int i = 0; i < k; i++) {
            res[i] = pq.top().val;
            pq.pop();
        }

        return res;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<int> nums;
    LeetCodeIO::scan(cin, nums);
    int k;
    LeetCodeIO::scan(cin, k);

    Solution* obj = new Solution();
    auto res = obj->topKFrequent(nums, k);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
