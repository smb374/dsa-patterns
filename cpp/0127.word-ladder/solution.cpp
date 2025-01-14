// Created by Po-Yeh Chen at 2025/01/13 23:46
// leetgo: 1.4.13
// https://leetcode.com/problems/word-ladder/

#include "LC_IO.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <string>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

// @lc code=begin

constexpr int hamming_distance(const string_view& a, const string_view& b,
                               const int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        count += (int)(a[i] != b[i]);
    }

    return count;
}

class Solution {
  public:
    int ladderLength(string beginWord, string endWord,
                     vector<string>& wordList) {
        if (find(wordList.begin(), wordList.end(), endWord) == wordList.end()) {
            return 0;
        }
        int size = beginWord.size();
        vector<string_view> words(wordList.begin(), wordList.end());
        // Double-ended BFS
        unordered_set<string_view> head, tail, next;

        head.reserve(wordList.size() + 1);
        tail.reserve(wordList.size() + 1);
        next.reserve(wordList.size() + 1);

        head.emplace(beginWord);
        tail.emplace(endWord);

        for (int level = 1; !head.empty() && !tail.empty(); level++) {
            if (head.size() > tail.size()) {
                head.swap(tail);
            }

            for (auto p : head) {
                for (auto q : tail) {
                    if (hamming_distance(p, q, size) == 1) {
                        return level + 1;
                    }
                }

                int idx = 0;
                while (idx < words.size()) {
                    string_view q = words[idx];
                    if (hamming_distance(p, q, size) != 1) {
                        idx++;
                        continue;
                    }

                    swap(words[idx], words.back());
                    words.pop_back();
                    next.insert(q);
                }
            }
            head.swap(next);
            next.clear();
        }

        return 0;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    string beginWord;
    LeetCodeIO::scan(cin, beginWord);
    string endWord;
    LeetCodeIO::scan(cin, endWord);
    vector<string> wordList;
    LeetCodeIO::scan(cin, wordList);

    Solution* obj = new Solution();
    auto res = obj->ladderLength(beginWord, endWord, wordList);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
