#include <stdexcept>
#include <vector>
#include <stack>


#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"
using std::vector;
using std::stack;

struct GraphVertex {
  vector<GraphVertex*> edges;
  enum Color {WHITE, GREY, BLACK};
  Color color = WHITE;
};

bool DFS(GraphVertex& graph) {
  if (graph.color == GraphVertex::GREY) {
    return false;
  }
  else if (graph.color == GraphVertex::BLACK) {
    return true;
  }

  graph.color = GraphVertex::GREY;

  for (auto nextGraph: graph.edges) {
    if (!DFS(*nextGraph)) {
      return false;
    }
  }

  graph.color = GraphVertex::BLACK;
  return true;
}

bool IsDeadlocked(vector<GraphVertex>* graph) {

  vector<GraphVertex>& g = *graph;
  for (auto& vertex: g) {
    if (!DFS(vertex)) {
      return true;
    }
  }

  return false;
}
struct Edge {
  int from;
  int to;
};

namespace test_framework {
template <>
struct SerializationTrait<Edge> : UserSerTrait<Edge, int, int> {};
}  // namespace test_framework

bool HasCycleWrapper(TimedExecutor& executor, int num_nodes,
                     const vector<Edge>& edges) {
  vector<GraphVertex> graph;
  if (num_nodes <= 0) {
    throw std::runtime_error("Invalid num_nodes value");
  }
  graph.reserve(num_nodes);

  for (int i = 0; i < num_nodes; i++) {
    graph.push_back(GraphVertex{});
  }

  for (const Edge& e : edges) {
    if (e.from < 0 || e.from >= num_nodes || e.to < 0 || e.to >= num_nodes) {
      throw std::runtime_error("Invalid vertex index");
    }
    graph[e.from].edges.push_back(&graph[e.to]);
  }

  return executor.Run([&] { return IsDeadlocked(&graph); });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "num_nodes", "edges"};
  return GenericTestMain(args, "deadlock_detection.cc",
                         "deadlock_detection.tsv", &HasCycleWrapper,
                         DefaultComparator{}, param_names);
}
