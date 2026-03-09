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