#include "workermanager.h"
#include <iostream>

Workermanager::Workermanager() {
}
Workermanager::~Workermanager() {
}
void Workermanager::showmenu() {
    cout << "0.退出程序" << endl;
    cout << "1.添加职工信息" << endl;
    cout << "2.显示职工信息" << endl;
    cout << "3.删除离职职工" << endl;
    cout << "4.修改职工信息" << endl;
    cout << "5.查找职工信息" << endl;
    cout << "6.按照编号排序" << endl;
    cout << "7.清空所有文档" << endl;
    
}