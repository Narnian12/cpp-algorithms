#include <iostream>
#include <vector>

using namespace std;

// void recurseDFS(vector<vector<char>>& grid, int i, int j, int row, int col) {
//   // Go north
//   DFS(grid, i, j + 1, row, col);
//   // Go south
//   DFS(grid, i, j - 1, row, col);
//   // Go east
//   DFS(grid, i + 1, j, row, col);
//   // Go west
//   DFS(grid, i - 1, j, row, col);
// }

void DFS(vector<vector<char>>& grid, int i, int j, int row, int col) {
  // Either the currently checked element is outside the range of the matrix
  // or is not an island
  if (i < 0 || j < 0 || i >= row || j >= col || grid[i][j] == '0') return;
  // Otherwise a portion of the island is found and recursively look again
  grid[i][j] = '0';
  // Go north
  DFS(grid, i, j + 1, row, col);
  // Go south
  DFS(grid, i, j - 1, row, col);
  // Go east
  DFS(grid, i + 1, j, row, col);
  // Go west
  DFS(grid, i - 1, j, row, col);
}

int numIslands(vector<vector<char>>& grid) {
  int row = grid.size();
  int col = grid[0].size();
  int count = 0;

  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      // A part of island is found
      if (grid[i][j] == '1') {
        ++count;
        grid[i][j] = '0';
        // Recursively go north/south/east/west to see what the island is connected to
        // Go north
        DFS(grid, i, j + 1, row, col);
        // Go south
        DFS(grid, i, j - 1, row, col);
        // Go east
        DFS(grid, i + 1, j, row, col);
        // Go west
        DFS(grid, i - 1, j, row, col);
      }
    }
  }
  return count;
}

int main() {
  vector<vector<char>> matrix;
  vector<char> firstRow { '0', '0', '1', '0'};
  vector<char> secondRow { '0', '0', '1', '1' };
  vector<char> thirdRow { '1', '1', '0', '1' };
  matrix.emplace_back(firstRow);
  matrix.emplace_back(secondRow);
  matrix.emplace_back(thirdRow);

  cout << numIslands(matrix) << "\n"; // 2

  return 0;
}