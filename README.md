# dsa-patterns

LeetCode DSA patterns

## Prefix Sum

### [303. Range Sum Query - Immutable (Easy)](/cpp/0303.range-sum-query-immutable/question.md)

Build a prefix sum array such that
`sum[i, j] = sum[0, j] - sum[0, i - 1]`

### [525. Contiguous Array (Medium)](/cpp/0525.contiguous-array/question.md)

Gradual prefix sum. Note that we need to interpret 0 as -1.

<details>

<summary>Code</summary>

```cpp
int findMaxLength(vector<int>& nums) {
    int n = nums.size(), sum = 0, len = 0;
    unordered_map<int, int> table;

    for (int i = 0; i < n; i++) {
        // prefix sum for nums until i
        // 0 -> -1 such that equal numbers of 0 and 1 will have a sum of 0
        sum += nums[i] ? 1 : -1;
        if (!sum) {
            // Case 1: found equal numbers at i
            len = i + 1;
        } else if (table.count(sum)) {
            // Case 2: repeated sum happend at i and j = table[sum]
            // means the sum is 0 between i and j -> equal number of 0
            // and 1.
            len = max(len, i - table[sum]);
        } else {
            // Case 3: record seen sum to index pair.
            table[sum] = i;
        }
    }

    return len;
}
```

</details>

### [560. Subarray Sum Equals K (Medium)](/cpp/0560.subarray-sum-equals-k/question.md)

Gradual prefix sum. Note that we should match `k` in building loop
before adding `table[sum]`, otherwise it could match on extras
when `k = 0` if we choose other approach.

<details>

<summary>Code</summary>

```cpp
int subarraySum(vector<int>& nums, int k) {
    int sum = 0, n = nums.size(), count = 0;
    unordered_map<int, int> table;
    // means k = sum[0, i], always unique so table[0] = 1.
    table[0] = 1;

    // sum[i, j] = k
    // -> sum[0, j] - sum[0, i] = k
    // -> sum[0, j] - k = sum[0, i]
    for (int i = 0; i < n; i++) {
        sum += nums[i];
        if (table.count(sum - k)) {
            count += table[sum - k];
        }
        table[sum]++;
    }

    return count;
}
```

</details>

## Two Pointers

### [167. Two Sum II - Input Array Is Sorted (Medium)](/cpp/0167.two-sum-ii-input-array-is-sorted/question.md)

Two pointer starting on both sides,
advance right if sum is bigger, left if sum is smaller.

<details>
<summary>Code</summary>

```cpp
vector<int> twoSum(vector<int>& numbers, int target) {
    int n = numbers.size();
    int i = 0, j = n - 1;
    while (i < j) {
        int sum = numbers[i] + numbers[j];
        if (sum > target) {
            j--;
        } else if (sum < target) {
            i++;
        } else {
            return {i + 1, j + 1};
        }
    }

    return {-1, -1};
}
```

</details>

### [15. 3Sum (Medium)](/cpp/0015.3sum/question.md)

Sort the array first then for `i` in `[0..n-2]`:
Two pointers starting from `i+1` and `n-1`,
`j++` if sum is smaller, `k--` if sum is bigger.

Remember to skip identical numbers as the problem requests unique triplets.

<details>
<summary>Code</summary>

```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());

    for (int i = 0; i < n - 2; i++) {
        // Skip same numbers.
        if (i != 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        int x = nums[i];
        int j = i + 1, k = n - 1;
        while (j < k) {
            int y = nums[j], z = nums[k];
            int sum = x + y + z;

            if (sum < 0) {
                j++;
            } else if (sum > 0) {
                k--;
            } else {
                result.push_back({x, y, z});
                // Skip same numbers.
                while (j < k && nums[j] == y)
                    j++;
                while (j < k && nums[k] == z)
                    k--;
            }
        }
    }

    return result;
}
```

</details>

### [11. Container With Most Water (Medium)](/cpp/0011.container-with-most-water/question.md)

Two pointer starting on both sides, advance the one with lower height.

<details>
<summary>Code</summary>

