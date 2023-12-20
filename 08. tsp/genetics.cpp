#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <chrono>
#include <Random>
#include <unordered_set>
#include "graph.h"

#define P 100
#define N 10
#define MaxIt 50
#define Pm 0.2
#define GRAPH_SIZE 80

using namespace std;

double random_in_range(double a, double b) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<> dis(a, b);
    return dis(gen);
}

vector<vector<int>> generatePopulation(Graph &graph, int p) {
    vector<vector<int>> population;
    for (int i = 0; i < p; ++i) {
        vector<int> chromosome;
        for (auto const &pair: graph.get_adjacent_vertices(0)) {
            chromosome.push_back(pair);
        }
        random_shuffle(chromosome.begin(), chromosome.end());
        population.push_back(chromosome);
    }
    return population;
}

double calculate_weight(Graph &graph, vector<int> &chromosome) {
    double weight = 0;
    for (size_t i = 0; i < chromosome.size() - 1; ++i) {
        weight += graph.edge_weight(chromosome[i], chromosome[i + 1]);
    }
    weight += graph.edge_weight(chromosome.back(), chromosome[0]);
    return weight;
}

vector<int> sus(vector<vector<int>> &population, vector<double> &fitness, int n) {
    double F = 0;
    for (double fit: fitness) {
        F += fit;
    }
    double dist = F / n;
    double start = random_in_range(0, dist);

    vector<int> chosen;
    int k = 0;
    double sum_weight = fitness[0];

    for (int i = 0; i < n; ++i) {
        double point = start + i * dist;

        while (sum_weight < point) {
            ++k;
            sum_weight += fitness[k];
        }

        chosen.push_back(k);
    }

    return chosen;
}

vector<int> crossover_er(vector<int> &parent1, vector<int> &parent2, Graph &graph) {
    unordered_map<int, vector<int>> edge_map;

    for (size_t i = 0; i < parent1.size(); ++i) {
        int node = parent1[i];
        edge_map[node].push_back(parent1[(i - 1 + parent1.size()) % parent1.size()]);
        edge_map[node].push_back(parent1[(i + 1) % parent1.size()]);
    }

    for (size_t i = 0; i < parent2.size(); ++i) {
        int node = parent2[i];
        if (edge_map.find(node) == edge_map.end()) {
            edge_map[node].push_back(parent2[(i - 1 + parent2.size()) % parent2.size()]);
            edge_map[node].push_back(parent2[(i + 1) % parent2.size()]);
        } else {
            edge_map[node].push_back(parent2[(i - 1 + parent2.size()) % parent2.size()]);
            edge_map[node].push_back(parent2[(i + 1) % parent2.size()]);
        }
    }

    vector<int> offspring;
    int current_node = parent1[0];
    offspring.push_back(current_node);

    unordered_set<int> visited_nodes;
    visited_nodes.insert(current_node);

    while (offspring.size() < parent1.size()) {
        vector<int> candidates = graph.get_adjacent_vertices(current_node);

        for (int node: candidates) {
            auto it = find(edge_map[current_node].begin(), edge_map[current_node].end(), node);
            if (it != edge_map[current_node].end()) {
                edge_map[node].erase(remove(edge_map[node].begin(), edge_map[node].end(), current_node),
                                     edge_map[node].end());
            }
        }

        int min_edges = INT_MAX;
        int next_node = -1;
        for (int node: candidates) {
            if (visited_nodes.find(node) == visited_nodes.end()) {
                if (edge_map[node].size() < min_edges) {
                    min_edges = edge_map[node].size();
                    next_node = node;
                }
            }
        }

        if (next_node == -1) {
            for (int node: parent1) {
                if (visited_nodes.find(node) == visited_nodes.end()) {
                    next_node = node;
                    break;
                }
            }
        }

        current_node = next_node;
        offspring.push_back(current_node);
        visited_nodes.insert(current_node);
    }

    return offspring;
}

