#include "utils.h"

void pause1() {
    std::cout << "按任意键继续..." << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cin.get();
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    // Linux, macOS, etc.

    system("clear");
#endif
}