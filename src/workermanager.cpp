#include "workermanager.h"
#include "utils.h"
#include "worker.h"
#include <fstream>

Workermanager::Workermanager() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    if (!ifs.is_open()) {
        // cout << "文件不存在！" << endl;
        m_num = 0;
        m_array = nullptr;
        m_iskong = true;
        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    if (ifs.eof()) {
        // cout << "文件为空！" << endl;
        m_num = 0;
        m_array = nullptr;
        m_iskong = true;
        ifs.close();
        return;
    }
    ifs.close();

    int num = this->get_innum();
    // cout << "职工个数为" << num << endl;
    this->m_num = num;

    this->m_array = new worker *[this->m_num];
    this->begin_worker(); // 初始化数据

    //     for (int i = 0; i < this->m_num; i++) {
    //     cout<<this->m_array[i]->m_id<<"   "<<this->m_array[i]->m_name<<"   "<<this->m_array[i]->bumen<<endl;
    //     }
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
    pause();
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
        this->save();
        this->m_iskong = false;

    } else {
        cout << "输入有误" << endl;
    }

    pause();
    clear_screen();
}

void Workermanager::save() {
    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    for (int i = 0; i < m_num; i++) {
        ofs << this->m_array[i]->m_id << '\t' << this->m_array[i]->m_name << '\t' << this->m_array[i]->bumen << endl;
    }

    ofs.close();
}

int Workermanager::get_innum() {
    ifstream ifs2;
    ifs2.open(FILENAME, ios::in);

    int d_id;
    string d_name;
    int d_bumen;

    int num = 0;

    while (ifs2 >> d_id && ifs2 >> d_name && ifs2 >> d_bumen) {
        num++;
    }
    ifs2.close();
    return num;
}

void Workermanager::begin_worker() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int i_id;
    string i_name;
    int i_bumen;

    int shu = 0;

    while (ifs >> i_id && ifs >> i_name && ifs >> i_bumen) {
        worker *wkr = nullptr;

        if (i_bumen == 1) {
            wkr = new putong(i_id, i_name, i_bumen);
        } else if (i_bumen == 2) {
            wkr = new jingli(i_id, i_name, i_bumen);
        } else {
            wkr = new boss(i_id, i_name, i_bumen);
        }
        this->m_array[shu] = wkr;
        shu++;
    }
    ifs.close();
}

Workermanager::~Workermanager() {
    if (this->m_array != nullptr) {
        for (int i = 0; i < m_num; i++) {
            // 逐个释放每个worker对象
            delete this->m_array[i];
        }
        // 释放指针数组本身
        delete[] this->m_array;
        this->m_array = nullptr;
    }
}