#include "duplicates.h"

#include "set"
#include "algorithm"

#define USE_OPTIMAL_ALGORITHM false

using namespace std;


bool has_duplicates(const std::vector<int> &data) {
#if USE_OPTIMAL_ALGORITHM == true
    // Оптимальный
    // Перебор элементов O(n) + вставка O(log n) и поиск O(log n) = O(n * log n)
    set<int> unique_values;
    for (auto value: data) {
        auto item = unique_values.find(value);
        if (item == unique_values.end()) { // Если элемент не найден
            unique_values.insert(value);
        } else {
            return true;
        }
    }
    return false;

#else
    // Перебор
    for (int current_value: data) {
        int number_of_current_values = 0;
        for (int iter_value: data) {
            if (current_value == iter_value) {
                number_of_current_values += 1;
            }
            if (number_of_current_values > 1) {
                return true;
            }
        }
    }
    return false;
#endif
}


std::vector<int> get_duplicates(const std::vector<int> &data) {
#if USE_OPTIMAL_ALGORITHM == true
    // O(n * log n + (n - 1))
    set<int> result;
    set<int> unique_value;
    for (auto value: data) {
        auto item = unique_value.find(value);
        if (item == unique_value.end()) {
            unique_value.insert(value);
        } else {
            result.insert(value);
        }
    }

    vector<int> result_vector;

    for (int value: result) {
        result_vector.push_back(value);
    }

    return result_vector;
#else
    vector<int> result;
    for (int value: data) {
        bool has_in_result_vector = (find(result.begin(), result.end(), value) == result.end());
        auto value_counts = count(data.begin(), data.end(), value);
        if (has_in_result_vector and (value_counts > 1)) {
            result.push_back(value);
        }
    }

    return result;
#endif

}
