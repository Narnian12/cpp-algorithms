#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;


vector<vector<string>> groupAnagrams(vector<string>& strs) {
  map<string, vector<int>> anagrams;
  vector<vector<string>> anagramGroups;
  for (int i = 0; i < strs.size(); ++i) {
    auto sortedWord = strs[i];
    sort(sortedWord.begin(), sortedWord.end());
    if (anagrams.count(sortedWord) > 0) {
      anagrams[sortedWord].emplace_back(i);
    }
    else anagrams[sortedWord] = { i };
  }

  for (auto const& [key, val] : anagrams) {
    vector<string> anagram;
    for (auto idx : val) anagram.emplace_back(strs[idx]);
    anagramGroups.emplace_back(anagram);
  }

  return anagramGroups;
}

int main() {
  vector<string> words = { "eat", "tea", "tan", "ate", "nat", "bat"};
  vector<vector<string>> anagrams = groupAnagrams(words);
  for (auto grams : anagrams) {
    for (auto word : grams) cout << word << " "; // bat \neat tea ate \ntan nat 
    cout << "\n";
  }
  return 0;
}
