#include <iostream>
#include <filesystem>
#include <map>

using namespace std;
using namespace std::filesystem;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Usage: program <directory_path> <bin_width>\n";
        return 1;
    }

    string path = argv[1];
    long long binWidth = stoll(argv[2]);

    if (!exists(path) || !is_directory(path)) {
        cout << "Invalid directory.\n";
        return 1;
    }

    if (binWidth <= 0) {
        cout << "Bin width must be positive.\n";
        return 1;
    }
    map<long long, int> histogram;

    for (const auto& entry : recursive_directory_iterator(path)) {
        try {
            if (is_regular_file(entry.path())) {
                long long size = file_size(entry.path());
                long long binStart = (size / binWidth) * binWidth;
                histogram[binStart]++;
            }
        } catch (...) {
        }
    }
