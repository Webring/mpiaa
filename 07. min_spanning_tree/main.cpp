#include "min_spanning_tree.h"
#include "iostream"
#include "chrono"


#define NUMBER_OF_VERTICES 4000
#define NUMBER_OF_EDGES 10000

using namespace std;
using namespace std::chrono;


int random_in_range(int start = 0, int end = RAND_MAX) {
    return rand() % (end - start + 1) + start;
}

Graph generate_random_weighted_graph(int num_vertices, int num_edges) {
    Graph graph;

    // Генерируем вершины
    for (int i = 1; i <= num_vertices; ++i) {
        graph.add_vertex(i);
    }

    // Генерируем рёбра с случайными весами
    for (int i = 0; i < num_edges; ++i) {
        int start_vertex = rand() % num_vertices + 1;
        int end_vertex = rand() % num_vertices + 1;
        double weight = (rand() % 100) / 10.0; // Случайные веса от 0 до 9.9

        // Проверяем, что такого ребра ещё нет
        if (!graph.has_edge(start_vertex, end_vertex)) {
            graph.add_edge(start_vertex, end_vertex, weight);
        }
    }

    return graph;
}

int main() {
    srand(50);

    Graph new_graph = generate_random_weighted_graph(NUMBER_OF_VERTICES, NUMBER_OF_EDGES);

    auto start_time = steady_clock::now();

    min_spanning_tree(new_graph);

    cout << "time " << duration<double>(steady_clock::now() - start_time).count() << endl;

}
