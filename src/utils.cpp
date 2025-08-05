#include "utils.h"
#include <Windows.h>
#include <iostream>

void useUTF8() {
  SetConsoleOutputCP(65001);
  SetConsoleCP(65001);
}

void pause() {
  std::cout << "按回车继续..." << std::endl;
  std::cin.get();

}