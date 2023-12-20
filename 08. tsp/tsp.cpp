#include "tsp.h"
#include "iostream"
#include "queue"
#include <set>
#include <limits>

#define INFINITY numeric_limits<double>::infinity()

using namespace std;

int random_in_range(int start = 0, int end = RAND_MAX) {
    return rand() % (end - start + 1) + start;
}

double random_in_range(double start = 0, double end = RAND_MAX) {
    return (rand() - 0) * (end - start) / (RAND_MAX - 0) + start;
}

double calc_path_len(const Graph &graph, vector<int> path) {
    if (path.size() < 2) return INFINITY;

    double path_sum = 0;

    for (int i = 0; i + 1 < path.size(); i++) {
        path_sum += graph.edge_weight(path[i], path[i + 1]);
    }

    path_sum += graph.edge_weight(path[0], path[path.size() - 1]);
    return path_sum;
}

vector<int> min_path(const Graph &graph, vector<int> first_path, vector<int> second_path) {
    if (calc_path_len(graph, first_path) > calc_path_len(graph, second_path)) {
        return second_path;
    }
    return first_path;
}


double calc_lower_bound(const Graph &graph, vector<int> visited) {
    double sum = 0;
    vector<int> graph_vertices = graph.get_vertices();

    for (int i = 0; i < graph_vertices.size(); i++) {
        vector<int> unvisisted_vert;
        vector<double> edges_weight;
        if (find(visited.begin(), visited.end(), graph_vertices[i]) == visited.end()) {
            //проверяет что в visited нет i-ой вершины графа
            unvisisted_vert = graph.get_adjacent_vertices(graph_vertices[i]);
            //в непосещенные вершины записываем смежные с посещенной

            for (int j = 0; j < unvisisted_vert.size(); j++) //пробег в цикле по непосещенным вершинам
            {
                if (find(visited.begin(), visited.end(), unvisisted_vert[j]) == visited.end()) {
                    //проверяет что в visited нет j-ой вершины графа
                    edges_weight.push_back(graph.edge_weight(graph_vertices[i], unvisisted_vert[j]));
                    //добавляем вес ребер
                }
            }
            sort(edges_weight.begin(), edges_weight.end()); //Сортируем массив весов по возрастанию
        }

        if (edges_weight.size() == 1)
            sum += edges_weight[0];
        else if (edges_weight.size() > 1)
            sum += edges_weight[0] + edges_weight[1];
        edges_weight.clear();
    }

    return sum / 2;
}

vector<int> BnB(const Graph &graph, vector<int> visited, vector<int> best_path) {
    if (visited.size() == graph.get_vertices().size()) {
        return min_path(graph, best_path, visited);
    }

    for (int i = 0; i < graph.get_vertices().size(); i++) {
        if (find(visited.begin(), visited.end(), i) == visited.end()) {
            //если i вершина не в посещенных
            auto next_vertex = visited;
            next_vertex.push_back(i);
            if (best_path.size() < graph.get_vertices().size() or calc_lower_bound(graph, next_vertex) < calc_path_len(
                    graph, best_path)) {
                auto path = BnB(graph, next_vertex, best_path);
                best_path = min_path(graph, best_path, path); //выбор наиболее оптимального пути
            }
        }
    }
    return best_path;
}

vector<int> tsp_bnb(const Graph &graph, int start_vertex) {
    vector<int> best_path;
    vector<int> visited{start_vertex};

    return BnB(graph, visited, best_path);
}

vector<int> tsp_bf(const Graph &graph) {
    const vector<int> vertices = graph.get_vertices();
    const int num_vertices = vertices.size();

    // Создаем вектор с начальной перестановкой вершин (0, 1, 2, ..., n-1)
    vector<int> current_path(num_vertices);
    for (int i = 0; i < num_vertices; ++i) {
        current_path[i] = i;
    }

    vector<int> best_path;
    double min_length = INFINITY;

    do {
        double current_length = calc_path_len(graph, current_path);
        if (current_length < min_length) {
            min_length = current_length;
            best_path = current_path;
        }
    } while (next_permutation(current_path.begin(), current_path.end()));

    if (min_length == INFINITY) return vector<int>{};

    return best_path;
}

vector<int> tsp_greedy(const Graph &graph, int start) {
    if (graph.get_vertices().size() < 2) {
        return {};
    }

    int current = start;
    vector<int> path{current};

    while (path.size() < graph.get_vertices().size()) {
        double minimal_distance = INFINITY;
        int closet_vertex = -1;
        for (auto p: graph.get_adjacent_edges(current)) {
            if (find(path.begin(), path.end(), p.first) == path.end()) {
                if (p.second < minimal_distance) {
                    minimal_distance = p.second;
                    closet_vertex = p.first;
                }
            }
        }
        path.push_back(closet_vertex);
        current = closet_vertex;
    }
    return path;
}

vector<int> tsp(const Graph &graph){
    return tsp_bf(graph);
}