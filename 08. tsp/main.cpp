#include "tsp.h"
#include "iostream"
#include "chrono"


#define NUMBER_OF_VERTICES 7

using namespace std;
using namespace std::chrono;

Graph generate_random_weighted_full_graph(int num_vertices) {
    Graph graph;

    for (int i = 0; i < num_vertices - 1; i++)
        for (int j = i + 1; j < num_vertices; j++)
            graph.add_edge(i, j, (rand() % 100) / 10.0);

    return graph;
}


int main() {
    srand(50);

    Graph new_graph = generate_random_weighted_full_graph(NUMBER_OF_VERTICES);

    auto start_time = steady_clock::now();
    vector<int> path = tsp_bf(new_graph);
    double path_len = calc_path_len(new_graph, path);
    cout << "BF time " << duration<double>(steady_clock::now() - start_time).count() << endl;
    cout << "BF path len " << path_len << endl << endl;

    start_time = steady_clock::now();
    path = tsp_bnb(new_graph, 0);
    path_len = calc_path_len(new_graph, path);
    cout << "BnB time " << duration<double>(steady_clock::now() - start_time).count() << endl;
    cout << "BnB path len " << path_len << endl << endl;

    start_time = steady_clock::now();
    path = tsp_greedy(new_graph, 0);
    path_len = calc_path_len(new_graph, path);
    cout << "greedy time " << duration<double>(steady_clock::now() - start_time).count() << endl;
    cout << "greedy path len " << path_len << endl << endl;

    return 0;
}
