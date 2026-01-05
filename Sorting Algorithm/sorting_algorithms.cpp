#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 BASIC SORTING ALGORITHMS
====================================================
*/

/*
-------------------------
1) BUBBLE SORT
Concept:
- Adjacent elements compare
- Bigger element goes to right like a bubble
Time:
- Worst: O(n^2)
- Best: O(n) (already sorted)
*/
void bubbleSort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        // If no swap happened, array already sorted
        if (!swapped) break;
    }
}

/*
-------------------------
2) SELECTION SORT
Concept:
- Find minimum element
- Put it at the beginning
Time:
- Always O(n^2)
*/
void selectionSort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[minIndex])
                minIndex = j;
        }
        swap(a[i], a[minIndex]);
    }
}

/*
-------------------------
3) INSERTION SORT
Concept:
- Like arranging playing cards
- Left part is always sorted
Time:
- Worst: O(n^2)
- Best: O(n)
*/
void insertionSort(vector<int>& a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;

        // Shift elements greater than key
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

/*
====================================================
 INTERMEDIATE SORTING ALGORITHMS
====================================================
*/

/*
-------------------------
4) MERGE SORT
Concept:
- Divide and Conquer
- Divide array into halves
- Merge sorted halves
Time:
- O(n log n)
Space:
- O(n)
*/

void mergeArray(vector<int>& a, int l, int m, int r) {
    vector<int> left(a.begin() + l, a.begin() + m + 1);
    vector<int> right(a.begin() + m + 1, a.begin() + r + 1);

    int i = 0, j = 0, k = l;

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }

    while (i < left.size()) a[k++] = left[i++];
    while (j < right.size()) a[k++] = right[j++];
}

void mergeSort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    mergeArray(a, l, m, r);
}

/*
-------------------------
5) QUICK SORT
Concept:
- Choose pivot
- Smaller left, bigger right
Time:
- Average: O(n log n)
- Worst: O(n^2)
*/

int partitionArray(vector<int>& a, int l, int r) {
    int pivot = a[r];      // last element as pivot
    int i = l - 1;

    for (int j = l; j < r; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
}

void quickSort(vector<int>& a, int l, int r) {
    if (l < r) {
        int p = partitionArray(a, l, r);
        quickSort(a, l, p - 1);
        quickSort(a, p + 1, r);
    }
}

/*
====================================================
 ADVANCED SORTING ALGORITHMS
====================================================
*/

/*
-------------------------
6) HEAP SORT
Concept:
- Build max heap
- Swap root with last
- Heapify again
Time:
- O(n log n)
Space:
- O(1)
*/

void heapify(vector<int>& a, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;
    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(vector<int>& a) {
    int n = a.size();

    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    // Extract elements
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

/*
-------------------------
7) COUNTING SORT
Concept:
- Count frequency of elements
- Works when range is small
Time:
- O(n + k)
*/
void countingSort(vector<int>& a) {
    int mx = *max_element(a.begin(), a.end());
    vector<int> count(mx + 1, 0);

    for (int x : a) count[x]++;

    int idx = 0;
    for (int i = 0; i <= mx; i++) {
        while (count[i]--) {
            a[idx++] = i;
        }
    }
}

/*
-------------------------
8) RADIX SORT
Concept:
- Sort digit by digit
- Uses counting sort internally
*/

void countingSortDigit(vector<int>& a, int exp) {
    int n = a.size();
    vector<int> output(n);
    vector<int> count(10, 0);

    for (int i = 0; i < n; i++)
        count[(a[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int idx = (a[i] / exp) % 10;
        output[--count[idx]] = a[i];
    }

    a = output;
}

void radixSort(vector<int>& a) {
    int mx = *max_element(a.begin(), a.end());
    for (int exp = 1; mx / exp > 0; exp *= 10)
        countingSortDigit(a, exp);
}

/*
====================================================
 MAIN FUNCTION (TEST ANY SORT)
====================================================
*/

int main() {
    int n;
    cin >> n;              // size of array

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];       // input elements
    }

    /*
    ==============================
    Choose ONE sorting algorithm
    ==============================
    */

    // bubbleSort(a);
    // selectionSort(a);
    // insertionSort(a);
    // mergeSort(a, 0, n - 1);
    // quickSort(a, 0, n - 1);
    // heapSort(a);
    // countingSort(a);
    // radixSort(a);

    /*
    ==============================
    Output sorted array
    ==============================
    */
    for (int x : a) {
        cout << x << " ";
    }

    cout << endl;
    return 0;
}
