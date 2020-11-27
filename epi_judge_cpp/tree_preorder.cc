#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::vector;


void traversePreOrder(const unique_ptr<BinaryTreeNode<int>>& tree, vector<int>& results) {
	
	if (NULL == tree) {
		return;
	}

	results.push_back(tree->data);
	traversePreOrder(tree->left, results);
	traversePreOrder(tree->right, results);
}


vector<int> PreorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {

	vector<int> results;
	traversePreOrder(tree, results);
	return results;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_preorder.cc", "tree_preorder.tsv",
                         &PreorderTraversal, DefaultComparator{}, param_names);
}
