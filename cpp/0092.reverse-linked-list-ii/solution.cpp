// Created by Po-Yeh Chen at 2025/01/13 16:43
// leetgo: 1.4.13
// https://leetcode.com/problems/reverse-linked-list-ii/

#include "LC_IO.h"
#include <bits/stdc++.h>
using namespace std;

// @lc code=begin

ListNode* reverse(ListNode* head) {
    ListNode *prev = nullptr, *curr = head, *next = nullptr;

    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

class Solution {
  public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode *prev = nullptr, *curr = head;
        int count = 1;

        // Get start node
        while (count != left) {
            prev = curr;
            curr = curr->next;
            count++;
        }
        ListNode* start = curr;
        // Get end node
        while (count != right) {
            curr = curr->next;
            count++;
        }
        ListNode* end = curr->next;
        // split the end and revers the list.
        curr->next = nullptr;
        ListNode* new_head = reverse(start);
        // prev of start is previous node of start before reverse.
        if (prev) {
            prev->next = new_head;
        }
        // walk to list end and append end node.
        curr = new_head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = end;
        // check if left is 1 (reverse strarts at head)
        return (left == 1) ? new_head : head;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    ListNode* head;
    LeetCodeIO::scan(cin, head);
    int left;
    LeetCodeIO::scan(cin, left);
    int right;
    LeetCodeIO::scan(cin, right);

    Solution* obj = new Solution();
    auto res = obj->reverseBetween(head, left, right);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
