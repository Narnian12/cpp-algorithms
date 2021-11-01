//
//  main.cpp
//  kadane
//
//  Created by Peter Sun on 10/30/21.
//

#include <iostream>
#include <vector>

using namespace std;

int maxSubarraySum(vector<int> arr) {
    int globalSum = 0;
    int localSum = 0;
    for (auto elem : arr) {
        localSum += elem;
        if (globalSum < localSum) globalSum = localSum;
        if (localSum < 0) localSum = 0;
    }
    
    return globalSum;
}

int main(int argc, const char * argv[]) {
    vector<int> vec { -2, -3, 4, -1 -2, 1, 5, -3 };
    cout << maxSubarraySum(vec) << "\n";
    std::cout << "Hello, World!\n";
    return 0;
}
