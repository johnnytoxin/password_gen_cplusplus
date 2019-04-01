#include "pch.h"
#include <Windows.h>
//
#include "Generator.h"

using namespace std;

int main(int argc, char* argv[])
{
    SetConsoleTitle(L"Johnny Toxin's Password Generator v1.0.0.0");

    // Initialize random with seed
    srand(GetTickCount());
    Generator generator;
    // Get the executable path
    // Source: http://www.cplusplus.com/forum/windows/49104/#msg266992
    char executablePath[255];
    _fullpath(executablePath, argv[0], sizeof(executablePath));
    generator.run(executablePath);

    return 0;
}
