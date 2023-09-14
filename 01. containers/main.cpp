#include <iostream>
#include <algorithm>
#include <chrono>

#include "vector"
#include "list"
#include "set"
#include "unordered_set"

#define N 100000000

using namespace std;
using namespace std::chrono;

int random_in_range(int start = 0, int end = RAND_MAX) {
    return rand() % (end - start + 1) + start;
}


int main() {
    unordered_set<int> object;

    auto start_time = steady_clock::now();

    for (int i = 0; i < N; i++) {
        int new_value = random_in_range(0, N);
        //object.push_back(new_value);
        //object.insert(object.begin(), new_value);
        object.insert(new_value);
    }

    auto write_time = steady_clock::now();

    for (int i = 0; i < N; i++) {
        object.find(i);
        //find(object.begin(), object.end(), i);
    }

    auto find_time = steady_clock::now();

    cout << "write: " << duration<double>(write_time - start_time).count() << " sec." << endl;
    cout << "Search: " << duration<double>(find_time - write_time).count() << " sec." << endl;


    return 0;
}
