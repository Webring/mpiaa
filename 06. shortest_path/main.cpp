#include "shortest_path.h"
#include "iostream"
#include "chrono"


#define NUMBER_OF_VERTICES 400
#define NUMBER_OF_EDGES 800

using namespace std;
using namespace std::chrono;


int random_in_range(int start = 0, int end = RAND_MAX) {
    return rand() % (end - start + 1) + start;
}

Graph generate_random_weighted_graph(int num_vertices, int num_edges) {
    Graph graph;

    // ���������� �������
    for (int i = 1; i <= num_vertices; ++i) {
        graph.add_vertex(i);
    }

    // ���������� ���� � ���������� ������
    for (int i = 0; i < num_edges; ++i) {
        int start_vertex = rand() % num_vertices + 1;
        int end_vertex = rand() % num_vertices + 1;
        double weight = (rand() % 100) / 10.0; // ��������� ���� �� 0 �� 9.9

        // ���������, ��� ������ ����� ��� ���
        if (!graph.has_edge(start_vertex, end_vertex)) {
            graph.add_edge(start_vertex, end_vertex, weight);
        }
    }

    return graph;
}

int main() {
    srand(50);

    cout << "start" << endl;

    double search_time_sum = 0;
    int number_of_search = 0;

    Graph new_graph = generate_random_weighted_graph(NUMBER_OF_VERTICES, NUMBER_OF_EDGES);
    cout << "gen end" << endl;
    for (int start = 0; start < NUMBER_OF_VERTICES - 1; start++) {
        cout << start << " AVG " << search_time_sum / number_of_search << endl;
        for (int end = start + 1; end < NUMBER_OF_VERTICES; end++) {
            auto start_time = steady_clock::now();
            shortest_path(new_graph, start, end);
            search_time_sum += duration<double>(steady_clock::now() - start_time).count();
            number_of_search += 1;
        }
    }

    cout << "AVG " << search_time_sum / number_of_search << endl;

}
