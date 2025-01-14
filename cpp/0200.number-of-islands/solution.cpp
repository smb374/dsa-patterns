// Created by Po-Yeh Chen at 2025/01/14 00:23
// leetgo: 1.4.13
// https://leetcode.com/problems/number-of-islands/

#include "LC_IO.h"
#include <bits/stdc++.h>
#include <vector>
using namespace std;

// @lc code=begin

const int dr[4] = {1, 0, -1, 0};
const int dc[4] = {0, -1, 0, 1};

void dfs(int sr, int sc, vector<vector<char>>& grid, const int& m,
         const int& n) {
    if (sr >= 0 && sr < m && sc >= 0 && sc < n && grid[sr][sc] == '1') {
        grid[sr][sc] = '0';

        for (int i = 0; i < 4; i++) {
            dfs(sr + dr[i], sc + dc[i], grid, m, n);
        }
    }
}

class Solution {
  public:
    int numIslands(vector<vector<char>>& grid) {
        if (!grid.size()) {
            return 0;
        }

        int m = grid.size(), n = grid[0].size(), count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    dfs(i, j, grid, m, n);
                }
            }
        }

        return count;
    }
};

// @lc code=end

// Warning: this is a manual question, the generated test code may be incorrect.
int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<vector<char>> grid;
    LeetCodeIO::scan(cin, grid);

    Solution* obj = new Solution();
    auto res = obj->numIslands(grid);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
