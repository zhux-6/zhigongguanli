#include "worker.h"



//普通职工
putong::putong(int id, string name, int bumen) {
    this->m_id = id;
    this->m_name = name;
    this->bumen = bumen;
}
worker:: ~worker() {
}

void putong::showinfo() {
    cout << "职工编号: " << this->m_id << endl;
    cout << "职工姓名: " << this->m_name << endl;
    cout<<"职工部门: "<<this->getbumen()<<endl;
}
string putong::getbumen() {
    return string("普通职工");
}

// 经理类
jingli::jingli(int id, string name, int bumen) {
    this->m_id = id;
    this->m_name = name;
    this->bumen = bumen;
}

void jingli::showinfo() {
    cout << "职工编号" << this->m_id << '\t';
    cout << "职工姓名" << this->m_name << '\t';
    cout << "职工部门" << this->getbumen() << endl;
}
string jingli::getbumen() {
    return string("经理");
}

// 老板类
boss::boss(int id, string name, int bumen) {
    this->m_id = id;
    this->m_name = name;
    this->bumen = bumen;
}

void boss::showinfo() {
    cout << "职工编号" << this->m_id << endl;
    cout << "职工姓名" << this->m_name << endl;
    cout << "职工部门" << this->getbumen() << endl;
}
string boss::getbumen() {
    return string("老板");
}