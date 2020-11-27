#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
#include <unordered_set>

using namespace std;

/*

Brute force solution O(n) space O(h) time

unordered_set<int> walk(const unique_ptr<BinaryTreeNode<int>>& node0) {

  unordered_set<int> v;
  BinaryTreeNode<int>* w = node0.get();
  while (w != NULL) {
    v.insert(w->data);
    w = w->parent;
  }

  return v;
}

BinaryTreeNode<int>* getLCA(const unique_ptr<BinaryTreeNode<int>>& node1, unordered_set<int> v) {
  
  BinaryTreeNode<int>* w = node1.get();
  while (NULL != w) {
    if (0 != v.count(w->data)) {
      return w;
    }
    w = w->parent;
  }

  return nullptr;
}

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0, const unique_ptr<BinaryTreeNode<int>>& node1) {

  unordered_set<int> v = walk(node0);
  return getLCA(node1, v);
}

*/


int getDepth(const unique_ptr<BinaryTreeNode<int>>& node0) {

  int d = 0;
  BinaryTreeNode<int>* w = node0.get();
  while (w != NULL) {
    d++;
    w = w->parent;
  }

  return d;
}


BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0, const unique_ptr<BinaryTreeNode<int>>& node1) {

  int d0 = getDepth(node0);
  int d1 = getDepth(node1);

  BinaryTreeNode<int>* w0 = node0.get();
  BinaryTreeNode<int>* w1 = node1.get();

  while (d0 > d1) {
    w0 = w0->parent;
    d0--;
  }

  while (d1 > d0) {
    w1 = w1->parent;
    d1--;
  }

  while (w0->data != w1->data) {
    w0 = w0->parent;
    w1 = w1->parent;
  }

  return w0;
}


int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
