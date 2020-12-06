#include <deque>
#include <vector>
#include <queue>
#include <utility>



#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::deque;
using std::vector;
using std::queue;
using std::pair;

void FlipColor(int x, int y, vector<deque<bool>>* image_ptr) {

  vector<deque<bool>>& image = *image_ptr;
  bool color = image[x][y];
  queue<pair<int,int>> BFSQ;
  BFSQ.push({x, y});

  while (!BFSQ.empty()) {
    pair<int,int> nextPair = BFSQ.front();
    int nextX = nextPair.first;
    int nextY = nextPair.second;
    BFSQ.pop();

    if (nextX >= image.size() || nextX < 0 || nextY >= image[nextX].size() || nextY < 0 || image[nextX][nextY] != color) {
      continue;
    }

    image[nextX][nextY] = !color;
    vector<pair<int,int>> nextPairs = {{nextX + 1, nextY}, {nextX - 1, nextY}, {nextX, nextY + 1}, {nextX, nextY- 1}};
    for (auto& dPair : nextPairs) {
      BFSQ.push(dPair);
    }
  }
}



vector<vector<int>> FlipColorWrapper(TimedExecutor& executor, int x, int y,
                                     vector<vector<int>> image) {
  vector<deque<bool>> b;
  b.reserve(image.size());
  for (const vector<int>& row : image) {
    deque<bool> tmp;
    tmp.resize(row.size());
    for (int i = 0; i < row.size(); ++i) {
      tmp[i] = static_cast<bool>(row[i]);
    }
    b.push_back(tmp);
  }

  executor.Run([&] { FlipColor(x, y, &b); });

  image.resize(b.size());

  for (int i = 0; i < image.size(); ++i) {
    image[i].resize(b.size());
    for (int j = 0; j < image[i].size(); ++j) {
      image[i][j] = b[i][j];
    }
  }
  return image;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "x", "y", "image"};
  return GenericTestMain(args, "matrix_connected_regions.cc", "painting.tsv",
                         &FlipColorWrapper, DefaultComparator{}, param_names);
}
