#include "collatz.h"
#include <fstream>

std::unordered_map<int, int> CollatzData::memo;
std::vector<std::pair<int, int>> CollatzData::iteration_data;
std::unordered_map<int, std::vector<int>> CollatzData::sequences;

/*
    Calculates the number of iterations required for a given integer n to reach 1.
    Uses memoization for skipping calculations for numbers already computed.
*/
int CollatzData::collatz_iterations(int n) {
    if (memo.contains(n)) {
        return memo[n];
    }

    int iterations = 0;
    std::vector<int> sequence;
    long long current = n;

    sequence.push_back(n);
    while (current != 1) {
        if (current % 2 == 0) {
            current /= 2;
        } else {
            current = 3 * current + 1;
        }
        sequence.push_back(static_cast<int>(current));
        iterations++;

        if (current < n && memo.contains(static_cast<int>(current))) {
            iterations += memo[static_cast<int>(current)];
            break;
        }
    }

    memo[n] = iterations;
    sequences[n] = sequence;
    iteration_data.emplace_back(n, iterations);

    return iterations;
}

std::vector<int> CollatzData::get_sequence(int n) {
    if (!sequences.contains(n)) {
        collatz_iterations(n);
    }
    return sequences[n];
}

void CollatzData::save_to_file(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& [number, seq] : sequences) {
        file << number << ": ";
        for (int value : seq) {
            file << value << " ";
        }
        file << "\n";
    }
    file.close();
}

const std::vector<std::pair<int, int>>& CollatzData::get_iteration_data() {
    return iteration_data;
}