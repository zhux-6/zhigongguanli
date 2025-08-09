
#include "utils.h"
#include "worker.h"
#include "workermanager.h"
#include <iostream>

using namespace std;

int main() {

    Workermanager wm;
    int choice = 0;
    while (true) {

        wm.showmenu();
        cout << "请输入选择" << endl;
        cin >> choice;

        if (cin.fail()) {
            cout << "输入无效，请重新输入一个数字！" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause1();
            clear_screen();
            continue;
        }
        switch (choice) {
        case 0: // 退出
            wm.exitexe();
            break;
        case 1: // 添加职工信息
            wm.addnum();
            break;
        case 2: // 显示职工信息
            wm.show_worker();
            break;
        case 3: // 删除离职职工
            wm.del_worker();
            break;
        case 4: // 修改职工信息
            wm.change_worker();
            break;
        case 5: // 查找职工信息
            wm.find_worker();
            break;
        case 6: // 按照编号排序
            wm.paixu();
            break;
        case 7: // 清空所有文档
            break;
        default:
            clear_screen();
            break;
        }
    }

    return 0;
}