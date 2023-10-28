#include <iostream>
#include "vector"
#include "chrono"
#include "lcs.h"

#define N 100

using namespace std;
using namespace std::chrono;


const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

int random_in_range(int start = 0, int end = RAND_MAX) {
    return rand() % (end - start + 1) + start;
}

string string_generator(int length = 10) {
    string result = "";
    for (int i = 0; i < length; i++) {
        result += ALPHABET[random_in_range(0, ALPHABET.length() - 1)];
    }
    return result;
}

int main() {
    srand(50);

    vector<string> words1;
    vector<string> words2;

    for (int i = 0; i < N; i++) {
        words1.push_back(string_generator(10));
        words2.push_back(string_generator(5));
    }

    auto start_time = steady_clock::now();

    for (int i = 0; i < N; i++) {
        lcs(words1[i], words2[i]);
    }

    auto end_time = steady_clock::now();
    double total_duration = duration<double>(end_time - start_time).count();
    cout << "total time: " << total_duration << endl;

}
