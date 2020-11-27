#include <vector>
#include <queue>
#include <iostream>

#include "test_framework/generic_test.h"
using std::vector;
using namespace std;
// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int>* A_ptr) {


	priority_queue<int, vector<int>, greater<int>> pq;
	for (auto i : *A_ptr) {

		if (pq.size() < k) { 
			pq.push(i);
		}
		else {
			if (pq.top() < i) {
				pq.pop();
				pq.push(i);
			}
		}
	}

	if (pq.size() < k) {
		return -1;
	}

  return pq.top();
}
int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
