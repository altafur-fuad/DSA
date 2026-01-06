#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 SEARCHING ALGORITHMS (BEGINNER → ADVANCED)
====================================================
*/

/*
-------------------------
1) LINEAR SEARCH
Concept:
- Check elements one by one
- Works on both sorted and unsorted array
Time Complexity:
- O(n)
*/
int linearSearch(vector<int>& a, int target) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == target)
            return i;
    }
    return -1;
}

/*
-------------------------
2) BINARY SEARCH (ITERATIVE)
Concept:
- Only works on sorted array
- Divide search space into half
Time Complexity:
- O(log n)
*/
int binarySearchIterative(vector<int>& a, int target) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == target)
            return mid;
        else if (a[mid] < target)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}

/*
-------------------------
3) BINARY SEARCH (RECURSIVE)
*/
int binarySearchRecursive(vector<int>& a, int l, int r, int target) {
    if (l > r) return -1;

    int mid = l + (r - l) / 2;
    if (a[mid] == target)
        return mid;
    else if (a[mid] < target)
        return binarySearchRecursive(a, mid + 1, r, target);
    else
        return binarySearchRecursive(a, l, mid - 1, target);
}

/*
-------------------------
4) JUMP SEARCH
Concept:
- Sorted array
- Jump by sqrt(n)
- Then linear search inside block
Time Complexity:
- O(√n)
*/
int jumpSearch(vector<int>& a, int target) {
    int n = a.size();
    int step = sqrt(n);
    int prev = 0;

    while (prev < n && a[min(step, n) - 1] < target) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    for (int i = prev; i < min(step, n); i++) {
        if (a[i] == target)
            return i;
    }
    return -1;
}

/*
-------------------------
5) INTERPOLATION SEARCH
Concept:
- Works best on uniformly distributed sorted array
- Uses estimated position formula
Time Complexity:
- Best: O(log log n)
- Worst: O(n)
*/
int interpolationSearch(vector<int>& a, int target) {
    int low = 0, high = a.size() - 1;

    while (low <= high && target >= a[low] && target <= a[high]) {
        if (low == high) {
            if (a[low] == target) return low;
            return -1;
        }

        int pos = low + 
            ((double)(high - low) / (a[high] - a[low])) *
            (target - a[low]);

        if (a[pos] == target)
            return pos;
        else if (a[pos] < target)
            low = pos + 1;
        else
            high = pos - 1;
    }
    return -1;
}

/*
-------------------------
6) EXPONENTIAL SEARCH
Concept:
- Find range where element may exist
- Then apply binary search
Time Complexity:
- O(log n)
*/
int exponentialSearch(vector<int>& a, int target) {
    int n = a.size();
    if (a[0] == target) return 0;

    int i = 1;
    while (i < n && a[i] <= target)
        i *= 2;

    return binarySearchRecursive(a, i / 2, min(i, n - 1), target);
}

/*
====================================================
 STL SEARCHING FUNCTIONS
====================================================
*/

void stlSearching(vector<int>& a, int target) {
    // binary_search → returns true/false
    if (binary_search(a.begin(), a.end(), target))
        cout << "STL binary_search: FOUND\n";
    else
        cout << "STL binary_search: NOT FOUND\n";

    // lower_bound → first position >= target
    auto lb = lower_bound(a.begin(), a.end(), target);
    if (lb != a.end())
        cout << "lower_bound index: " << lb - a.begin() << "\n";

    // upper_bound → first position > target
    auto ub = upper_bound(a.begin(), a.end(), target);
    if (ub != a.end())
        cout << "upper_bound index: " << ub - a.begin() << "\n";
}

/*
====================================================
 MAIN FUNCTION (USER INPUT)
====================================================
*/

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int target;
    cin >> target;

    /*
    IMPORTANT:
    - Binary, Jump, Interpolation, Exponential search
      REQUIRE SORTED ARRAY
    */
    sort(a.begin(), a.end());

    // Uncomment ONE search method to test

    // cout << linearSearch(a, target) << endl;
    // cout << binarySearchIterative(a, target) << endl;
    // cout << binarySearchRecursive(a, 0, n - 1, target) << endl;
    // cout << jumpSearch(a, target) << endl;
    // cout << interpolationSearch(a, target) << endl;
    // cout << exponentialSearch(a, target) << endl;

    // STL searching demo
    stlSearching(a, target);

    return 0;
}
