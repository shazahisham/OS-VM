#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Frame {
public:
    int pageNumber;
    unsigned int counter;
    bool referenceBit;

    Frame() {
        pageNumber = -1;
        counter = 0;
        referenceBit = false;
    }
};

vector<int> readReferences(string filename) {
    vector<int> references;
    ifstream file(filename);

    if (!file) {
        cout << "Cannot open file." << endl;
        exit(1);
    }

    int page;
    while (file >> page) {
        references.push_back(page);
    }

    file.close();
    return references;
}

int main() {
    string filename;
    cout << "Enter reference file name: ";
    cin >> filename;

    vector<int> references = readReferences(filename);

    cout << "Total references read: " << references.size() << endl;

    return 0;
}