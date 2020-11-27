#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;


void traversePostOrder(const unique_ptr<BinaryTreeNode<int>>& tree, vector<int>& results) {
	if (NULL == tree) {
		return;
	}

	traversePostOrder(tree->left, results);
	traversePostOrder(tree->right, results);
	results.push_back(tree->data);
}

vector<int> PostorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {

	vector<int> results;
	traversePostOrder(tree, results);
	return results;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_postorder.cc", "tree_postorder.tsv",
                         &PostorderTraversal, DefaultComparator{}, param_names);
}
