// Created by Po-Yeh Chen at 2025/01/14 00:31
// leetgo: 1.4.13
// https://leetcode.com/problems/surrounded-regions/

#include "LC_IO.h"
#include <bits/stdc++.h>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

// @lc code=begin

const int dr[4] = {1, 0, -1, 0};
const int dc[4] = {0, -1, 0, 1};
void bfs(int sr, int sc, vector<vector<char>>& board, const int& m,
         const int& n) {
    queue<pair<int, int>> q;
    q.emplace(sr, sc);

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        if (board[r][c] != 'O')
            continue;

        board[r][c] = 'E';

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                q.emplace(nr, nc);
            }
        }
    }
}

class Solution {
  public:
    void solve(vector<vector<char>>& board) {
        int m = board.size();
        if (!m)
            return;
        int n = board[0].size();

        vector<pair<int, int>> border;

        for (int r = 0; r < m; r++) {
            if (board[r][0] == 'O') {
                border.emplace_back(r, 0);
            }
            if (board[r][n - 1] == 'O') {
                border.emplace_back(r, n - 1);
            }
        }
        for (int c = 0; c < n; c++) {
            if (board[0][c] == 'O') {
                border.emplace_back(0, c);
            }
            if (board[m - 1][c] == 'O') {
                border.emplace_back(m - 1, c);
            }
        }

        for (auto [r, c] : border) {
            bfs(r, c, board, m, n);
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == 'E')
                    board[i][j] = 'O';
            }
        }
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<vector<char>> board;
    LeetCodeIO::scan(cin, board);

    Solution* obj = new Solution();
    obj->solve(board);
    LeetCodeIO::print(out_stream, board);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
