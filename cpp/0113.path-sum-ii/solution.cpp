// Created by Po-Yeh Chen at 2025/01/13 22:42
// leetgo: 1.4.13
// https://leetcode.com/problems/path-sum-ii/

#include "LC_IO.h"
#include <bits/stdc++.h>
#include <vector>
using namespace std;

// @lc code=begin

void dfs(TreeNode* node, int sum, vector<int>& path,
         vector<vector<int>>& result, const int& target) {
    if (!node) {
        return;
    }

    sum += node->val;
    path.push_back(node->val);

    if (!node->left && !node->right && sum == target) {
        result.emplace_back(path);
    } else {
        dfs(node->left, sum, path, result, target);
        dfs(node->right, sum, path, result, target);
    }

    path.pop_back();
    sum -= node->val;

    return;
}

class Solution {
  public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<int> path;
        vector<vector<int>> res;

        dfs(root, 0, path, res, targetSum);

        return res;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    TreeNode* root;
    LeetCodeIO::scan(cin, root);
    int targetSum;
    LeetCodeIO::scan(cin, targetSum);

    Solution* obj = new Solution();
    auto res = obj->pathSum(root, targetSum);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
