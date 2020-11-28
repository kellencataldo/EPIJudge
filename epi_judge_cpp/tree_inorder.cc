#include <memory>
#include <vector>
#include <stack>
#include <iostream>
#include <utility>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;
using std::stack;
using std::pair;
/*

recursive solution

void traverseInOrder(const unique_ptr<BinaryTreeNode<int>>& tree, vector<int>& results) {

	if (tree == NULL) {
		return;
	}
	
	traverseInOrder(tree->left, results);
	results.push_back(tree->data);
	traverseInOrder(tree->right, results);
}

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
	// left, root, right
	vector<int> output;
	traverseInOrder(tree, output);
	return output;
}
*/

// Non-recursive solution

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
	// left, root, right
	vector<int> output;
	if (NULL == tree) {
		return output;
	} 

	stack<BinaryTreeNode<int>*> vs;
	vs.push(tree.get());
	bool keepScanning = true;

	while (!vs.empty()) {
		BinaryTreeNode<int>* next = vs.top();
		if (keepScanning && next->left != NULL) {
			vs.push(next->left.get());
		}
		else {

			if (next->left == NULL) {
				keepScanning = false;
			}

			vs.pop();
			output.push_back(next->data);
			if (next->right != NULL) {
				vs.push(next->right.get());
				keepScanning = true;
			}
		}

	}



	return output;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
