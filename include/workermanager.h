#pragma once
#include "worker.h"
#include <iostream>

using namespace std;

class Workermanager {
  public:
    int m_num;
    worker**m_array;
    Workermanager();
    void showmenu();
    void exitexe();
    void addnum();
    ~Workermanager();
};