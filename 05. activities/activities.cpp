#include <algorithm>
#include <iostream>
#include "activities.h"

#define USING_OPTIMAL_WAY false

using namespace std;

bool compare_by_finish_time(const Activity &first, const Activity &second) {
    return first.finish < second.finish;
}

#if USING_OPTIMAL_WAY

vector<Activity> get_max_activities(const vector<Activity> &activities) {
    vector<Activity> sorted = activities;
    sort(sorted.begin(), sorted.end(), compare_by_finish_time);

    int current_task_id = 0;
    vector<Activity> result;

    while (current_task_id < sorted.size()) {
        result.push_back(sorted[current_task_id]);
        int next = current_task_id + 1;

        while (next < sorted.size()) {
            if (sorted[next].start >= sorted[current_task_id].finish){
                break;
            }
            next ++;
        }

        current_task_id = next;
    }

    return result;
}

#else

void generateCombinations(const vector<Activity> &elements, vector<Activity> &current_combination, int index, int k, vector<vector<Activity>> &all_combinations) {
    if (k == 0) {
        all_combinations.push_back(current_combination);
        return ;
    }

    for (int i = index; i < elements.size(); ++i) {
        current_combination.push_back(elements[i]);
        generateCombinations(elements, current_combination, i + 1, k - 1, all_combinations);
        current_combination.pop_back();
    }
}

vector<Activity> get_max_activities(const vector<Activity> &activities) {
    vector<Activity> current_combination;
    vector<vector<Activity>>all_combinations;

    for (int i = 1; i <= activities.size(); i++) {
        generateCombinations(activities, current_combination, 0, i, all_combinations);
    }

    vector<Activity> max_combination;

    for (auto &comb: all_combinations) {
        auto sorted_comb = comb;
        sort(sorted_comb.begin(), sorted_comb.end(), compare_by_finish_time);

        bool success = true;

        for (int i = 1; i < sorted_comb.size(); i++) {
            if (sorted_comb[i-1].finish > sorted_comb[i].start){
                success = false;
                break;
            }
        }

        if (success and sorted_comb.size() > max_combination.size()){
            max_combination = sorted_comb;
        }
    }

    return max_combination;
}

#endif
