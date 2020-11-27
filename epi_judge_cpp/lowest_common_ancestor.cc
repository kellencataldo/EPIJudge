#include <memory>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

struct SR {

  SR() : LFound(false), RFound(false), LCA(NULL) { }
  bool LFound;
  bool RFound;
  BinaryTreeNode<int>* LCA;

};


SR findLCA(const unique_ptr<BinaryTreeNode<int>>& tree, const unique_ptr<BinaryTreeNode<int>>& node0, const unique_ptr<BinaryTreeNode<int>>& node1) {

  if (tree == NULL) {
    return SR();
  }

  SR result = SR();
  if (tree->data == node0->data) {
    result.LFound = true;
  }
  if (tree->data == node1->data) {
    result.RFound = true;
  }
  
  SR ls = findLCA(tree->left, node0, node1);
  SR rs = findLCA(tree->right, node0, node1);
  result.LFound = result.LFound || ls.LFound || rs.LFound;
  result.RFound = result.RFound || ls.RFound || rs.RFound;

  if (ls.LCA != NULL) {
    result.LCA = ls.LCA;
  } else if (rs.LCA != NULL) {
    result.LCA = rs.LCA;
  }
  else if (result.LFound && result.RFound) {
    result.LCA = tree.get();
  }

  return result;
}

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& tree, const unique_ptr<BinaryTreeNode<int>>& node0, const unique_ptr<BinaryTreeNode<int>>& node1) {
  SR result = findLCA(tree, node0, node1);
  return result.LCA;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(tree, node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
