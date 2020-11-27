#include "binary_tree_node.h"
#include "test_framework/generic_test.h"



bool checkSym(const unique_ptr<BinaryTreeNode<int>>& l, const unique_ptr<BinaryTreeNode<int>>& r) {


  if (r == NULL && l == NULL) {
    return true;
  }
  else if (r == NULL || l == NULL) {

    return false;
  }

  else if (l->data != r->data) {

    return false;
  }
  else {
    return checkSym(l->left, r->right) && checkSym(l->right, r->left);
  }
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (NULL == tree) {
    return true;
  }

  return checkSym(tree->left, tree->right);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
