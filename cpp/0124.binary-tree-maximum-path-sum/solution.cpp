// Created by Po-Yeh Chen at 2025/01/13 22:19
// leetgo: 1.4.13
// https://leetcode.com/problems/binary-tree-maximum-path-sum/

#include "LC_IO.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <limits>
using namespace std;

// @lc code=begin

int dfs(TreeNode* node, int& max_sum) {
    if (!node) {
        return 0;
    }

    int lgain = max(dfs(node->left, max_sum), 0);
    int rgain = max(dfs(node->right, max_sum), 0);

    max_sum = max(max_sum, node->val + lgain + rgain);

    return max(node->val + lgain, node->val + rgain);
}

class Solution {
  public:
    int maxPathSum(TreeNode* root) {
        int max_sum = numeric_limits<int>::min();

        dfs(root, max_sum);

        return max_sum;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    TreeNode* root;
    LeetCodeIO::scan(cin, root);

    Solution* obj = new Solution();
    auto res = obj->maxPathSum(root);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
