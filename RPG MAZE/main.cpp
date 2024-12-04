#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#include "fairy.h"

using namespace std;

// To avoid encoding issues on Windows, while Mac/Linux is fine with this issue
void setupWindows() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif 
}

int main() {

    setupWindows();

    Fairy fairy;

    // fairy.readHollowFromFile("custom.txt");
    fairy.readHollowFromFile();
    fairy.startConnection();
    
}