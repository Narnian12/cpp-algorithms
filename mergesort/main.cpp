/// MergeSort Algorithm
/// Complexity:
  /// Worse-case: O(nlog(n))
  /// Average-case: O(nlog(n))
/// Works well on any size of array
/// More storage space requirement than mergesort

#include <iostream>
#include <vector>

using namespace std;

void updateVecVal(vector<int>& vec, int& vecIdx, vector<int>& subVec, int& subVecIdx) {
  vec[vecIdx] = subVec[subVecIdx];
  ++subVecIdx;
  ++vecIdx;
}

void merge(vector<int>& vec, int left, int mid, int right) {
  // Starting index in vec once subarrays are added back in
  int mergeIdx = left;

  vector<int> leftSubVec;
  vector<int> rightSubVec;

  // Left vector contains [left, mid]
  for (int i = left; i <= mid; ++i) leftSubVec.emplace_back(vec[i]);
  // Right vector contains (mid, right]
  for (int i = mid + 1; i <= right; ++i) rightSubVec.emplace_back(vec[i]);

  // Starting indices for subarrays
  int leftSubVecIdx = 0;
  int rightSubVecIdx = 0;

  // Push values from left to right within vec
  while (leftSubVecIdx < leftSubVec.size() && rightSubVecIdx < rightSubVec.size()) {
    // Left val is less than right val, push left val into 
    if (leftSubVec[leftSubVecIdx] <= rightSubVec[rightSubVecIdx]) updateVecVal(vec, mergeIdx, leftSubVec, leftSubVecIdx);
    else updateVecVal(vec, mergeIdx, rightSubVec, rightSubVecIdx);
  }
  // Push the rest of the values from left and right subarrays
  for (int i = leftSubVecIdx; i < leftSubVec.size(); ++i) updateVecVal(vec, mergeIdx, leftSubVec, leftSubVecIdx);
  for (int i = rightSubVecIdx; i < rightSubVec.size(); ++i) updateVecVal(vec, mergeIdx, rightSubVec, rightSubVecIdx);
}

void mergeSort(vector<int>& vec, int begin, int end) {
  if (end <= begin) return;
  // Grab the floor
  int mid = begin + (end - begin) / 2;
  mergeSort(vec, begin, mid);
  mergeSort(vec, mid + 1, end);
  merge(vec, begin, mid, end);
}

int main() {
  vector<int> vec { 38, 27, 43, 3, 9, 82, 10 };
  mergeSort(vec, 0, vec.size() - 1);
  for (auto elem : vec) cout << elem << " "; // [3 9 10 27 38 43 82]
  return 0;
}