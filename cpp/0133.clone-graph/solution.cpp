// Created by Po-Yeh Chen at 2025/01/13 22:37
// leetgo: 1.4.13
// https://leetcode.com/problems/clone-graph/

#include "LC_IO.h"
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

// Definition for a Node.
class Node {
  public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

// @lc code=begin

class Solution {
  private:
    unordered_map<Node*, Node*> visited;

  public:
    Node* cloneGraph(Node* node) {
        if (!node)
            return node;

        if (visited.count(node)) {
            return visited[node];
        }

        Node* cloned = new Node(node->val, {});

        visited[node] = cloned;

        for (Node* neighbor : node->neighbors) {
            cloned->neighbors.push_back(cloneGraph(neighbor));
        }

        return cloned;
    }
};

// @lc code=end

// Warning: this is a manual question, the generated test code may be incorrect.
int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<vector<int>> edges;
    LeetCodeIO::scan(cin, edges);

    Solution* obj = new Solution();
    auto res = obj->cloneGraph(edges);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
