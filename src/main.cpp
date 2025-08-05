#include "utils.h"
#include "worker.h"
#include "workermanager.h"
#include <iostream>
#include <limits>


using namespace std;

int main() {
    useUTF8();

    Workermanager test;
    int choice = 0;
    while (true) {

        test.showmenu();
        cout << "请输入选择" << endl;
        cin >> choice;
        if (cin.fail()) {
            cout << "输入无效，请重新输入一个数字！" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("pause");
            system("cls");
            continue;
        }
        switch (choice) {
        case 0: // 退出
            test.exitexe();
            break;
        case 1: // 添加职工信息
            break;
        case 2: // 显示职工信息
            break;
        case 3: // 删除离职职工
            break;
        case 4: // 修改职工信息
            break;
        case 5: // 查找职工信息
            break;
        case 6: // 按照编号排序
            break;
        case 7: // 清空所有文档
            break;
        default:
            system("cls");
            break;
        }
    }

    system("pause");
    return 0;
}