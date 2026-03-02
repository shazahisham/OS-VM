#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

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
int simulateAging(vector<int> &references, int numFrames) {
    vector<Frame> frames(numFrames);
    int pageFaults = 0;

    for (int i = 0; i < references.size(); i++) {
        int page = references[i];
        bool hit = false;

        for (int j = 0; j < numFrames; j++) {
            if (frames[j].pageNumber == page) {
                frames[j].referenceBit = true;
                hit = true;
                break;
            }
        }

        if (!hit) {
            pageFaults++;
            int victim = 0;

            for (int j = 0; j < numFrames; j++) {
                if (frames[j].pageNumber == -1) {
                    victim = j;
                    break;
                }
            }

            if (frames[victim].pageNumber != -1) {
                int minCounter = frames[0].counter;
                victim = 0;
                for (int j = 1; j < numFrames; j++) {
                    if (frames[j].counter < minCounter) {
                        minCounter = frames[j].counter;
                        victim = j;
            }
            }
            }

            frames[victim].pageNumber = page;
            frames[victim].counter = 0;
            frames[victim].referenceBit = true;
        }

        for (int j = 0; j < numFrames; j++) {
            frames[j].counter >>= 1;
            if (frames[j].referenceBit) {
                frames[j].counter |= 128;
                frames[j].referenceBit = false;
    }
    }
    }

    return pageFaults;
}