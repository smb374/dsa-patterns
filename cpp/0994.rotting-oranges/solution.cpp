// Created by Po-Yeh Chen at 2025/01/13 23:18
// leetgo: 1.4.13
// https://leetcode.com/problems/rotting-oranges/

#include "LC_IO.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

// @lc code=begin

const int dr[4] = {1, 0, -1, 0};
const int dc[4] = {0, -1, 0, 1};

class Solution {
  public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), max_time = 2;
        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                }
            }
        }
        // BFS on matrix to mark timestamp.
        while (!q.empty()) {

            auto& cell = q.front();

            for (int i = 0; i < 4; i++) {
                int nr = cell.first + dr[i];
                int nc = cell.second + dc[i];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
                    grid[nr][nc] == 1) {
                    grid[nr][nc] = grid[cell.first][cell.second] + 1;
                    q.push({nr, nc});
                }
            }

            q.pop();
        }
        // Search the max timestamp & check fresh ones.
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    return -1;
                }
                max_time = max(max_time, grid[i][j]);
            }
        }

        return max_time - 2;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<vector<int>> grid;
    LeetCodeIO::scan(cin, grid);

    Solution* obj = new Solution();
    auto res = obj->orangesRotting(grid);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
