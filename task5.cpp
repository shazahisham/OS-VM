#include <iostream>
#include <vector>
using namespace std;

float FCFS(vector<int> arrival, vector<int> burst, int n) {
    vector<int> waiting(n);
    waiting[0] = 0;

    for (int i = 1; i < n; i++) {
        waiting[i] = burst[i - 1] + waiting[i - 1];
    }

    float total = 0;
    for (int i = 0; i < n; i++)
        total += waiting[i];

    return total / n;
}