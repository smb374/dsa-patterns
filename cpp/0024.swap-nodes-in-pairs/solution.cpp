// Created by Po-Yeh Chen at 2025/01/13 17:07
// leetgo: 1.4.13
// https://leetcode.com/problems/swap-nodes-in-pairs/

#include "LC_IO.h"
#include <bits/stdc++.h>
using namespace std;

// @lc code=begin

class Solution {
  public:
    ListNode* swapPairs(ListNode* head) {
        if (!head)
            return head;
        ListNode dummy(-1);
        dummy.next = head;
        ListNode *n1 = head, *n2 = head->next, *prev = &dummy;
        if (!n2)
            return head;

        while (n1 && n2) {
            // prev -> n1 -> n2 -> next
            ListNode* next = n2->next;
            // (prev -> n1, n2) -> next
            n1->next = next;
            // (prev, n2) -> n1 -> next
            n2->next = n1;
            // prev -> n2 -> n1 -> next
            prev->next = n2;
            prev = n1;
            if (next && next->next) {
                n1 = next;
                n2 = next->next;
            } else {
                break;
            }
        }

        return dummy.next;
    }
};

// @lc code=end

int main() {
    ios_base::sync_with_stdio(false);
    stringstream out_stream;

    ListNode* head;
    LeetCodeIO::scan(cin, head);

    Solution* obj = new Solution();
    auto res = obj->swapPairs(head);
    LeetCodeIO::print(out_stream, res);
    cout << "\noutput: " << out_stream.rdbuf() << endl;

    delete obj;
    return 0;
}
