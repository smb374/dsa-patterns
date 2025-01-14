// Created by Po-Yeh Chen at 2025/01/13 23:11
// leetgo: 1.4.13
// https://leetcode.com/problems/binary-tree-level-order-traversal/

#include "LC_IO.h"
#include <bits/stdc++.h>
#include <queue>
#include <vector>
using namespace std;

// @lc code=begin

class Solution {
  public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root)
            return {};
        queue<TreeNode*> q;
        vector<vector<int>> res;

        q.push(root);

        while (!q.empty()) {
            int n = q.size();
            vector<int> nodes;
            for (int i = 0; i < n; i++) {
                TreeNode* node = q.front();
                nodes.emplace_back(node->val);

                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);

                q.pop();
            }
            res.emplace_back(nodes);
        }

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
    auto res = obj->levelOrder(root);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
