//
//  main.cpp
//  partitioner
//
//  Created by Peter Sun on 1/31/21.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using std::vector;
using std::string;

class Solution {
public:
  int sumVec(vector<int> valVec) {
    int sum = 0;
    for (auto val : valVec) sum += val;
    return sum;
  }

  bool compareSubsets(vector<int> subset1, vector<int> subset2) {
    if (sumVec(subset1) == sumVec(subset2)) {
      std::cout << "Explanation: The array can be partitioned as ";
      string subsets = "[";
      for (auto val : subset1) subsets = subsets + std::to_string(val) + ",";
      subsets.pop_back();
      subsets += "] and [";
      for (auto val : subset2) subsets = subsets + std::to_string(val) + ",";
      subsets.pop_back();
      std::cout << subsets << "].\n";
      return true;
    }
    return false;
  }
  
  // Generally, subset1 will start empty and subset2 will start with all the values
  bool recursePartition(vector<int> subset1, vector<int> subset2, int currIdx, bool resetIdx, bool& evenPartition) {
    if (evenPartition) return true;
    if (resetIdx) currIdx = 0;
    if (subset2.empty() || currIdx >= subset2.size()) return false;

    // See if subset with currIdx can be partitioned evenly
    subset1.push_back(subset2[currIdx]);
    subset2.erase(subset2.begin() + currIdx);
    if (!evenPartition) evenPartition = compareSubsets(subset1, subset2);
    // Recurse with subset1 having the currIdx
    recursePartition(subset1, subset2, currIdx, true, evenPartition);

    // Put the currIdx value back to subset2 and try without the currIdx
    subset2.insert(subset2.begin() + currIdx, subset1.back());
    subset1.pop_back();
    if (!evenPartition) evenPartition = compareSubsets(subset1, subset2);
    recursePartition(subset1, subset2, currIdx + 1, false, evenPartition);

    return evenPartition;
  }
  
  // ALGORITHM
  // Create subsets depending on whether the first subset has the current index or not
  // If adding the current index:
    // Push the current index value of subset2 into subset1 [O(1)]
    // Delete the current index value from subset1 [O(log(N))]
    // Compare sum of subsets and see if they are equal
    // Recurse by resetting current index to 0
  // If not adding the current index:
    // Push last value of subset1 back to current index location within subset2 [O(log(N))]
    // Delete the last value in subset1 [O(1)]
    // Compare sum of subsets and see if they are equal
    // Increment current index by 1
    // Recurse by incrementing current index by 1
  // The overall complexity should be O(Nlog(N))
  bool canPartition(vector<int>& nums) {
    vector<int> sub1IdxVec = vector<int>();
    bool evenPartition = false;
    return recursePartition(vector<int>(), nums, 0, true, evenPartition);
  }
};

int main(int argc, const char * argv[]) {
  Solution solution;
  std::cout << "Input: ";
  string tmp;
  string numStr;
  vector<int> nums = vector<int>();
  std::cin >> tmp >> tmp >> numStr;
  numStr.erase(numStr.begin());
  numStr.pop_back();
  std::stringstream ss(numStr);
  int num;
  while (ss >> num) {
    nums.push_back(num);
    if (ss.peek() == ',') ss.ignore();
  }
  if (!solution.canPartition(nums)) std::cout << "The array cannot be partitioned into equal sum subsets.\n";
  return 0;
}
