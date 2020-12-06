#include <stdexcept>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <queue>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;
using std::pair;
using std::set;
using std::queue;



void populateSafeSet(set<pair<int,int>>& safeSet, vector<vector<char>>& board, int x, int y) {

  char targetColor = board[x][y];
  queue<pair<int,int>> q;
  q.push({x, y});
  while (!q.empty()) {
    auto nextCoords = q.front();
    q.pop();
    int thisX = nextCoords.first;
    int thisY = nextCoords.second;
    if (thisX < 0 || thisX >= board.size() || thisY < 0 || thisY >= board.at(thisX).size() || board[thisX][thisY] != targetColor || 0 != safeSet.count({x,y})) {
      continue;
    }

    safeSet.insert(nextCoords);
    static vector<pair<int,int>> dPairs = {{-1, 0}, {1, 0}, {0, -1}, {0 ,1}};
    for (auto& dPair: dPairs) {
      int nextX = thisX + dPair.first;
      int nextY = thisY + dPair.second;
      q.push({nextX, nextY});
    }
  }
}

void FillSurroundedRegions(vector<vector<char>>* board_ptr) {

  vector<vector<char>>& board = *board_ptr;
  set<pair<int,int>> safeSet;

  for (int x = 0; x < board.size(); x++) {
    if (board[x][0] == 'W') {
      populateSafeSet(safeSet, board, x, 0);
    }
  }

  for (int y = 0; y < board.at(0).size(); y++) {
    if (board[0][y] == 'W') {
      populateSafeSet(safeSet, board, 0, y);
    }
  }

  for (int x = 0; x < board.size(); x++) {
    if (board[x][board.at(x).size() - 1] == 'W') {
      populateSafeSet(safeSet, board, x, board.at(x).size() - 1);
    }
  }

  for (int y = 0; y < board.at(board.size() - 1).size(); y++) {
    if (board[board.size() - 1][y] == 'W') {
      populateSafeSet(safeSet, board, board.size() - 1, y);
    }
  }

  for (int x = 0; x < board.size(); x++) {
    for (int y = 0; y < board.at(x).size(); y++) {
      if (board[x][y] == 'W' && 0 == safeSet.count({x, y})) {
        board[x][y] = 'B';
      }
    }
  }

  return;
}
vector<vector<string>> FillSurroundedRegionsWrapper(
    TimedExecutor& executor, vector<vector<string>> board) {
  vector<vector<char>> char_vector;
  char_vector.resize(board.size());
  for (int i = 0; i < board.size(); i++) {
    for (const string& s : board[i]) {
      if (s.size() != 1) {
        throw std::runtime_error("String size is not 1");
      }
      char_vector[i].push_back(s[0]);
    }
  }

  executor.Run([&] { FillSurroundedRegions(&char_vector); });

  board.clear();
  board.resize(char_vector.size(), {});
  for (int i = 0; i < board.size(); i++) {
    for (char c : char_vector[i]) {
      board[i].emplace_back(1, c);
    }
  }

  return board;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "board"};
  return GenericTestMain(
      args, "matrix_enclosed_regions.cc", "matrix_enclosed_regions.tsv",
      &FillSurroundedRegionsWrapper, DefaultComparator{}, param_names);
}
