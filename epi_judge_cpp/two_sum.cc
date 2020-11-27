#include <vector>
#include <unordered_set>

#include "test_framework/generic_test.h"
using std::vector;
using namespace std;

bool HasTwoSum(const vector<int>& A, int t) {

	int lowerBound = 0;
	int upperBound = A.size() - 1;
	
	while (lowerBound <= upperBound) {

		int thisTotal = A[lowerBound] + A[upperBound];
		if (thisTotal == t) {
			return true;
		}
		else if (thisTotal > t) {
			upperBound--;
		}
		else {
			lowerBound++;
		}
	}

	return false;
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "two_sum.cc", "two_sum.tsv", &HasTwoSum,
                         DefaultComparator{}, param_names);
}
