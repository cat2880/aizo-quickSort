#include <chrono>
#include "array.cpp"

using namespace std;

template<typename T>
void runProgram(Array<T>& array);

int main(){
    cout << "Choose data type:\n" << "1. int\n"
                                  << "2. float\n"
                                  << "3. char\n";
    int dataType;
    cout << "Your choice: ";
    cin >> dataType;
    switch (dataType) {
        case 1: {
            Array<int> array;
            runProgram(array);
            break;
        }
        case 2: {
            Array<float> array;
            runProgram(array);
            break;
        }
        case 3: {
            Array<char> array;
            runProgram(array);
            break;
        }default:{
            cout << "Not correct data type\n";
            break;
        }
    }
    return 0;
}

template<typename dataType>
void runProgram(Array<dataType>& array){
    bool arrayIsGenerated = false;
    double totalTime = 0;
    int totalMeasurements = 0;
    while (true){
        cout << "\nMenu:\n" << "1. Uploud from file\n"
                            << "2. Generate random array\n"
                            << "3. Show array\n"
                            << "4. Sort array\n"
                            << "5. Sort correctness checker\n"
                            << "6. Exit\n"
                            << "Choose: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:{
                cout << "Enter fileName: ";
                string filename;
                cin >> filename;
                array.loadFromFile(filename);
                arrayIsGenerated = true;
                break;
            }
            case 2:{
                cout << "Enter size of an array: ";
                int size;
                cin >> size;
                array.generateData(size);
                arrayIsGenerated = true;
                break;
            }
            case 3:{
                if (arrayIsGenerated){
                    cout << "Array: \n";
                    array.displayArray();
                } else cout << "An array has not been generated yet\n";
                break;
            }
            case 4: {
                if (arrayIsGenerated){
                    int numMeasurements, sortChoice;
                    cout << "Choose sorting method:\n"
                         << "1. Quick Sort\n"
                         << "2. Insertion Sort\n"
                         << "3. Binary Insertion Sort\n"
                         << "4. Heap Sort\n"
                         << "Choose: ";
                    cin >> sortChoice;
                    cout << "Enter number of measurements: ";
                    cin >> numMeasurements;
                    totalMeasurements += numMeasurements;
                    string sortMethodName;
                    switch (sortChoice) {
                        case 1:
                            sortMethodName = "Quick Sort";
                            break;
                        case 2:
                            sortMethodName = "Insertion Sort";
                            break;
                        case 3:
                            sortMethodName = "Binary Insertion Sort";
                            break;
                        case 4:
                            sortMethodName = "Heap Sort";
                            break;
                        default:
                            cout << "Invalid sorting method choice\n";
                            break;
                    }
                    for (int i = 0; i < numMeasurements; ++i) {
                        auto start = chrono::high_resolution_clock::now();
                        switch (sortChoice) {
                            case 1:
                                array.quickSort(0, array.size() - 1);
                                break;
                            case 2:
                                array.insertionSort();
                                break;
                            case 3:
                                array.binaryInsertionSort();
                                break;
                            case 4:
                                array.heapSort();
                                break;
                            default:
                                cout << "Invalid sorting method choice\n";
                                break;
                        }
                        auto end = chrono::high_resolution_clock::now();
                        chrono::duration<double> elapsed = end - start;
                        totalTime += elapsed.count();
                        cout << "Time elapsed for " << sortMethodName << " (measurement " << i+1 << "): " << elapsed.count() << " seconds\n";
                    }
                    double averageTime = totalTime / totalMeasurements;
                    cout << "Average Time elapsed for " << sortMethodName << ": " << averageTime << " seconds\n";
                } else cout << "First generate or load an array.\n";
                break;
            }
            case 5:{
                if (arrayIsGenerated){
                    array.sortCheck();
                } else cout << "First generate or upload the array\n";
            }
            case 6:{
                return;
            }
            default:{
                cout << "Your choice is not correct. Please try again:\n";
                break;
            }
        }
    }
}



