#include "worker.h"
#include <iostream>
#include <string>

putong::putong(int id, string name, int bumen) {
    this->m_id = id;
    this->m_name = name;
    this->bumen = bumen;
}

void putong::showinfo() {
    cout << "职工编号" << this->m_id << endl;
    cout << "职工姓名" << this->m_name << endl;
    cout<<"职工部门"<<this->getbumen()<<endl;
}
string putong::getbumen() {
    return string("普通职工");
 }