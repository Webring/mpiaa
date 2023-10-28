#include "min_spanning_tree.h"

using namespace std;

struct Edge {
    int start_vertex;
    int end_vertex;
    double weight;

    Edge(int start, int end, double w) : start_vertex(start), end_vertex(end), weight(w) {}

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

vector<pair<int, int>> min_spanning_tree(const Graph &graph) {
    int num_vertices = graph.get_vertices().size();
    vector<Edge> edges;

    // Получение всех рёбер графа
    for (int vertex : graph.get_vertices()) {
        for (const auto& neighbor : graph.get_adjacent_edges(vertex)) {
            edges.push_back(Edge(vertex, neighbor.first, neighbor.second));
        }
    }

    // Сортировка рёбер по весу
    sort(edges.begin(), edges.end());

    vector<pair<int, int>> mst; // Рёбра MST
    vector<int> components(num_vertices);

    for (int i = 0; i < num_vertices; i++) {
        components[i] = i;
    }

    for (const Edge& edge : edges) {
        int start_component = components[edge.start_vertex - 1];
        int end_component = components[edge.end_vertex - 1];

        if (start_component != end_component) {
            mst.push_back({edge.start_vertex, edge.end_vertex});

            // Объединение двух компонент в одну
            for (int i = 0; i < num_vertices; i++) {
                if (components[i] == start_component) {
                    components[i] = end_component;
                }
            }
        }
    }

    return mst;
}
