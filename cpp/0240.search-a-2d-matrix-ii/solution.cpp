// Created by Po-Yeh Chen at 2025/01/13 21:40
// leetgo: 1.4.13
// https://leetcode.com/problems/search-a-2d-matrix-ii/

#include "LC_IO.h"
#include <bits/stdc++.h>
using namespace std;

// @lc code=begin

class Solution {
  public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size() - 1;
        int col = 0;
        // Walk from bottom left
        // since column 0 is the smallest in a row
        // and row n-1 is the biggest in a column
        while (row >= 0 && col < matrix[0].size()) {
            if (matrix[row][col] > target) {
                // walk up
                row--;
            } else if (matrix[row][col] < target) {
                // walk right
                col++;
            } else {
                return true;
            }
        }

        return false;
    }
};

// @lc code=end

// Warning: this is a manual question, the generated test code may be incorrect.
int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    vector<vector<int>> matrix;
    LeetCodeIO::scan(cin, matrix);
    int target;
    LeetCodeIO::scan(cin, target);

    Solution* obj = new Solution();
    auto res = obj->searchMatrix(matrix, target);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
