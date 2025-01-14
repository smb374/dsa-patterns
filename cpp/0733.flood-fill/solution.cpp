// Created by Po-Yeh Chen at 2025/01/14 00:16
// leetgo: 1.4.13
// https://leetcode.com/problems/flood-fill/

#include "LC_IO.h"
#include <bits/stdc++.h>
#include <queue>
#include <utility>
using namespace std;

// @lc code=begin

const int dr[4] = {1, 0, -1, 0};
const int dc[4] = {0, -1, 0, 1};
class Solution {
  public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc,
                                  int color) {
        int m = image.size(), n = image[0].size();
        int source_color = image[sr][sc];
        if (source_color == color) {
            return image;
        }
        queue<pair<int, int>> q;
        image[sr][sc] = color;
        q.emplace(sr, sc);

        while (!q.empty()) {
            pair<int, int> cell = q.front();

            for (int i = 0; i < 4; i++) {
                int nr = cell.first + dr[i];
                int nc = cell.second + dc[i];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
                    image[nr][nc] == source_color) {
                    image[nr][nc] = color;
                    q.emplace(nr, nc);
                }
            }

            q.pop();
        }

        return image;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<vector<int>> image;
    LeetCodeIO::scan(cin, image);
    int sr;
    LeetCodeIO::scan(cin, sr);
    int sc;
    LeetCodeIO::scan(cin, sc);
    int color;
    LeetCodeIO::scan(cin, color);

    Solution* obj = new Solution();
    auto res = obj->floodFill(image, sr, sc, color);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
