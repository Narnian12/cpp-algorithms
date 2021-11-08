#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct Letter {
public:
  Letter(int idx_in, bool vowel_in) {
    idx = idx_in;
    vowel = vowel_in;
  }
  int idx;
  bool vowel;
};

bool isVowel(char c) {
  return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

// See if we can do the max subarray but keep the indices as well
string findSubstring(string s, int k) {
  deque<Letter> letters;
  int localMaxIdx = 0;
  int globalMaxIdx = 0;
  int localMax = 0;
  int globalMax = 0;
  for (int i = 0; i < s.size(); ++i) {
    char currChar = s[i];
    if (i - localMaxIdx >= k) {
      // Maximum size of subarray reached, pop out front
      if (letters.front().vowel) --localMax;
      letters.pop_front();
      ++localMaxIdx;
    }
    letters.emplace_back(Letter(i, isVowel(currChar)));
    if (letters.back().vowel) ++localMax;
    if (localMax > globalMax) {
      globalMaxIdx = localMaxIdx;
      globalMax = localMax;
    }
  }
  return s.substr(globalMaxIdx, k);
}

int main() {
  cout << findSubstring("azerdii", 5);
  return 0;
}