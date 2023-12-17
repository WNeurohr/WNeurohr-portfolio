#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class GroceryTracker {
private:
    map<string, int> itemFrequency;

public:
    void readInputFile(const string& filename) {
        ifstream inputFile(filename);
        string item;

        if (inputFile.is_open()) {
            while (getline(inputFile, item)) {
                if (!item.empty()) {
                    itemFrequency[item]++;
                }
            }
            inputFile.close();
        }
        else {
            cout << "Unable to open file: " << filename << endl;
        }
    }

    void writeFrequencyFile(const string& filename) {
        ofstream outputFile(filename);

        if (outputFile.is_open()) {
            for (const auto& pair : itemFrequency) {
                outputFile << pair.first << " " << pair.second << endl;
            }
            outputFile.close();
        }
        else {
            cout << "Unable to open file for writing: " << filename << endl;
        }
    }

    void searchItem(const string& item) {
        auto it = itemFrequency.find(item);
        if (it != itemFrequency.end()) {
            cout << "Frequency of '" << item << "': " << it->second << endl;
        }
        else {
            cout << "Item '" << item << "' not found." << endl;
        }
    }

    void printItemFrequencies() {
        cout << "Item Frequencies:" << endl;
        for (const auto& pair : itemFrequency) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

    void printHistogram() {
        cout << "Item Histogram:" << endl;
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};
void showMenu() {
    cout << "1. Search for an item" << endl;
    cout << "2. Print frequency of all items" << endl;
    cout << "3. Print histogram" << endl;
    cout << "4. Exit" << endl;
}

int main() {
    int choice;
    bool running = true;
    GroceryTracker tracker;

    tracker.readInputFile("CS210_Project_Three_Input_File.txt");

    while (running) {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // Clears the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discards the input buffer
            cout << "Invalid input. Please try again." << endl;
            continue;
        }

        switch (choice) {
        case 1: {
            string item;
            cout << "Enter the item to search for: ";
            cin >> item;
            tracker.searchItem(item);
            break;
        }
        case 2:
            tracker.printItemFrequencies();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            running = false;
            tracker.writeFrequencyFile("frequency.dat");
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
