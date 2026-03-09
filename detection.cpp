#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int main() {
    ifstream file("input.txt");

    int n, m;
    file >> n >> m;
    vector<int> E(m);
    vector<vector<int>> C(n, vector<int>(m));
    vector<vector<int>> R(n, vector<int>(m));
    vector<int> A(m);
        for (int i = 0; i < m; i++) {
        file >> E[i];
    }
        for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            file >> C[i][j];
        }
    }
        for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            file >> R[i][j];
        }
    }