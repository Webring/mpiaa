#define TESTING false

#if TESTING == true
#include "duplicates.h"

#define CATCH_CONFIG_RUNNER

#include "../catch.hpp"

int main(int argc, char **argv) {
    int result = Catch::Session().run(argc, argv);
    return result;
}
#else

#include "iostream"
#include "chrono"
#include "duplicates.h"

#define NUMBER_OF_VALUES 100000

using namespace std;
using namespace std::chrono;

int random_in_range(int start = 0, int end = RAND_MAX) {
    return rand() % (end - start + 1) + start;
}

int main() {
    srand(50);

    vector<int> values;
    for (int i = 0; i < NUMBER_OF_VALUES; i++) {
        int new_value = random_in_range(0, NUMBER_OF_VALUES);
        values.push_back(new_value);
    }

    auto start_time = steady_clock::now();

    bool has_duplicates_flag = has_duplicates(values);

    auto has_duplicates_time = steady_clock::now();

    vector<int> duplicates = get_duplicates(values);

    auto get_duplicates_time = steady_clock::now();

    cout << "has_duplicates: " << has_duplicates_flag << endl;
    cout << "number of duplicates: " << duplicates.size() << endl;

    double has_duplicates_duration = duration<double>(has_duplicates_time - start_time).count();
    double get_duplicates_duration = duration<double>(get_duplicates_time - has_duplicates_time).count();

    cout << "has time: " << has_duplicates_duration << endl;
    cout << "get time: " << get_duplicates_duration << endl;
    return 0;
}

#endif