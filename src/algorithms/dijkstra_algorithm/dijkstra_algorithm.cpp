#define DOCTEST_CONFIG_IMPLEMENT

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include "doctest/doctest.h"

using namespace std;

// Structure that represents a vertex of the graph
struct Vertex {
  // ID of the vertex
  int id;

  // Vector that stores the neighbors of the vertex
  vector<pair<Vertex *, int>> neighbors;

  // Constructor
  explicit Vertex(int _id) : id(_id) {}
};

// Structure that represents an edge of the graph
struct Edge {
  // Source vertex of the edge
  Vertex *source;

  // Destination vertex of the edge
  Vertex *destination;

  // Weight of the edge
  int weight;

  // Constructor
  Edge(Vertex *_source, Vertex *_destination, int _weight)
      : source(_source), destination(_destination), weight(_weight) {}
};

// Class that represents a graph
class Graph {
 private:
  // Vector that stores the vertices of the graph
  vector<Vertex *> vertices;

  // Vector that stores the edges of the graph
  vector<Edge *> edges;

 public:
  // Method that adds a vertex to the graph
  void addVertex(int id) {
    vertices.push_back(new Vertex(id));
  }

  // Method that adds an edge to the graph
  void addEdge(Vertex *source, Vertex *destination, int weight) {
    // Create a new edge
    Edge *edge = new Edge(source, destination, weight);

    // Add the edge to the vector of neighbors of the source vertex
    source->neighbors.emplace_back(destination, weight);

    // Add the edge to the vector of edges of the graph
    edges.push_back(edge);
  }

  // Getter method that returns the vertices of the graph
  [[nodiscard]] vector<Vertex *> getVertices() const {
    return vertices;
  }
};

// Structure that represents the result of the Dijkstra algorithm
struct ShortestPath {
  // Vector that stores the distances from the source vertex to each vertex of the graph
  vector<int> distances;

  // Vector that stores the paths from the source vertex to each vertex of the graph
  vector<vector<int>> paths;
};

// Class that implements the Dijkstra algorithm
class Dijkstra {
 private:
  // Graph on which the algorithm will be executed
  Graph *graph;

 public:
  // Constructor
  explicit Dijkstra(Graph *_graph) : graph(_graph) {}

  // Method that executes the Dijkstra algorithm
  ShortestPath shortestPath(Vertex *source) {
    // Define a priority queue that stores pairs of distance from source and vertex
    priority_queue<pair<int, Vertex *>, vector<pair<int, Vertex *>>, greater<>> priorityQueue;

    // Define a vector that stores the distances from the source vertex to each vertex of the graph
    vector<int> distances(graph->getVertices().size(), numeric_limits<int>::max());

    // Set the distance from the source vertex to itself to 0
    distances[source->id] = 0;

    // Add the source vertex to the priority queue
    priorityQueue.emplace(0, source);

    // Define a vector that stores the paths from the source vertex to each vertex of the graph
    vector<vector<int>> paths(graph->getVertices().size());

    // Loop while the priority queue is not empty
    while (!priorityQueue.empty()) {
      // Get the vertex with the smallest distance from the source vertex
      Vertex *vertex = priorityQueue.top().second;

      // Remove the vertex from the priority queue
      priorityQueue.pop();

      // Loop through the neighbors of the vertex
      for (auto neighbor : vertex->neighbors) {
        // Calculate the distance from the source vertex to the neighbor
        int distance = distances[vertex->id] + neighbor.second;

        // Check if the distance is smaller than the current distance
        if (distance < distances[neighbor.first->id]) {
          // Update the distance
          distances[neighbor.first->id] = distance;

          // Add the neighbor to the priority queue
          priorityQueue.emplace(distance, neighbor.first);

          // Update the path
          paths[neighbor.first->id] = paths[vertex->id];

          // Add the neighbor to the path
          paths[neighbor.first->id].push_back(vertex->id);
        }
      }
    }

    // Copy the distances and paths to the result structure
    vector<int> shortestDistances = distances;
    vector<vector<int>> shortestPaths = paths;
    for (int i = 0; i < distances.size(); i++) {
      if (distances[i] == numeric_limits<int>::max()) {
        shortestPaths[i].clear();
      } else {
        shortestPaths[i].push_back(i);
      }
    }
    ShortestPath shortestPath;
    shortestPath.distances = shortestDistances;
    shortestPath.paths = shortestPaths;

    // Return the result
    return shortestPath;
  }
};

// Function that prints the result of the shortest path algorithm
void printResult(const ShortestPath &sp, int source) {
  // Print header
  cout << "==================================================\n";
  cout << "Shortest path from vertex " << source << " to all other vertices:\n";
  cout << "==================================================\n";

  // Iterate over all vertices
  for (int i = 0; i < sp.distances.size(); i++) {
    // Check if vertex is reachable
    if (sp.distances[i] == numeric_limits<int>::max()) {
      // Print info for unreachable vertex
      cout << "  — No path from vertex " << source << " to vertex " << i << "\n";
    } else {
      // Print info for reachable vertex
      cout << "  — Shortest distance from vertex " << source << " to vertex " << i << " is " << sp.distances[i]
           << ":\n    Path: ";
      for (int j = 0; j < sp.paths[i].size(); j++) {
        cout << sp.paths[i][j];
        if (j < sp.paths[i].size() - 1) {
          cout << " -> ";
        }
      }
      cout << "\n";
    }
  }
  cout << "\n";
}

