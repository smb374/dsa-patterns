# dsa-patterns

LeetCode DSA patterns

## Prefix Sum

### [303. Range Sum Query - Immutable (Easy)](/cpp/0303.range-sum-query-immutable/question.md)

Build a prefix sum array such that
`sum[i, j] = sum[0, j] - sum[0, i - 1]`

### [525. Contiguous Array (Medium)](/cpp/0525.contiguous-array/question.md)

Gradual prefix sum. Note that we need to interpret 0 as -1.

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

### [560. Subarray Sum Equals K (Medium)](/cpp/0560.subarray-sum-equals-k/question.md)

Gradual prefix sum. Note that we should match `k` in building loop
before adding `table[sum]`, otherwise it could match on extras
when `k = 0` if we choose other approach.

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

## Two Pointers

## Sliding Window

## Fast & Slow Pointers

## In-Place Reverse Linked List

## Monotonic Stack

## Top-K Elements

## Overlapping Intervals

## Modified Binary Search

## Binary Tree Traversal

## DFS

## BFS

## Matrix Traversal

## Backtracking

## DP Patterns