```cpp
int maxArea(vector<int>& height) {
    int n = height.size();
    int i = 0, j = n - 1, area = numeric_limits<int>::min();

    while (i < j) {
        int hl = height[i], hr = height[j], width = j - i;

        if (hl < hr) {
            area = max(area, hl * width);
            i++;
        } else {
            area = max(area, hr * width);
            j--;
        }
    }

    return area;
}
```

</details>

## Sliding Window

### [643. Maximum Average Subarray I (Easy)](/cpp/0643.maximum-average-subarray-i/question.md)

Static window sliding.

<details>
<summary>Code</summary>

```cpp
double findMaxAverage(vector<int>& nums, int k) {
    int sum = 0, n = nums.size();
    for (int i = 0; i < k; i++) {
        sum += nums[i];
    }

    double avg = (double)sum / (double)k;
    if (k == n) {
        return avg;
    }

    for (int i = k; i < n; i++) {
        sum = sum + nums[i] - nums[i - k];
        avg = max(avg, (double)sum / (double)k);
    }

    return avg;
}
```

</details>

### [3. Longest Substring Without Repeating Characters (Medium)](/cpp/0003.longest-substring-without-repeating-characters/question.md)

Dynamic window sliding.
Remember length for `s[i..j]` is `j - i + 1` and use `j+1` in seen index table.

<details>
<summary>Code</summary>

```cpp
int lengthOfLongestSubstring(string s) {
    int n = s.size(), i = 0, len = 0;
    int seen[256] = {0};

    for (int j = 0; j < n; j++) {
        i = max(i, seen[s[j]]);
        len = max(len, j - i + 1);
        seen[s[j]] = j + 1;
    }

    return len;
}
```

</details>

### [76. Minimum Window Substring (Hard)](/cpp/0076.minimum-window-substring/question.md)

Dynamic window sliding.
Push & pop characters into the window and check the
minimum viable window length to contain all characters in target.

<details>
<summary>Code</summary>

```cpp
string minWindow(string s, string t) {
    // Early return cases.
    if (s.empty() || t.empty() || s.length() < t.length()) {
        return "";
    }

    // t_count: frequency table of t
    // window_count: frequency table of window
    int t_count[128] = {0}, window_count[128] = {0}, required = 0;

    for (const char c : t) {
        if (!t_count[c])
            required++; // check required unique chars.
        t_count[c]++;
    }

    // lo: window left bound
    // hi: window right bound
    int lo = 0, hi = 0, min_len = numeric_limits<int>::max(), base = 0;
    // formed: window has formed chars in t.
    int formed = 0;

    while (hi < s.length()) {
        char c = s[hi];
        // Push c to the window
        window_count[c]++;
        // If c is in t and window have the same frequency for c in t
        if (t_count[c] && window_count[c] == t_count[c]) {
            // Increase formed
            formed++;
        }

        while (lo <= hi && formed == required) {
            c = s[lo];
            // Update min_len
            if (hi - lo + 1 < min_len) {
                min_len = hi - lo + 1;
                base = lo;
            }
            // Pop c from the window
            window_count[c]--;
            // If c is in t and window have smaller frequency for c in t.
            if (t_count[c] && window_count[c] < t_count[c]) {
                // Decrease formed
                formed--;
            }

            lo++; // Advance lo ptr
        }
        hi++; // Advance hi ptr
    }

    return min_len == numeric_limits<int>::max() ? ""
                                                    : s.substr(base, min_len);
}
```

</details>

## Fast & Slow Pointers

### [141. Linked List Cycle (Easy)](/cpp/0141.linked-list-cycle/question.md)

Use slow-fast pointer to detect cycle

<details>
<summary>Code</summary>

```cpp
bool hasCycle(ListNode* head) {
    if (!head)
        return false;
    ListNode *slow = head, *fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }

    return false;
}
```

</details>

### [202. Happy Number (Easy)](/cpp/0202.happy-number/question.md)

Use slow-fast pointer with custom `next` function based on the rule.

<details>
<summary>Code</summary>

