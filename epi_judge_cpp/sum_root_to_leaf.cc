#include "binary_tree_node.h"
#include "test_framework/generic_test.h"





int getSum(BinaryTreeNode<int>* root, int prefix) {

  prefix = prefix << 1;
  prefix = (prefix | root->data);

  if (root->right == NULL && root->left == NULL) {
    return prefix;
  }

  int result = 0;
  if (root->right != NULL) {
    result += getSum(root->right.get(), prefix);
  }
  if (root->left != NULL) {
    result += getSum(root->left.get(), prefix);
  }

  return result;
}


int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.

  if (tree == NULL) {
    return 0;
  }
  return getSum(tree.get(), 0);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "sum_root_to_leaf.cc", "sum_root_to_leaf.tsv",
                         &SumRootToLeaf, DefaultComparator{}, param_names);
}
