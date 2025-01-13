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