```cpp
int next(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }

    return sum;
}

bool isHappy(int n) {
    if (n == 1) {
        return true;
    } else if (!n) {
        return false;
    }

    int slow = n, fast = n;

    while (fast != 1) {
        slow = next(slow);
        fast = next(next(fast));
        if (slow == fast && slow != 1) {
            return false;
        }
    }

    return true;
}
```

</details>

### [287. Find the Duplicate Number (Medium)](/cpp/0287.find-the-duplicate-number/question.md)

`O(1)` space solutions:

- Use slow-fast pointers and view the numbers in the list as next index to travel.
  (Floyd's Tortoise and Hare Algorithm)
- Open a `bool [100001]` array to record visited numbers.

<details>
<summary>Code</summary>

```cpp
int findDuplicate(vector<int>& nums) {
    int slow = nums[0];
    int fast = nums[0];

    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);

    slow = nums[0];

    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }

    return fast;
}
```

</details>

## In-Place Reverse Linked List

### [206. Reverse Linked List (Easy)](/cpp/0206.reverse-linked-list/question.md)

<details>
<summary>Code</summary>

```cpp
ListNode* reverseList(ListNode* head) {
    ListNode *prev = nullptr, *curr = head;

    while (curr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}
```

</details>

### [92. Reverse Linked List II (Medium)](/cpp/0092.reverse-linked-list-ii/question.md)

<details>
<summary>Code</summary>

```cpp
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
```

</details>

### [24. Swap Nodes in Pairs (Medium)](/cpp/0024.swap-nodes-in-pairs/question.md)

<details>
<summary>Code</summary>

```cpp
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
```

</details>

## Monotonic Stack

### [496. Next Greater Element I (Easy)](/cpp/0496.next-greater-element-i/question.md)

Use a monotonic decrease stack to detect and store next greater element.

<details>
<summary>Code</summary>

```cpp
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    stack<int> s;
    unordered_map<int, int> table;
    // Preprocess nums2 with a monotonic stack
    // and store stack top's next greater value in the table.
    for (int num : nums2) {
        while (!s.empty() && num > s.top()) {
            table[s.top()] = num;
            s.pop();
        }
        s.push(num);
    }

    while (!s.empty()) {
        table[s.top()] = -1;
        s.pop();
    }

    vector<int> res;

    for (int num : nums1) {
        res.push_back(table[num]);
    }

    return res;
}
```

</details>

### [739. Daily Temperatures (Medium)](/cpp/0739.daily-temperatures/question.md)

Use a monotonic decrease stack to find the distance of warmer days and stack top.

<details>
<summary>Code</summary>

```cpp
vector<int> dailyTemperatures(vector<int>& temperatures) {
    stack<int> s;
    int n = temperatures.size();
    vector<int> res(n, 0);

    for (int i = 0; i < n; i++) {
        int t = temperatures[i];
        while (!s.empty() && t > temperatures[s.top()]) {
            res[s.top()] = i - s.top();
            s.pop();
        }
        s.push(i);
    }

    return res;
}
```

</details>

### [84. Largest Rectangle in Histogram (Hard)](/cpp/0084.largest-rectangle-in-histogram/question.md)

Use a monotonic increase stack.

<details>
<summary>Code</summary>

```cpp
int largestRectangleArea(vector<int>& heights) {
    stack<int> s;
    s.push(-1);
    int amax = 0;

    for (int i = 0; i < heights.size(); i++) {
        while (s.top() != -1 && heights[i] < heights[s.top()]) {
            int height = heights[s.top()];
            s.pop();
            int width = i - s.top() - 1;
            amax = max(amax, width * height);
        }
        s.push(i);
    }

    while (s.top() != -1) {
        int height = heights[s.top()];
        s.pop();
        int width = heights.size() - s.top() - 1;
        amax = max(amax, width * height);
    }

    return amax;
}
```

</details>

## Top-K Elements

### [215. Kth Largest Element in an Array (Medium)](/cpp/0215.kth-largest-element-in-an-array/question.md)

Use `nth_element`, which uses worst case linear time selection.

<details>
<summary>Code</summary>

```cpp
int findKthLargest(vector<int>& nums, int k) {
    // O(n) selecttion algorithm
    nth_element(nums.begin(), nums.begin() + k - 1, nums.end(),
                std::greater<>{});

    return nums[k - 1];
}
```

</details>

### [347. Top K Frequent Elements (Medium)](/cpp/0347.top-k-frequent-elements/question.md)

Use a priority queue.

<details>
<summary>Code</summary>

```cpp
vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2,
                                    int k) {
    vector<vector<int>> ans;
    priority_queue<pair<int, pair<int, int>>> pq;
    for (int i = 0; i < nums1.size(); i++) {
        for (int j = 0; j < nums2.size(); j++) {
            int sum = nums1[i] + nums2[j];
            if (pq.size() < k)
                pq.push({sum, {nums1[i], nums2[j]}});
            else if (sum < pq.top().first) {
                pq.pop();
                pq.push({sum, {nums1[i], nums2[j]}});
            } else if (sum >= pq.top().first) {
                break;
            }
        }
    }
    while (!pq.empty()) {
        ans.push_back({pq.top().second.first, pq.top().second.second});
        pq.pop();
    }
    return ans;
}
```

</details>

### [373. Find K Pairs with Smallest Sums (Medium)](/cpp/0373.find-k-pairs-with-smallest-sums/question.md)

Use a priority queue with at most size `k`.

<details>
<summary>Code</summary>

```cpp
vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2,
                                    int k) {
    vector<vector<int>> ans;
    priority_queue<pair<int, pair<int, int>>> pq;
    for (int i = 0; i < nums1.size(); i++) {
        for (int j = 0; j < nums2.size(); j++) {
            int sum = nums1[i] + nums2[j];
            if (pq.size() < k)
                pq.push({sum, {nums1[i], nums2[j]}});
            else if (sum < pq.top().first) {
                pq.pop();
                pq.push({sum, {nums1[i], nums2[j]}});
            } else if (sum >= pq.top().first) {
                break;
            }
        }
    }
    while (!pq.empty()) {
        ans.push_back({pq.top().second.first, pq.top().second.second});
        pq.pop();
    }
    return ans;
}
```

</details>

## Overlapping Intervals

### [56. Merge Intervals (Medium)](/cpp/0056.merge-intervals/question.md)

Sort the intervals by start time then push or merge to the result array.

<details>
<summary>Code</summary>

```cpp
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(),
            [](const vector<int>& a, const vector<int>& b) {
                return a[0] < b[0];
            });
    vector<vector<int>> res;

    for (vector<int>& i : intervals) {
        if (res.empty() || i[0] > res.back()[1]) {
            res.emplace_back(i);
        } else {
            int end = max(res.back()[1], i[1]);
            res.back()[1] = end;
        }
    }

    return res;
}
```

</details>

### [57. Insert Interval (Medium)](/cpp/0057.insert-interval/question.md)

Add the new interval to intervals, and sort the intervals by start time
then push or merge to the result array.

<details>
<summary>Code</summary>

```cpp
vector<vector<int>> insert(vector<vector<int>>& intervals,
                            vector<int>& newInterval) {
    intervals.emplace_back(newInterval);
    sort(intervals.begin(), intervals.end(),
            [](const vector<int>& a, const vector<int>& b) {
                return a[0] < b[0];
            });
    vector<vector<int>> res;

    for (vector<int>& i : intervals) {
        if (res.empty() || i[0] > res.back()[1]) {
            res.emplace_back(i);
        } else {
            int end = max(res.back()[1], i[1]);
            int start = min(res.back()[0], i[0]);

            res.back()[0] = start;
            res.back()[1] = end;
        }
    }

    return res;
}
```

</details>

### [435. Non-overlapping Intervals (Medium)](/cpp/0435.non-overlapping-intervals/question.md)

Sort the intervals by end time and count the non-overlapping ones.
Result is intervals size - non-overlapping intervals size.

<details>
<summary>Code</summary>

```cpp
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(),
            [](const vector<int>& a, const vector<int>& b) {
                return a[1] < b[1];
            });

    int count = 1, prev = 0;
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] >= intervals[prev][1]) {
            prev = i;
            count++;
        }
    }

    return intervals.size() - count;
}
```

</details>

## Modified Binary Search

### [33. Search in Rotated Sorted Array (Medium)](/cpp/0033.search-in-rotated-sorted-array/question.md)

Use the property of rotated sort to check which half is sorted and move the boundary.

<details>
<summary>Code</summary>

```cpp
int search(vector<int>& nums, int target) {
    int i = 0, j = nums.size() - 1;
    // rotate sorted: s[0] > s[n-1], s[pivot] is the highest point
    while (i <= j) {
        int mid = i + ((j - i) / 2);
        if (nums[mid] == target) {
            // Case 1: Found target
            return mid;
        } else if (nums[mid] >= nums[i]) {
            // Case 2: mid's left is sorted.
            if (target >= nums[i] && target < nums[mid]) {
                // target is on left subarray
                j = mid - 1;
            } else {
                // target is on right subarray
                i = mid + 1;
            }
        } else {
            // Case 3: mid's right is sorted.
            if (target <= nums[j] && target > nums[mid]) {
                // target is on right subarray
                i = mid + 1;
            } else {
                // target is on left subarray
                j = mid - 1;
            }
        }
    }

    return -1;
}
```

</details>

### [153. Find Minimum in Rotated Sorted Array (Medium)](/cpp/0153.find-minimum-in-rotated-sorted-array/question.md)

Use the property of rotated sort to find the minimal.

<details>
<summary>Code</summary>

```cpp
int findMin(vector<int>& nums) {
    // Search the center
    int i = 1, j = nums.size() - 2;

    while (i <= j) {
        int mid = i + ((j - i) / 2);
        if (nums[mid - 1] > nums[mid] && nums[mid + 1] > nums[mid]) {
            // Case 1: found minimal
            return nums[mid];
        } else if (nums[mid] > nums[0]) {
            // Case 2: mid is at the left of pivot
            i = mid + 1;
        } else {
            // Case 3: mid is at the right of pivot.
            j = mid - 1;
        }
    }
    // Not rotate sorted.
    return min(nums[0], nums[nums.size() - 1]);
}
```

</details>

### [240. Search a 2D Matrix II (Medium)](/cpp/0240.search-a-2d-matrix-ii/question.md)

Walk from bottom left: `matrix[r][c] > t => r--`, `matrix[r][c] < t => c++`

<details>
<summary>Code</summary>

```cpp
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
```

</details>

## Binary Tree Traversal

### [257. Binary Tree Paths (Easy)](/cpp/0257.binary-tree-paths/question.md)

DFS post-order explore

<details>
<summary>Code</summary>

```cpp
void dfs(TreeNode* node, string path, vector<string>& res) {
    if (node) {
        path += to_string(node->val);
        if (!node->left && !node->right) {
            res.push_back(path);
        } else {
            path += "->";
            dfs(node->left, path, res);
            dfs(node->right, path, res);
        }
    }
}

vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> res;
    string path;

    dfs(root, path, res);

    return res;
}
```

</details>

### [230. Kth Smallest Element in a BST (Medium)](/cpp/0230.kth-smallest-element-in-a-bst/question.md)

DFS in-order traversal to build a list and get `k-1`th element from that list.

<details>
<summary>Code</summary>

```cpp
void dfs(TreeNode* node, vector<int>& path) {
    if (node) {
        dfs(node->left, path);
        path.push_back(node->val);
        dfs(node->right, path);
    }
}

int kthSmallest(TreeNode* root, int k) {
    vector<int> path;

    dfs(root, path);

    if (path.size() >= k) {
        return path[k - 1];
    } else {
        return -1;
    }
}
```

</details>

### [124. Binary Tree Maximum Path Sum (Hard)](/cpp/0124.binary-tree-maximum-path-sum/question.md)

DFS post-order traversal. Remember the result is to choose a branch.

<details>
<summary>Code</summary>

```cpp
int dfs(TreeNode* node, int& max_sum) {
    if (!node) {
        return 0;
    }

    int lgain = max(dfs(node->left, max_sum), 0);
    int rgain = max(dfs(node->right, max_sum), 0);

    max_sum = max(max_sum, node->val + lgain + rgain);

    return max(node->val + lgain, node->val + rgain);
}

int maxPathSum(TreeNode* root) {
    int max_sum = numeric_limits<int>::min();

    dfs(root, max_sum);

    return max_sum;
}
```

</details>

## DFS & BFS

### [133. Clone Graph (Medium)](/cpp/0133.clone-graph/question.md)

DFS or BFS explore graph and clone the nodes

<details>
<summary>Code</summary>

```cpp
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
```

</details>

### [113. Path Sum II (Medium)](/cpp/0113.path-sum-ii/question.md)

DFS explore until leaf then compare sum.

<details>
<summary>Code</summary>

```cpp
void dfs(TreeNode* node, int sum, vector<int>& path,
         vector<vector<int>>& result, const int& target) {
    if (!node) {
        return;
    }

    sum += node->val;
    path.push_back(node->val);

    if (!node->left && !node->right && sum == target) {
        result.emplace_back(path);
    } else {
        dfs(node->left, sum, path, result, target);
        dfs(node->right, sum, path, result, target);
    }

    path.pop_back();
    sum -= node->val;

    return;
}

class Solution {
  public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<int> path;
        vector<vector<int>> res;

        dfs(root, 0, path, res, targetSum);

        return res;
    }
};
```

</details>

### [210. Course Schedule II (Medium)](/cpp/0210.course-schedule-ii/question.md)

Topological sort from **every** node that has in-degree of 0 in `[0, numCourses-1]`,
including unused ones.

<details>
<summary>Code</summary>

```cpp
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
```

</details>

### [102. Binary Tree Level Order Traversal (Medium)](/cpp/0102.binary-tree-level-order-traversal/question.md)

BFS on binary trees. Remember to use level fashion loop..

<details>
<summary>Code</summary>

```cpp
class Solution {
  public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root)
            return {};
        queue<TreeNode*> q;
        vector<vector<int>> res;

        q.push(root);

        while (!q.empty()) {
            int n = q.size();
            vector<int> nodes;
            for (int i = 0; i < n; i++) {
                TreeNode* node = q.front();
                nodes.emplace_back(node->val);

                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);

                q.pop();
            }
            res.emplace_back(nodes);
        }

        return res;
    }
};
```

</details>

### [994. Rotting Oranges (Medium)](/cpp/0994.rotting-oranges/question.md)

BFS explore the grid and stamp time stamps.
The answer will be maximum timestamp - 2 or
-1 if any fresh orange left.

<details>
<summary>Code</summary>

```cpp
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
```

</details>

### [127. Word Ladder (Hard)](/cpp/0127.word-ladder/question.md)

Double-ended BFS that returns the level when meet in the middle.
Edge requirement: hamming distance of 1.

<details>
<summary>Code</summary>

```cpp
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
```

</details>

## Matrix Traversal

### [733. Flood Fill (Easy)](/cpp/0733.flood-fill/question.md)

Remember to store the source color before writing image.
Rest is grid BFS on 4 directions.

<details>
<summary>Code</summary>

```cpp
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
```

</details>

### [200. Number of Islands (Medium)](/cpp/0200.number-of-islands/question.md)

Find a land first then use grid BFS to mark connected lands to 0.

<details>
<summary>Code</summary>

```cpp
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
```

</details>

### [130. Surrounded Regions (Medium)](/cpp/0130.surrounded-regions/question.md)

BFS from all open cell from the edge and apply special marker 'E'.
After that change left 'O' to 'X' (unreachable to edge) and 'E' to 'O'.

<details>
<summary>Code</summary>

```cpp
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
```

</details>
## Backtracking

## DP Patterns
