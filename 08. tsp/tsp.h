#include "graph.h"

#include <vector>

double calc_path_len(const Graph &graph, std::vector<int> path);

std::vector<int> tsp(const Graph &graph);

std::vector<int> tsp_bf(const Graph &graph);

std::vector<int> tsp_bnb(const Graph &graph, int start);

std::vector<int> tsp_greedy(const Graph &graph, int start);