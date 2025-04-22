#include <iostream>
#include <vector>
using namespace std;

void printAllocation(const vector<int>& allocation) {
    for (size_t i = 0; i < allocation.size(); i++) {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " is allocated to block " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " is not allocated" << endl;
    }
    cout << endl;
}

void firstFit(const vector<int>& blockSize, const vector<int>& processSize) {
    vector<int> allocation(processSize.size(), -1);
    vector<int> blocks = blockSize;

    for (size_t i = 0; i < processSize.size(); i++) {
        for (size_t j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processSize[i]) {
                allocation[i] = j;
                blocks[j] -= processSize[i];
                break;
            }
        }
    }

    cout << "\n--- First Fit Allocation ---\n";
    printAllocation(allocation);
}

void bestFit(const vector<int>& blockSize, const vector<int>& processSize) {
    vector<int> allocation(processSize.size(), -1);
    vector<int> blocks = blockSize;

    for (size_t i = 0; i < processSize.size(); i++) {
        int bestIdx = -1;
        for (size_t j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processSize[i]) {
                if (bestIdx == -1 || blocks[j] < blocks[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blocks[bestIdx] -= processSize[i];
        }
    }

    cout << "\n--- Best Fit Allocation ---\n";
    printAllocation(allocation);
}

void worstFit(const vector<int>& blockSize, const vector<int>& processSize) {
    vector<int> allocation(processSize.size(), -1);
    vector<int> blocks = blockSize;

    for (size_t i = 0; i < processSize.size(); i++) {
        int worstIdx = -1;
        for (size_t j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processSize[i]) {
                if (worstIdx == -1 || blocks[j] > blocks[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blocks[worstIdx] -= processSize[i];
        }
    }

    cout << "\n--- Worst Fit Allocation ---\n";
    printAllocation(allocation);
}

void nextFit(const vector<int>& blockSize, const vector<int>& processSize) {
    vector<int> allocation(processSize.size(), -1);
    vector<int> blocks = blockSize;
    int startIdx = 0;
    int m = blocks.size();

    for (size_t i = 0; i < processSize.size(); i++) {
        int count = 0;
        int j = startIdx;
        while (count < m) {
            if (blocks[j] >= processSize[i]) {
                allocation[i] = j;
                blocks[j] -= processSize[i];
                startIdx = j;
                break;
            }
            j = (j + 1) % m;
            count++;
        }
    }

    cout << "\n--- Next Fit Allocation ---\n";
    printAllocation(allocation);
}

int main() {
    int m, n, choice;
    vector<int> blockSize, processSize;

    cout << "Enter number of memory blocks: ";
    cin >> m;
    blockSize.resize(m);
    cout << "Enter sizes of memory blocks:\n";
    for (int i = 0; i < m; i++) {
        cout << "Block " << i + 1 << ": ";
        cin >> blockSize[i];
    }

    cout << "\nEnter number of processes: ";
    cin >> n;
    processSize.resize(n);
    cout << "Enter sizes of processes:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ": ";
        cin >> processSize[i];
    }

    do {
        cout << "\n========== Memory Allocation Menu ==========\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Next Fit\n";
        cout << "5. Exit\n";
        cout << "Choose an option (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                firstFit(blockSize, processSize);
                break;
            case 2:
                bestFit(blockSize, processSize);
                break;
            case 3:
                worstFit(blockSize, processSize);
                break;
            case 4:
                nextFit(blockSize, processSize);
                break;
            case 5:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}



