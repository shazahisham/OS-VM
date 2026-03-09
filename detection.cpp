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
    for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += C[i][j];
        }
        A[j] = E[j] - sum;
}
    vector<bool> finish(n, false);
    bool progress = true;
        while (progress) {
        progress = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canRun = true;

                for (int j = 0; j < m; j++) {
                    if (R[i][j] > A[j]) {
                        canRun = false;
                        break;
                    }
                }
            if (canRun) {
                    for (int j = 0; j < m; j++) {
                        A[j] += C[i][j];
                    }

                    finish[i] = true;
                    progress = true;
                }
                            }
        }
    }
        bool deadlock = false;

    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            deadlock = true;
            break;
        }
    }

