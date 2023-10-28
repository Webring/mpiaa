#include "iostream"
#include "chrono"
#include "activities.h"

#define N 18

using namespace std;
using namespace std::chrono;

int random_in_range(int start = 0, int end = RAND_MAX) {
    return rand() % (end - start + 1) + start;
}

int main() {
    srand(50);

    vector<Activity> activities;

    for (int i = 0; i < N; i++) {
        int start = random_in_range(0, 99);
        int finish = random_in_range(start, 100);
        activities.push_back(Activity(start, finish));
    }

    cout << "start" << endl;

    auto start_time = steady_clock::now();
    auto maximum_activities = get_max_activities(activities);
    auto end_time = steady_clock::now();
    double total_duration = duration<double>(end_time - start_time).count();
    cout << "total time: " << total_duration << endl;
}
