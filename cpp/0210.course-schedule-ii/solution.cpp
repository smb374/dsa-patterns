// Created by Po-Yeh Chen at 2025/01/13 22:52
// leetgo: 1.4.13
// https://leetcode.com/problems/course-schedule-ii/

#include "LC_IO.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

// @lc code=begin

unordered_map<int, int> find_indegree(unordered_map<int, vector<int>>& graph) {
    unordered_map<int, int> indegree;
    for (auto& entry : graph) {
        indegree[entry.first] = 0;
    }

    for (auto& node : graph) {
        for (auto& neighbor : node.second) {
            indegree[neighbor] += 1;
        }
    }

    return indegree;
}

class Solution {
  public:
    // Topoligical sort
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int n = prerequisites.size();
        unordered_map<int, vector<int>> graph;
        unordered_map<int, int> indegree;
        // Build graph
        for (int i = 0; i < n; i++) {
            graph[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }
        // Build indegree
        for (auto& node : graph) {
            for (auto& neighbor : node.second) {
                indegree[neighbor] += 1;
            }
        }

        // Topological sort.
        vector<int> res;
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (!indegree[i])
                q.push(i);
        }

        while (!q.empty()) {
            int node = q.front();

            res.emplace_back(node);
            for (const int& neighbor : graph[node]) {
                indegree[neighbor]--;
                if (!indegree[neighbor]) {
                    q.push(neighbor);
                }
            }
            q.pop();
        }

        reverse(res.begin(), res.end());
        if (res.size() == numCourses) {
            return res;
        } else {
            return {};
        }
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    int numCourses;
    LeetCodeIO::scan(cin, numCourses);
    vector<vector<int>> prerequisites;
    LeetCodeIO::scan(cin, prerequisites);

    Solution* obj = new Solution();
    auto res = obj->findOrder(numCourses, prerequisites);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
