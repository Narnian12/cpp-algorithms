#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

bool moveIsValid(string subStr, int n, int x, int y) {
    int start = x;
    for (auto chr : subStr) {
        if (chr == 'l') --start;
        else if (chr == 'r') ++start;
        if (start > n) return false;
    }
    return start == y;
}

void checkMove(string subStr, int idxToDelete, int n, int x, int y, int& moves, unordered_map<string, bool>& finishedMoves) {
    if (idxToDelete != -1) subStr.erase(idxToDelete, 1);
    // If move has not been tried before
    if (finishedMoves.find(subStr) == finishedMoves.end()) {
        moves = moveIsValid(subStr, n, x, y) ? moves + 1 : moves;
        finishedMoves[subStr] = true;
    }
    else return;
    if (subStr.size() > 0) {
        for (int i = 0; i < subStr.size(); ++i) {
            checkMove(subStr, i, n, x, y, moves, finishedMoves);
        }
    }
}

/*
 * Complete the 'distinctMoves' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. INTEGER n
 *  3. INTEGER x
 *  4. INTEGER y
 */

int distinctMoves(string s, int n, int x, int y) {
    int moves = 0;
    unordered_map<string, bool> finishedMoves;
    checkMove(s, -1, n, x, y, moves, finishedMoves);
    return moves;
}

int main() {
    cout << distinctMoves("rrlrlr", 6, 1, 2) << "\n"; // 7
}