#include "lcs.h"
#include <set>
#include <algorithm>

#define USE_OPTIMAL_ALGORITHM true

using namespace std;

#if USE_OPTIMAL_ALGORITHM

string LCS(const string &str1, const string &str2, int len1, int len2) {

    // Создаем двумерный массив для хранения длин LCS
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

    // Заполняем массив dp
    for (int current_len_1 = 1; current_len_1 <= len1; current_len_1++) {
        for (int current_len_2 = 1; current_len_2 <= len2; current_len_2++) {
            if (str1[current_len_1 - 1] == str2[current_len_2 - 1]) {
                dp[current_len_1][current_len_2] = dp[current_len_1 - 1][current_len_2 - 1] + 1;
            } else {
                dp[current_len_1][current_len_2] = max(dp[current_len_1 - 1][current_len_2], dp[current_len_1][current_len_2 - 1]);
            }
        }
    }

    // Восстанавливаем LCS из массива dp
    int current_len_1 = len1, current_len_2 = len2;
    string lcs;
    while (current_len_1 > 0 and current_len_2 > 0) {
        if (str1[current_len_1 - 1] == str2[current_len_2 - 1]) {
            lcs = str1[current_len_1 - 1] + lcs;
            current_len_1--;
            current_len_2--;
        } else if (dp[current_len_1 - 1][current_len_2] > dp[current_len_1][current_len_2 - 1]) {
            current_len_1--;
        } else {
            current_len_2--;
        }
    }

    return lcs;
}

/*
string LCS(const string &string_1, const string &string_2, int string_1_length, int string_2_length) {
    if (string_1_length == 0 or string_2_length == 0) {
        return "";
    }

    if (string_1[string_1_length - 1] == string_2[string_2_length - 1]) {
        return LCS(string_1, string_2, string_1_length - 1, string_2_length - 1) + string_1[string_1_length - 1];
    } else {
        string left = LCS(string_1, string_2, string_1_length - 1, string_2_length);
        string right = LCS(string_1, string_2, string_1_length, string_2_length - 1);

        if (left.size() > right.size()) {
            return left;
        } else {
            return right;
        }
    }
}
*/
#else

void find_all_subsequences(string str, string current, int index, set<string> &subsequences) {
    if (index == str.length()) {
        subsequences.insert(current);
        return;
    }

    find_all_subsequences(str, current + str[index], index + 1, subsequences);

    find_all_subsequences(str, current, index + 1, subsequences);
}

string LCS(const string &string_1, const string &string_2, int string_1_length, int string_2_length) {
    set<string> seq_1;
    set<string> seq_2;

    find_all_subsequences(string_1, "", 0, seq_1);
    find_all_subsequences(string_2, "", 0, seq_2);

    set<string> intersect;
    set_intersection(seq_1.begin(), seq_1.end(), seq_2.begin(), seq_2.end(), inserter(intersect, intersect.begin()));

    string max_string = "";
    for (string current_string: intersect) {
        if (current_string.length() > max_string.length()) {
            max_string = current_string;
        }
    }
    return max_string;
}

#endif


string lcs(const string &first, const string &second) {
    return LCS(first, second, first.length(), second.length());
}
