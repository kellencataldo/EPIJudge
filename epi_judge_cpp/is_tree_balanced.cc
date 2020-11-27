#include "binary_tree_node.h"
#include <algorithm>    // std::max
#include "test_framework/generic_test.h"

using namespace std;

struct tResult {
	int height;
	bool balanced;
};


tResult getHeightAndBalance(const unique_ptr<BinaryTreeNode<int>>& root, int h) {


  if (NULL == root) {
    return {h, true};
  }

  tResult rh = getHeightAndBalance(root->right, h + 1);
  tResult lh = getHeightAndBalance(root->left, h + 1);

  int maxH = max(rh.height, lh.height);
  if (!rh.balanced || !lh.balanced) {

    return { maxH, false };
  }

  int diff = abs(lh.height - rh.height);
  if (diff > 1) {
    return {maxH, false};
  }

  return {maxH, true};
}



bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {

  tResult t = getHeightAndBalance(tree, 0);
  return t.balanced;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
