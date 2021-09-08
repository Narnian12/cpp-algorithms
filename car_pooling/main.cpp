//
//  main.cpp
//  car_pooling
//
//  Created by Peter Sun on 3/11/21.
//

#include <iostream>
#include <vector>

using std::vector;
using std::string;

class Solution {
public:
  // PROPOSED ALGORITHM
  // - Iterate and determine the furthest east position (highest value of trips[i][2])
  // - Iterate again, adding from value in trips[i][1] up to value in trips[i][2]-1
  // - Once any point in the vector we are making exceeds capacity, return false
  // - If we can go through everything, return true
  bool carPooling(vector<vector<int>>& trips, int capacity) {
    int furthestEndLocation = 0;
    for (auto trip : trips) {
      if (trip[2] > furthestEndLocation) furthestEndLocation = trip[2];
    }
    vector<int> passengers(furthestEndLocation, 0);
    for (auto trip : trips) {
      for (int i = trip[1]; i < trip[2]; ++i) {
        passengers[i] += trip[0];
        if (passengers[i] > capacity) return false;
      }
    }
    return true;
  }
};

void addValue(vector<int>& values, string& value) {
  if (value.length() > 0) {
    values.emplace_back(std::stoi(value));
    value = "";
  }
}

int main(int argc, const char * argv[]) {
  Solution solution;
  std::cout << "Input: ";
  string tmp;
  string tripsStr;
  int capacity = 0;
  vector<vector<int>> trips = vector<vector<int>>();
  vector<int> values = vector<int>();
  string value = "";
  std::cin >> tmp >> tmp >> tripsStr >> tmp >> tmp >> capacity;
  tripsStr.erase(0, 2);
  for (auto tripChr : tripsStr) {
    if (tripChr == '[') continue;
    else if (tripChr == ',') {
      addValue(values, value);
      continue;
    }
    else if (tripChr == ']') {
      addValue(values, value);
      if (values.size() == 3) {
        trips.emplace_back(values);
        values.clear();
      }
      continue;
    }
    value += tripChr;
  }
  bool canCarpool = solution.carPooling(trips, capacity);
  string carpooled = canCarpool ? "true" : "false";
  std::cout << "Output: " << carpooled << "\n";
  return 0;
}
