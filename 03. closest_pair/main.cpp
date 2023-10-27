#include "closest_pair.h"

#include "iostream"
#include "chrono"

#define NUMBER_OF_VALUES 10000

using namespace std;
using namespace std::chrono;

int random_in_range(int start = 0, int end = RAND_MAX) {
    return rand() % (end - start + 1) + start;
}

int main() {
    srand(50);

    vector<Point> values;
    for (int i = 0; i < NUMBER_OF_VALUES; i++) {
        double x = random_in_range(-NUMBER_OF_VALUES, NUMBER_OF_VALUES);
        double y = random_in_range(-NUMBER_OF_VALUES, NUMBER_OF_VALUES);

        values.push_back(Point(x, y));
    }

    auto start_time = steady_clock::now();

    auto closest_pair_points = closest_pair(values);

    auto end_time = steady_clock::now();


    double total_duration = duration<double>(end_time - start_time).count();

    cout << "total time: " << total_duration << endl;
    return 0;
}
