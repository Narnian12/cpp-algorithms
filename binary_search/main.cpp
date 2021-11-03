#include <iostream>
#include <vector>>

using namespace std;

int binarySearch(vector<int> vec, int left, int right, int target) {
  if (left > right) return -1;
  int middle = left + ((right - left) / 2);
  // Remove the middle index from recursive searches
  if (target < vec[middle]) binarySearch(vec, left, middle - 1, target);
  else if (target > vec[middle]) binarySearch(vec, middle + 1, right, target);
  else return middle;
}

int main() {
  vector<int> vec { 1, 3, 5, 9, 10, 14 };
  cout << binarySearch(vec, 0, vec.size() - 1, 5); // 2
}
