#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include "../inc/SimpleCalculator.h"
#include "../inc/BasicOperations.h"


using namespace std;

int main() {
    SimpleCalculator calc;
    string fileName;
    cout << "Enter the name of the file: ";
    getline(std::cin, fileName);
    calc.fileExecution(fileName);
    this_thread::sleep_for(std::chrono::minutes(5));
    return 0;
}