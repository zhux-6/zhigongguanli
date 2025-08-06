#include "workermanager.h"
#include "utils.h"
#include "worker.h"
#include <cstdlib>
#include <iostream>

Workermanager::Workermanager() {
    m_num = 0;
    m_array = nullptr;
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



void Workermanager::exitexe() {
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}




void Workermanager ::addnum() {
    cout << "输入要添加的数量" << endl;
    int cinnum = 0;
    cin >> cinnum;

    if (cinnum > 0) {
        int newsize = this->m_num + cinnum;
        worker **newspace = new worker *[newsize];

        if (this->m_array != nullptr) {
            for (int i = 0; i < m_num; i++) {
                newspace[i] = this->m_array[i];
            }
        }

        for (int i = 0; i < cinnum; i++) {
            int id;
            string name;
            int bumen;

            cout << "输入第" << i + 1 << "个新职工编号" << endl;
            cin >> id;

            cout << "输入第" << i + 1 << "个新职工姓名" << endl;
            cin >> name;

            cout << "选择岗位" << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> bumen;

            worker *wk = nullptr;
            switch (bumen) {
            case 1:
                wk = new putong(id, name, bumen);
                break;
            case 2:
                wk = new jingli(id, name, bumen);
                break;
            case 3:
                wk = new boss(id, name, bumen);
                break;
            default:
                break;
            }

            newspace[this->m_num + i] = wk;
        }
        delete[] this->m_array;

        this->m_array = newspace;
        this->m_num = newsize;

        cout << "成功添加" << cinnum << "名新职工" << endl;

    } else {
        cout << "输入有误" << endl;
    }

    system("pause");
    system("cls");
}