#include <iostream>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

// Leetcode answer - https://www.tutorialcup.com/leetcode-solutions/kth-largest-element-in-a-stream-leetcode-solution.htm
class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int>> pq;
    int K;
    KthLargest(int k, vector<int>& nums) {
        K = k;
        for (auto num : nums) {
            pq.push(num);
            if (pq.size() > k) pq.pop();
        }
    }
    
    int add(int val) {
        pq.push(val);
        if (pq.size() > K) pq.pop();
        return pq.top();
    }
};

int main() {
  vector<int> vec { 4, 5, 8, 2 };
  KthLargest* obj = new KthLargest(3, vec);
  cout << obj->add(3) << "\n"; // 4
  cout << obj->add(5) << "\n"; // 5

  return 0;
}