// Main function
int main() {
  // Output example graph
  Graph graph;
  graph.addVertex(0);
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addVertex(3);
  graph.addEdge(graph.getVertices()[0], graph.getVertices()[1], 10);
  graph.addEdge(graph.getVertices()[0], graph.getVertices()[2], 3);
  graph.addEdge(graph.getVertices()[1], graph.getVertices()[2], 1);
  graph.addEdge(graph.getVertices()[1], graph.getVertices()[3], 2);
  graph.addEdge(graph.getVertices()[2], graph.getVertices()[1], 4);
  graph.addEdge(graph.getVertices()[2], graph.getVertices()[3], 8);

  Dijkstra dijkstra(&graph);
  ShortestPath shortestPath0 = dijkstra.shortestPath(graph.getVertices()[0]);
  printResult(shortestPath0, 0);

  ShortestPath shortestPath1 = dijkstra.shortestPath(graph.getVertices()[1]);
  printResult(shortestPath1, 1);

  ShortestPath shortestPath2 = dijkstra.shortestPath(graph.getVertices()[2]);
  printResult(shortestPath2, 2);

  ShortestPath shortestPath3 = dijkstra.shortestPath(graph.getVertices()[3]);
  printResult(shortestPath3, 3);

  // Run tests
  doctest::Context context;
  int res = context.run();
  return res;
}

// Tests
TEST_CASE("Test shortest path computation on a simple graph") {
  Graph graph;
  graph.addVertex(0);
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addEdge(graph.getVertices()[0], graph.getVertices()[1], 1);
  graph.addEdge(graph.getVertices()[0], graph.getVertices()[2], 2);
  graph.addEdge(graph.getVertices()[1], graph.getVertices()[2], 3);

  Dijkstra dijkstra(&graph);
  ShortestPath shortestPath0 = dijkstra.shortestPath(graph.getVertices()[0]);
  ShortestPath shortestPath1 = dijkstra.shortestPath(graph.getVertices()[1]);
  ShortestPath shortestPath2 = dijkstra.shortestPath(graph.getVertices()[2]);

  // Test shortest distance computation
  CHECK(shortestPath0.distances == vector<int>({0, 1, 2}));
  CHECK(shortestPath1.distances == vector<int>({numeric_limits<int>::max(), 0, 3}));
  CHECK(shortestPath2.distances == vector<int>({numeric_limits<int>::max(), numeric_limits<int>::max(), 0}));

  // Test shortest path computation
  CHECK(shortestPath0.paths == vector<vector<int>>({{0}, {0, 1}, {0, 2}}));
  CHECK(shortestPath1.paths == vector<vector<int>>({{}, {1}, {1, 2}}));
  CHECK(shortestPath2.paths == vector<vector<int>>({{}, {}, {2}}));
}

TEST_CASE("Test shortest path computation on a disconnected graph") {
  Graph graph;
  graph.addVertex(0);
  graph.addVertex(1);
  graph.addVertex(2);

  Dijkstra dijkstra(&graph);
  ShortestPath shortestPath0 = dijkstra.shortestPath(graph.getVertices()[0]);
  ShortestPath shortestPath1 = dijkstra.shortestPath(graph.getVertices()[1]);
  ShortestPath shortestPath2 = dijkstra.shortestPath(graph.getVertices()[2]);

  // Test shortest distance computation
  CHECK(shortestPath0.distances == vector<int>({0, numeric_limits<int>::max(), numeric_limits<int>::max()}));
  CHECK(shortestPath1.distances == vector<int>({numeric_limits<int>::max(), 0, numeric_limits<int>::max()}));
  CHECK(shortestPath2.distances == vector<int>({numeric_limits<int>::max(), numeric_limits<int>::max(), 0}));

  // Test shortest path computation
  CHECK(shortestPath0.paths == vector<vector<int>>({{0}, {}, {}}));
  CHECK(shortestPath1.paths == vector<vector<int>>({{}, {1}, {}}));
  CHECK(shortestPath2.paths == vector<vector<int>>({{}, {}, {2}}));
}

TEST_CASE("Test shortest path computation on a graph with negative edge weights") {
  Graph graph;
  graph.addVertex(0);
  graph.addVertex(1);
  graph.addVertex(2);
  graph.addEdge(graph.getVertices()[0], graph.getVertices()[1], -1);
  graph.addEdge(graph.getVertices()[0], graph.getVertices()[2], 2);
  graph.addEdge(graph.getVertices()[1], graph.getVertices()[2], 3);

  Dijkstra dijkstra(&graph);
  ShortestPath shortestPath0 = dijkstra.shortestPath(graph.getVertices()[0]);
  ShortestPath shortestPath1 = dijkstra.shortestPath(graph.getVertices()[1]);
  ShortestPath shortestPath2 = dijkstra.shortestPath(graph.getVertices()[2]);

  // Test shortest distance computation
  CHECK(shortestPath0.distances == vector<int>({0, -1, 2}));
  CHECK(shortestPath1.distances == vector<int>({numeric_limits<int>::max(), 0, 3}));
  CHECK(shortestPath2.distances == vector<int>({numeric_limits<int>::max(), numeric_limits<int>::max(), 0}));

  // Test shortest path computation
  CHECK(shortestPath0.paths == vector<vector<int>>({{0}, {0, 1}, {0, 2}}));
  CHECK(shortestPath1.paths == vector<vector<int>>({{}, {1}, {1, 2}}));
  CHECK(shortestPath2.paths == vector<vector<int>>({{}, {}, {2}}));
}
