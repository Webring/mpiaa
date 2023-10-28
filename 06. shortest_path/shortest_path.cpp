#include <queue>
#include "shortest_path.h"
#include "limits"
#define Infinity numeric_limits<double>::infinity();

using namespace std;


struct VertexInfo {
    int vertex;
    double distance;
};

struct CompareVertexInfo {
    bool operator()(const VertexInfo& lhs, const VertexInfo& rhs) const {
        return lhs.distance > rhs.distance;
    }
};

vector<int> shortest_path(const Graph& graph, int start_vertex, int end_vertex) {
    priority_queue<VertexInfo, vector<VertexInfo>, CompareVertexInfo> min_heap;
    map<int, double> distances;
    map<int, int> previous_vertices;

    min_heap.push({start_vertex, 0});
    distances[start_vertex] = 0;

    while (not min_heap.empty()) {
        int current_vertex = min_heap.top().vertex;
        min_heap.pop();

        if (current_vertex == end_vertex) {
            // Путь найден, восстановим его
            vector<int> path;
            while (current_vertex != start_vertex) {
                path.push_back(current_vertex);
                current_vertex = previous_vertices[current_vertex];
            }
            path.push_back(start_vertex);
            reverse(path.begin(), path.end());
            return path;
        }

        // Перебор соседей текущей вершины
        for (int neighbor : graph.get_adjacent_vertices(current_vertex)) {
            double edge_weight = graph.edge_weight(current_vertex, neighbor);
            double new_distance = distances[current_vertex] + edge_weight;

            if (distances.count(neighbor) == 0 or new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                previous_vertices[neighbor] = current_vertex;
                min_heap.push({neighbor, new_distance});
            }
        }
    }

    return vector<int>();
}

