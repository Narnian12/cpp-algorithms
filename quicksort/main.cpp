/// QuickSort Algorithm
/// Complexity:
  /// Worse-case: O(n^2)
  /// Average-case: O(nlog(n))
/// Works well on smaller arrays
/// Less storage space requirement than mergesort

#include <iostream>
#include <vector>

using namespace std;

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

// Use rightmost index as pivot
void QuickSort(vector<int> &unsorted, int low, int pivot) {
  if (pivot - low == 0) return;
  // Partition has two elements, check if they are sorted or if they need to swap
  if (pivot - low == 1) {
    if (unsorted[low] > unsorted[pivot]) swap(&unsorted[low], &unsorted[pivot]);
    return;
  }
  int newPivot = -1;
  int swapIdx = -1;
  for (int i = low; i < pivot; ++i) {
    if (unsorted[i] < unsorted[pivot]) {
      swapIdx = i;
      // Swap the lower value to the left until it is further left than all values greater than pivot
      while (swapIdx - 1 >= 0 && unsorted[swapIdx - 1] > unsorted[pivot]) {
        swap(&unsorted[swapIdx - 1], &unsorted[swapIdx]);
        newPivot = swapIdx;
        --swapIdx;
      }
    }
  }
  // swapIdx is the rightmost edge of values lower than pivot, so set the newPivot to the leftmost edge of values greater than pivot
  newPivot = swapIdx + 1;
  swap(&unsorted[newPivot], &unsorted[pivot]);
  if (pivot - low > 2) {
    QuickSort(unsorted, 0, newPivot - 1);
    QuickSort(unsorted, newPivot + 1, unsorted.size() - 1);
  }
}

int main() {
  vector<int> vect { 50, 23, 9, 18, 61, 10, 32 };
  QuickSort(vect, 0, vect.size() -1 );
  for (auto x : vect) {
    cout << x << " ";
  }
}