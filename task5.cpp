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
float SJF(vector<int> arrival, vector<int> burst, int n) {
    vector<bool> done(n, false);
    vector<int> waiting(n, 0);

    int completed = 0, time = 0;

    while (completed < n) {
        int idx = -1, minBurst = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && arrival[i] <= time && burst[i] < minBurst) {
                minBurst = burst[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        waiting[idx] = time - arrival[idx];
        time += burst[idx];
        done[idx] = true;
        completed++;
    }

    float total = 0;
    for (int i = 0; i < n; i++)
        total += waiting[i];

    return total / n;
}
float RoundRobin(vector<int> arrival, vector<int> burst, int n, int quantum) {
    vector<int> remaining = burst;
    vector<int> waiting(n, 0);

    int time = 0;

    while (true) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                done = false;

                if (remaining[i] > quantum) {
                    time += quantum;
                    remaining[i] -= quantum;
                } else {
                    time += remaining[i];
                    waiting[i] = time - burst[i] - arrival[i];
                    remaining[i] = 0;
                }
            }
        }

        if (done) break;
    }

    float total = 0;
    for (int i = 0; i < n; i++)
        total += waiting[i];

    return total / n;
}
int main() {
    int n = 4;

    vector<int> arrival = {0, 1, 2, 3};
    vector<int> burst = {5, 3, 8, 6};

    float fcfs = FCFS(arrival, burst, n);
    float sjf = SJF(arrival, burst, n);
    float rr = RoundRobin(arrival, burst, n, 2);

    cout << "Average Waiting Times:\n";
    cout << "FCFS: " << fcfs << endl;
    cout << "SJF: " << sjf << endl;
    cout << "RR : " << rr << endl;

    cout << "\nBar Chart:\n";

    cout << "FCFS: ";
    for (int i = 0; i < fcfs; i++) cout << "*";
    cout << endl;

    cout << "SJF : ";
    for (int i = 0; i < sjf; i++) cout << "*";
    cout << endl;

    cout << "RR  : ";
    for (int i = 0; i < rr; i++) cout << "*";
    cout << endl;

    return 0;
}