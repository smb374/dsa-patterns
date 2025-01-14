// Created by Po-Yeh Chen at 2025/01/13 22:00
// leetgo: 1.4.13
// https://leetcode.com/problems/binary-tree-paths/

#include "LC_IO.h"
#include <bits/stdc++.h>
#include <string>
#include <vector>
using namespace std;

// @lc code=begin

void dfs(TreeNode* node, string path, vector<string>& res) {
    if (node) {
        path += to_string(node->val);
        if (!node->left && !node->right) {
            res.push_back(path);
        } else {
            path += "->";
            dfs(node->left, path, res);
            dfs(node->right, path, res);
        }
    }
}

class Solution {
  public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        string path;

        dfs(root, path, res);

        return res;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    TreeNode* root;
    LeetCodeIO::scan(cin, root);

    Solution* obj = new Solution();
    auto res = obj->binaryTreePaths(root);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
