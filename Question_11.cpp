#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;

// Function to generate a random array
vector<int> generateRandomArray(int n, int max_value = 1000) {
    vector<int> arr(n);
    for (int &num : arr) {
        num = rand() % max_value; // Random numbers in range [0, max_value]
    }
    return arr;
}

// Sequential: Function to find the sum of elements
long long sumArraySequential(const vector<int>& arr) {
    long long sum = 0;
    for (int num : arr) sum += num;
    return sum;
}

// Sequential: Function to search for an element
bool searchElementSequential(const vector<int>& arr, int key) {
    for (int num : arr) {
        if (num == key) return true;
    }
    return false;
}

// Threaded: Function to compute partial sum
void sumArrayThreaded(const vector<int>& arr, int start, int end, long long &result) {
    result = 0;
    for (int i = start; i < end; i++) {
        result += arr[i];
    }
}

// Threaded: Function to search for an element
void searchElementThreaded(const vector<int>& arr, int start, int end, int key, bool &found) {
    for (int i = start; i < end; i++) {
        if (arr[i] == key) {
            found = true;
            return;
        }
    }
    found = false;
}

int main() {
    int n, key;
    cout << "Enter array size: ";
    cin >> n;
    cout << "Enter key to search: ";
    cin >> key;

    srand(time(0)); // Seed for random numbers
    vector<int> arr = generateRandomArray(n);

    // **Sequential Execution**
    auto start = high_resolution_clock::now();
    long long sumSeq = sumArraySequential(arr);
    bool foundSeq = searchElementSequential(arr, key);
    auto end = high_resolution_clock::now();
    cout << "Sequential Sum: " << sumSeq << ", Found: " << (foundSeq ? "Yes" : "No") 
         << ", Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    // **Threaded Execution (Using 2 Threads)**
    long long sum1 = 0, sum2 = 0;
    bool found1 = false, found2 = false;

    start = high_resolution_clock::now();
    thread t1(sumArrayThreaded, ref(arr), 0, n / 2, ref(sum1));
    thread t2(sumArrayThreaded, ref(arr), n / 2, n, ref(sum2));
    t1.join();
    t2.join();
    long long totalSum = sum1 + sum2;

    thread t3(searchElementThreaded, ref(arr), 0, n / 2, key, ref(found1));
    thread t4(searchElementThreaded, ref(arr), n / 2, n, key, ref(found2));
    t3.join();
    t4.join();
    bool totalFound = found1 || found2;

    end = high_resolution_clock::now();
    cout << "Threaded Sum: " << totalSum << ", Found: " << (totalFound ? "Yes" : "No") 
         << ", Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    return 0;
}
