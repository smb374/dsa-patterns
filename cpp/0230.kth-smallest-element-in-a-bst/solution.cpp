// Created by Po-Yeh Chen at 2025/01/13 22:07
// leetgo: 1.4.13
// https://leetcode.com/problems/kth-smallest-element-in-a-bst/

#include "LC_IO.h"
#include <bits/stdc++.h>
#include <vector>
using namespace std;

// @lc code=begin

void dfs(TreeNode* node, vector<int>& path) {
    if (node) {
        dfs(node->left, path);
        path.push_back(node->val);
        dfs(node->right, path);
    }
}

class Solution {
  public:
    int kthSmallest(TreeNode* root, int k) {
        vector<int> path;

        dfs(root, path);

        if (path.size() >= k) {
            return path[k - 1];
        } else {
            return -1;
        }
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    TreeNode* root;
    LeetCodeIO::scan(cin, root);
    int k;
    LeetCodeIO::scan(cin, k);

    Solution* obj = new Solution();
    auto res = obj->kthSmallest(root, k);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
