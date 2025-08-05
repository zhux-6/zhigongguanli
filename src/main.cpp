#include "utils.h"
#include "workermanager.h"
#include <iostream>

int main() {
    useUTF8();

    Workermanager test;
    test.showmenu();

    pause();
    return 0;
}