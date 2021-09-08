//
//  main.cpp
//  cookies
//
//  Created by Peter Sun on 3/19/21.
//

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class Solution {
public:
  string determineDirection(int currVal, int prevVal) {
    string direction = currVal - prevVal > 0 ? "Positive" : "Negative";
    direction = currVal - prevVal == 0 ? "Neutral" : direction;
    return direction;
  }
  
  // directionEnd is i - 1
  void addCookies(vector<int>& cookies, int directionStart, int directionEnd, string direction) {
    int cookieVal = 1;
    if (direction == "Negative") cookieVal = directionEnd - directionStart + 1;
    if (direction == "Neutral") {
      for (int j = directionStart + 1; j <= directionEnd; ++j) cookies[j] = cookieVal;
    }
    else if (direction == "Negative") {
      if (cookies[directionStart] < cookieVal) cookies[directionStart] = cookieVal;
      --cookieVal;
      for (int j = directionStart + 1; j <= directionEnd; ++j) {
        cookies[j] = cookieVal;
        --cookieVal;
      }
    }
    else {
      for (int j = directionStart; j <= directionEnd; ++j) {
        cookies[j] = cookieVal;
        ++cookieVal;
      }
    }
  }
  
  int cookie(vector<int>& ratings) {
    // Case 1
    if (ratings.size() == 1) return 1;
    // Case 2
    if (ratings.size() == 2) {
      if (ratings[1] - ratings[0] > 0 || ratings[1] - ratings[0] < 0) return 3;
      else return 2;
    }
    
    vector<int> cookies(ratings.size(), 0);
    int prevVal = ratings[0];
    int currVal = ratings[1];
    string prevDirection = determineDirection(currVal, prevVal);
    string currDirection = determineDirection(currVal, prevVal);
    int directionStart = 0;
    
    prevVal = ratings[1];
    for (int i = 2; i < ratings.size(); ++i) {
      currVal = ratings[i];
      currDirection = determineDirection(currVal, prevVal);
      // When direction is positive, generally increment number of cookies per rating
      // When direction is negative, generally decrement number of cookies per rating
      // and update the index right before the slope with 1 higher than the max number in this decrement
      // When direction is neutral, add 1 cookie (besides first neutral directional value after index 0)
      if (currDirection != prevDirection) {
        addCookies(cookies, directionStart, i - 1, prevDirection);
        directionStart = i - 1;
        prevDirection = currDirection;
      }
      // At the last index, do the remaining work
      if (i == ratings.size() - 1) {
        addCookies(cookies, directionStart, i, currDirection);
        break;
      }
      prevVal = currVal;
    }
    int totalCookies = 0;
    for (auto cookie: cookies) totalCookies += cookie;
    return totalCookies;
  }
};

int main(int argc, const char * argv[]) {
  vector<int> ratings = vector<int>();
  string tmp;
  string input;
  std::cout << "Input: ";
  std::cin >> tmp >> tmp >> input;
  string ratingVal = "";
  for (auto chr : input) {
    if (chr == '[') continue;
    else if (chr == ',') {
      ratings.push_back(std::stoi(ratingVal));
      ratingVal = "";
      continue;
    }
    else if (chr == ']') {
      ratings.push_back(std::stoi(ratingVal));
      break;
    }
    ratingVal += chr;
  }
  Solution solution;
  std::cout << "Output: " << solution.cookie(ratings) << "\n";
  return 0;
}
