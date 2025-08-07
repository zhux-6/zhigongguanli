#pragma once
#include "worker.h"
#include <fstream>
#include <iostream>

#define FILENAME "record.txt"

using namespace std;

class Workermanager {
  public:
    int m_num;
    worker**m_array;
    Workermanager();
    void showmenu();
    void exitexe();
    void addnum();
    void save();
    ~Workermanager();
};