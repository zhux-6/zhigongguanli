#include "worker.h"

// 普通职工
putong::putong(int id, string name, int bumen) {
    this->m_id = id;
    this->m_name = name;
    this->bumen = bumen;
}
worker::~worker() {
}

void putong::showinfo() const {
    cout << "职工编号: " << this->m_id << '\t';
    cout << "职工姓名: " << this->m_name << '\t';
    cout << "职工部门: " << this->getbumen() << endl;
}
string putong::getbumen() const {
    return string("普通职工");
}

// 经理类
jingli::jingli(int id, string name, int bumen) {
    this->m_id = id;
    this->m_name = name;
    this->bumen = bumen;
}

void jingli::showinfo() const {
    cout << "职工编号: " << this->m_id << '\t';
    cout << "职工姓名: " << this->m_name << '\t';
    cout << "职工部门: " << this->getbumen() << endl;
}
string jingli::getbumen() const {
    return string("经理");
}

// 老板类
boss::boss(int id, string name, int bumen) {
    this->m_id = id;
    this->m_name = name;
    this->bumen = bumen;
}

void boss::showinfo() const {
    cout << "职工编号: " << this->m_id << '\t';
    cout << "职工姓名: " << this->m_name << '\t';
    cout << "职工部门: " << this->getbumen() << endl;
}
string boss::getbumen() const {
    return string("老板");
}

std::ostream &operator<<(std::ostream &os, const worker &w) {
    os << "职工编号: " <<w.m_id << '\t' << "职工姓名: " << w.m_name << '\t' << "职工部门: " << w.getbumen() << endl;
    return os;
}