#ifndef COLLATZ_H
#define COLLATZ_H

#include <vector>
#include <unordered_map>
#include <string>

class CollatzData {
public:
    static int collatz_iterations(int n);
    static std::vector<int> get_sequence(int n);
    static void save_to_file(const std::string& filename);
    static const std::vector<std::pair<int, int>>& get_iteration_data();

private:
    static std::unordered_map<int, int> memo;
    static std::vector<std::pair<int, int>> iteration_data;
    static std::unordered_map<int, std::vector<int>> sequences;
};

#endif // COLLATZ_H