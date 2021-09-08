/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode() : val(0), next(nullptr) {}
*     ListNode(int x) : val(x), next(nullptr) {}
*     ListNode(int x, ListNode *next) : val(x), next(next) {}
* };
*/

#include <iostream>
#include <vector>
#include <string>

using std::vector;

class ListNode {
  public:
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
  };

class Solution {
public:
  // Helper function for generateValuesVec
  // Appends valueVec with integers from the ListNode pointer node
  void createVecFromListNode(vector<int> &valueVec, ListNode* node) {
    if (node == nullptr) return;
    valueVec.push_back(node->val);
    createVecFromListNode(valueVec, node->next);
  }

  // First operation within mergeKLists
  // Returns a vector of ints from a vector of ListNode pointers
  vector<int> generateValuesVec(vector<ListNode*>& lists) {
    vector<int> allValuesVec = vector<int>();
    for (auto linkedList : lists) createVecFromListNode(allValuesVec, linkedList);
    return allValuesVec;
  }
  
  // Second operation within mergeKLists
  // Takes in a vector of ints and generates a vector of vector of ints with two values in each inner vector
  // unless there is an odd number of values
  void createFirstDuoSplit(vector<int> unsortedMergedLists, vector<vector<int>>& initialSplitLists, int currIdx) {
    // If the vector is odd, the last vector will have a single value
    if (currIdx + 1 == unsortedMergedLists.size()) {
      initialSplitLists.push_back({unsortedMergedLists[currIdx]});
      return;
    }
    // Sort here
    if (unsortedMergedLists[currIdx] < unsortedMergedLists[currIdx + 1]) {
      initialSplitLists.push_back({unsortedMergedLists[currIdx], unsortedMergedLists[currIdx + 1]});
    }
    else {
      initialSplitLists.push_back({unsortedMergedLists[currIdx + 1], unsortedMergedLists[currIdx]});
    }
    if (currIdx + 1 == unsortedMergedLists.size() - 1) return;
    createFirstDuoSplit(unsortedMergedLists, initialSplitLists, currIdx + 2);
  }
  
  // Helper function for recurseMergeSort
  // Merges two sorted vectors into one sorted vector
  // Iterates through both vectors and whichever values is less than (or equal!) add to a new vector
  vector<int> mergeTwoSortedVec(vector<int> firstVec, vector<int> secondVec) {
    int firstIter = 0;
    int secondIter = 0;
    vector<int> mergedVec = vector<int>();
    // Keep iterating until both vectors are complete
    while (firstIter < firstVec.size() || secondIter < secondVec.size()) {
      // Once firstVec completes, fill the rest of mergedVec with the rest of secondVec
      if (firstIter == firstVec.size()) {
        while (secondIter < secondVec.size()) mergedVec.push_back(secondVec[secondIter++]);
        continue;
      }
      // Once secondVec completes, fill the rest of mergedVec with the rest of firstVec
      if (secondIter == secondVec.size()) {
        while (firstIter < firstVec.size()) mergedVec.push_back(firstVec[firstIter++]);
        continue;
      }
      if (firstVec[firstIter] < secondVec[secondIter]) mergedVec.push_back(firstVec[firstIter++]);
      else if (firstVec[firstIter] > secondVec[secondIter]) mergedVec.push_back(secondVec[secondIter++]);
      else {
        mergedVec.push_back(firstVec[firstIter++]);
        mergedVec.push_back(secondVec[secondIter++]);
      }
    }
    return mergedVec;
  }
  
