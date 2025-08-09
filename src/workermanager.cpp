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
        // cout << "文件不存在！" << endl;
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
            while (true) {
                bool idchongfu = false; 
                cout << "输入第" << i + 1 << "个新职工编号" << endl;
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 


                if (this->iscunzai(id) != -1) {
                    idchongfu = true;
                }

                if (!idchongfu) {
                    for (int j = 0; j < i; j++) {

                        if (newspace[this->m_num + j]->m_id == id) {
                            idchongfu = true;
                            break;
                        }
                    }
                }

                if (idchongfu) {
                    cout << "编号与已有职工或本次添加的职工重复，请重新输入。" << endl;
                } else {
                    break; // ID 不重复，跳出循环
                }
            }
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
        cout << "文件不存在或记录为空，无法修改。" << endl;
        pause1();
        clear_screen();
        return;
    }

    cout << "请输入要修改职工的ID:" << endl;
    int v_id;
    cin >> v_id;

    int index = this->iscunzai(v_id);

    if (index != -1) {
        cout << "找到职工：" << endl;
        this->m_array[index]->showinfo();

        char confirm;
        cout << "确定要修改吗？(Y/N):";
        cin >> confirm;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (confirm == 'Y' || confirm == 'y') {
            int new_id = 0;
            string new_name = "";
            int new_bumen = 0;

            // 1. 获取并验证新 ID
            while (true) {
                cout << "输入新职工编号：" << endl;
                cin >> new_id;

                if (this->iscunzai(new_id) != -1 && this->m_array[index]->m_id != new_id) {
                    cout << "编号与已有职工重复，请重新输入。" << endl;
                } else {
                    break;
                }
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "输入新职工姓名：" << endl;

            getline(cin, new_name);

            while (true) {
                cout << "选择新岗位：" << endl;
                cout << "1、普通职工" << endl;
                cout << "2、经理" << endl;
                cout << "3、老板" << endl;
                cin >> new_bumen;

                if (new_bumen >= 1 && new_bumen <= 3) {
                    break;
                } else {
                    cout << "输入有误，请重新选择。" << endl;
                }
            }

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
            }

            if (wk != nullptr) {
                delete this->m_array[index];
                this->m_array[index] = wk;
                this->save();
                cout << "修改成功！" << endl;
            } else {
                cout << "修改失败，无法创建新职工对象。" << endl;
            }

        } else {
            cout << "已取消修改操作。" << endl;
        }

    } else {
        cout << "未找到该职工，无法修改！" << endl;
    }

    pause1();
    clear_screen();
}

void Workermanager::find_worker() {
    if (this->m_iskong) {
        cout << "文件不存在或记录为空" << endl;

    } else {

        cout << "请输入要查找的方式：" << endl;
        cout << "1、按ID查找" << endl;
        cout << "2、按姓名查找" << endl;

        int select = 0;
        cin >> select;

        if (select == 1) {
            int iid;
            cout << "输入查找职工ID" << endl;
            cin >> iid;

            int index = iscunzai(iid);

            if (index != -1) {
                cout << "查找成功，信息如下:" << endl;
                cout << *this->m_array[index];
            } else {

                cout << "查无此人" << endl;
            }
        } else if (select == 2) {

            string iname;
            cout << "输入要查找的姓名" << endl;
            cin >> iname;

            bool flag = false;

            for (int i = 0; i < m_num; i++) {
                if (m_array[i]->m_name == iname) {

                    cout << *this->m_array[i];

                    flag = true;
                }
            }
            if (flag == false) {
                cout << "查无此人" << endl;
            }
        } else {
            cout << "输入选项有误" << endl;
        }
    }
    pause1();
    clear_screen();
}

void Workermanager::paixu() {
    if (this->m_iskong) {
        cout << "文件不存在或记录为空" << endl;
        pause1();
        clear_screen();
    } else {
        cout << "选择排序方式： 1、按职工号升序\t2、按职工号降序" << endl;
        int select = 0;
        while (true) {

            cin >> select;
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (select == 1 || select == 2) {
                break;
            } else {
                cout << "输入有误，请重新选择。" << endl;
            }
        }                                                

        for (int i=0; i < m_num; i++) {
            int minormax = i;

            for (int j = i + 1; j < m_num; j++) {

                if (select == 1) { // 升序

                    if (this->m_array[minormax]->m_id > this->m_array[j]->m_id) {

                        minormax = j;
                    }
                } else { // 降序

                    if (this->m_array[minormax]->m_id < this->m_array[j]->m_id) {

                        minormax = j;
                    }
                }
            }
            if (i != minormax) {

                worker *temp = this->m_array[i];
                this->m_array[i] = this->m_array[minormax];
                this->m_array[minormax] = temp;
            }
        }
        cout << "排序成功！排序后结果为：" << endl;

        this->save();
        this->show_worker();
    }
}

Workermanager::~Workermanager() {
    if (this->m_array != nullptr) {
        for (int i = 0; i < m_num; i++) {

            delete this->m_array[i];
        }

        delete[] this->m_array;

        this->m_array = nullptr;
    }
}