vector<int> two_opt_improve(vector<int> &chromosome, Graph &graph) {
    int n = chromosome.size();

    while (true) {
        int improvement = 0;
        double best_distance = calculate_weight(graph, chromosome);

        for (int i = 1; i < n - 2; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (j - i == 1) {
                    continue;
                }

                vector<int> new_chromosome = chromosome;
                reverse(new_chromosome.begin() + i, new_chromosome.begin() + j);

                double new_distance = calculate_weight(graph, new_chromosome);

                if (new_distance < best_distance) {
                    chromosome = new_chromosome;
                    best_distance = new_distance;
                    improvement++;
                }
            }
        }

        if (improvement == 0) {
            break;
        }
    }

    return chromosome;
}

vector<int> get_best_chromosome(Graph &graph, vector<vector<int>> &population) {
    vector<int> best_chromosome = population[0];
    double best_weight = calculate_weight(graph, best_chromosome);

    for (size_t i = 1; i < population.size(); ++i) {
        double weight = calculate_weight(graph, population[i]);
        if (weight < best_weight) {
            best_chromosome = population[i];
            best_weight = weight;
        }
    }

    return best_chromosome;
}

Graph generate_complete_graph(int num_vertices) {
    Graph graph;
    for (int u = 0; u < num_vertices; ++u) {
        for (int v = u + 1; v < num_vertices; ++v) {
            double weight = random_in_range(1, 10);
            graph.add_edge(u, v, weight);
        }
    }
    return graph;
}

vector<int> tsp_genetics(Graph &graph) {
    vector<vector<int>> population = generatePopulation(graph, P);

    for (int it = 0; it < MaxIt; ++it) {
        vector<double> fitness;
        for (auto &chromosome: population) {
            double weight = calculate_weight(graph, chromosome);
            fitness.push_back(1 / weight);
        }

        vector<int> parents = sus(population, fitness, N);

        vector<vector<int>> offspring;
        while (offspring.size() < P) {
            vector<int> parent1 = population[parents[random_in_range(0, parents.size() - 1)]];
            vector<int> parent2 = population[parents[random_in_range(0, parents.size() - 1)]];
            vector<int> child = crossover_er(parent1, parent2, graph);

            if (random_in_range(0, 1) < Pm) {
                child = two_opt_improve(child, graph);
            }

            offspring.push_back(child);
        }

        population = offspring;
    }

    return get_best_chromosome(graph, population);
}

vector<int> tsp_greedy(Graph &graph, int start) {
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

vector<int> tsp_local_search(Graph &graph) {
    if (graph.get_vertices().size() < 2) {
        return {};
    }

    vector<int> current_path = tsp_greedy(graph, 0);

    while (true) {
        vector<int> improved_path = two_opt_improve(current_path, graph);

        if (calculate_weight(graph, improved_path) < calculate_weight(graph, current_path)) {
            current_path = improved_path;
        } else {
            return current_path;
        }
    }
}

int main() {
    Graph graph = generate_complete_graph(GRAPH_SIZE);

    auto start_time = chrono::steady_clock::now();
    auto path = tsp_greedy(graph, 0);
    auto path_len = calculate_weight(graph, path);
    cout << "greedy time " << chrono::duration<double>(chrono::steady_clock::now() - start_time).count() << endl;
    cout << "greedy path len " << path_len << endl << endl;

    start_time = chrono::steady_clock::now();
    path = tsp_local_search(graph);
    path_len = calculate_weight(graph, path);
    cout << "ls time " << chrono::duration<double>(chrono::steady_clock::now() - start_time).count() << endl;
    cout << "ls path len " << path_len << endl << endl;

    start_time = chrono::steady_clock::now();
    path = tsp_genetics(graph);
    path_len = calculate_weight(graph, path);
    cout << "ga time " << chrono::duration<double>(chrono::steady_clock::now() - start_time).count() << endl;
    cout << "ga path len " << path_len << endl << endl;

    return 0;
}
