#include "workermanager.h"
#include "utils.h"
#include "worker.h"
#include <fstream>

Workermanager::Workermanager() {
    this->m_num = 0;
    this->m_array = nullptr;
    this->m_iskong = false;

    ifstream ifs(FILENAME);

    // 1. 检查文件是否存在
    if (!ifs.is_open()) {
        cout << "文件不存在！" << endl;
        this->m_iskong = true;
        return;
    }

    // 2. 检查文件是否为空

    ifs.seekg(0, ios::end);
    if (ifs.tellg() == 0) {
        cout << "文件为空！" << endl;
        this->m_iskong = true;
        ifs.close();
        return;
    }

    ifs.seekg(0, ios::beg);

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
    pause1();
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

    pause1();
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

void Workermanager::show_worker() {
    if (this->m_iskong) {
        cout << "文件不存在或者记录为空" << endl;
    } else {
        for (int i = 0; i < m_num; i++) {
            this->m_array[i]->showinfo();
        }
    }
    pause1();
    clear_screen();
}

void Workermanager::del_worker() {
    if (this->m_iskong) {
        cout << "文件不存在或记录为空，无法删除。" << endl;
    } else {
        cout << "请输入想要删除的职工ID:" << endl;
        int v_id = 0;
        cin >> v_id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int index = this->iscunzai(v_id);

        if (index != -1) {
            char confirm;
            cout << "找到职工: ";
            this->m_array[index]->showinfo();
            cout << "确定要删除吗？(Y/N): ";
            cin >> confirm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (confirm == 'Y' || confirm == 'y') {

                delete this->m_array[index];
                this->m_array[index] = nullptr;

                for (int i = index; i < this->m_num - 1; i++) {
                    this->m_array[i] = this->m_array[i + 1];
                }
                // 更新职工总人数
                this->m_num--;

                this->save();
                cout << "删除成功！" << endl;

                if (this->m_num == 0) {
                    this->m_iskong = true;
                }
            } else {
                cout << "已取消删除操作。" << endl;
            }
        } else {
            cout << "删除失败，未找到该职工！" << endl;
        }
    }
    std::cout << "按任意键继续..." << std::endl;
    std::cin.get();

    clear_screen();
}

int Workermanager::iscunzai(int id) {
    int in_num = -1;

    for (int i = 0; i < this->m_num; i++) {
        if (this->m_array[i]->m_id == id) {
            in_num = i;
            break;
        }
    }
    return in_num;
}

void Workermanager::change_worker() {
    if (this->m_iskong) {
        cout << "文件不存在或记录为空" << endl;
    } else {
        cout << "输入要修改职工的ID" << endl;
        int v_id;
        cin >> v_id;
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int index = this->iscunzai(v_id);

        if (index != -1) {
            char confirm;
            cout << "找到职工: ";

            this->m_array[index]->showinfo();

            cout << "确定要修改吗？(Y/N): ";

            cin >> confirm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (confirm == 'Y' || confirm == 'y') {

                delete this->m_array[index];
                this->m_array[index] = nullptr;

                int new_id = 0;
                string new_name = "";
                int new_bumen = 0;

                cout << "输入新职工编号" << endl;
                cin >> new_id;

                cout << "输入新职工姓名" << endl;
                cin >> new_name;

                cout << "选择岗位" << endl;
                cout << "1、普通职工" << endl;
                cout << "2、经理" << endl;
                cout << "3、老板" << endl;

                cin >> new_bumen;

                worker *wk = nullptr;

                switch (new_bumen) {
                case 1:
                    wk = new putong(new_id, new_name, new_bumen);
                    break;
                case 2:
                    wk = new jingli(new_id, new_name, new_bumen);
                    break;
                case 3:
                    wk = new boss(new_id, new_name, new_bumen);
                    break;
                default:
                    break;
                }

                this->m_array[index] = wk;

                cout << "修改成功" << this->m_array[index]->getbumen() << endl;

                this->save();

            } else {
                cout << "已取消修改" << endl;
            }
        }
    }
    pause1();
    clear_screen();
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