  // Helper function for mergeSplitLists
  void recurseMergeSort(vector<vector<int>> initialSplitLists, vector<vector<int>>& sortedMergedLists, int currIdx) {
    if (currIdx >= initialSplitLists.size()) return;
    while (currIdx < initialSplitLists.size()) {
      // Odd number of vectors in initialSplitLists
      if (currIdx == initialSplitLists.size() - 1) {
        if (sortedMergedLists.empty()) {
          sortedMergedLists.push_back(initialSplitLists.front());
          break;
        }
        vector<int> mergedVec = mergeTwoSortedVec(sortedMergedLists.back(), initialSplitLists.back());
        sortedMergedLists.pop_back();
        sortedMergedLists.push_back(mergedVec);
        break;
      }
      vector<int> mergedVec = mergeTwoSortedVec(initialSplitLists[currIdx], initialSplitLists[currIdx + 1]);
      sortedMergedLists.push_back(mergedVec);
      currIdx += 2;
    }
  }
  
  // Third operation within mergeKLists
  // Recursive operation to combine the initial duo split vectors into one fully sorted vector
  void mergeSplitLists(vector<vector<int>> initialSplitLists, vector<vector<int>>& sortedMergedLists) {
    while (sortedMergedLists.size() != 1) {
      sortedMergedLists.clear();
      recurseMergeSort(initialSplitLists, sortedMergedLists, 0);
      initialSplitLists.clear();
      initialSplitLists = sortedMergedLists;
    }
  }
  
  // Helper function to generate linked list from a singular ListNode and a vector of values
  void generateLinkedList(ListNode* previousNode, vector<int> values, int currIdx) {
    if (currIdx == values.size()) return;
    previousNode->next = new ListNode(values[currIdx]);
    return generateLinkedList(previousNode->next, values, ++currIdx);
  }

  // Primary Function
  // Returns a ListNode pointer [linked list] from a vector of ListNode pointers
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    vector<int> unsortedMergedLists = generateValuesVec(lists);
    vector<vector<int>> initialSplitLists = vector<vector<int>>();
    createFirstDuoSplit(unsortedMergedLists, initialSplitLists, 0);
    vector<vector<int>> sortedMergedLists = vector<vector<int>>();
    mergeSplitLists(initialSplitLists, sortedMergedLists);
    ListNode* mergedLinkedList = new ListNode(sortedMergedLists.front()[0]);
    generateLinkedList(mergedLinkedList, sortedMergedLists.front(), 1);
    return mergedLinkedList;
  }
};

// Takes a current ListNode and a vector of values, and creates a linked list
void generateLinkedList(ListNode* previousNode, vector<int> values, int currIdx) {
  if (currIdx == values.size()) return;
  previousNode->next = new ListNode(values[currIdx]);
  return generateLinkedList(previousNode->next, values, ++currIdx);
}

// Takes a ListNode pointer and prints out the linked list
void printLinkedList(ListNode* currNode, std::string& linkedListOutput) {
  if (currNode == nullptr) return;
  linkedListOutput = linkedListOutput + std::to_string(currNode->val) + ",";
  printLinkedList(currNode->next, linkedListOutput);
}

int main(int argc, char** argv) {
  Solution solution;
  std::cout << "Input: ";
  std::string tmp;
  std::string linkedLists;
  std::cin >> tmp >> tmp >> linkedLists;
  if (linkedLists.size() <= 4) std::cout << "Output: []" << "\n";
  else {
    vector<ListNode*> linkedListsVec = vector<ListNode*>();
    linkedLists.pop_back();
    vector<int> values = vector<int>();
    linkedLists.erase(0, 2);
    for (auto listChr : linkedLists) {
      if (listChr == '[' || listChr == ',') continue;
      if (listChr == ']') {
        ListNode* firstNode = new ListNode(values[0]);
        generateLinkedList(firstNode, values, 1);
        linkedListsVec.push_back(firstNode);
        values.clear();
        continue;
      }
      values.push_back(listChr - '0');
    }
    ListNode* mergedKLists = solution.mergeKLists(linkedListsVec);
    std::cout << "Output: ";
    std::string linkedListOutput = "[";
    printLinkedList(mergedKLists, linkedListOutput);
    linkedListOutput.pop_back();
    linkedListOutput += "]";
    std::cout << linkedListOutput << "\n";
  }
  return 0;
}
