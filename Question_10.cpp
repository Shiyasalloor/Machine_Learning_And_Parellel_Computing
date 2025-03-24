#include <iostream>
#include <thread>

using namespace std;

// Function to print first n natural numbers
void printNaturalNumbers(int n) {
    for (int i = 1; i <= n; i++) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    // Create a thread to execute the function
    thread t(printNaturalNumbers, n);

    // Wait for the thread to complete execution
    t.join();

    return 0;
}
