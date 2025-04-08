#include <iostream>

using namespace std;

int main() {
    system("g++ .\\simplex_interpretor.cpp -o simplex_interpretor");
    system(".\\simplex_interpretor");
    system("g++ .\\translated_code.cpp -o translated_code");
    system(".\\translated_code");
    system("pause");
    return 0;
}
