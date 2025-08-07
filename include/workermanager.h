#pragma once
#include "worker.h"
#include <fstream>
#include <iostream>

#define FILENAME "record.txt"

using namespace std;

class Workermanager {
  public:
    int m_num;

    worker **m_array;

    Workermanager();

    void showmenu();//显示菜单

    void exitexe();//退出

    void addnum();//加人

    void save();//保存到本地

    bool m_iskong;

    int get_innum();//获取本地人数

    void begin_worker();//本地获取初始化
    
    ~Workermanager();
};