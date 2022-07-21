/*************************************************************************
【文件名】ControllerCommandline.cpp
【功能模块和目的】业务流程类命令行派生类实现
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-21
【版权信息】以下代码由唐春洋根据清华大学自动化系2022年暑期“面向对象程序设计训练”课程要求独立编写，
    开发者唐春洋(tangcy21@mails.tsinghua.edu.cn)声明放弃对修改部分的任何版权诉求，任何使用者可做出任何修改、用于任何目的
    本代码遵守 CC 4.0 BY-SA 版权协议
    CC BY-SA 4.0 是一种许可协议，赋予遵守者两项重要权利：
    一、共享的权利。允许通过任何媒介和任何形式复制、发行作品。
    二、改编的权利。允许二次加工、转换和基于作品进行创作，不限制用途，甚至是商业应用。
【更改记录】
    2022-07-21 由唐春洋创建该文件
*************************************************************************/

#include "ControllerCommandline.hpp"
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <tuple>

void ControllerCommandline::ShowUserAuth(const pUser& user) const {
    std::map<bool, std::string> authMap = {{true, "YES"}, {false, "NO"}};
    std::tuple<bool, bool, bool> authTuple = user->GetStatus();
    std::cout << "   User: " << user->Name << ", ID: " << user->ID << "   "
              << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "|  Role   | Admin | Collector | Recorder |" << std::endl;
    std::cout << "|Authority|  " << setw(5) << authMap[std::get<0>(authTuple)]
              << "|    " << setw(7) << authMap[std::get<1>(authTuple)]
              << "|    " << setw(7) << authMap[std::get<2>(authTuple)] << '|'
              << std::endl
              << "------------------------------------------" << std::endl;
}

void ControllerCommandline::ShowAvailableOperations(const pUser& user) const {
    if (user == nullptr) {
        std::cout << "Available Operations:" << std::endl;
        std::cout << "   1. Login" << std::endl;
        std::cout << "   2. Register" << std::endl;
        std::cout << "   3. Quit" << std::endl;
        std::cout << "Please input an integer: " << std::endl;
        return;
    } else {
        ShowUserAuth(user);
        std::tuple<bool, bool, bool> authTuple = user->GetStatus();
        std::cout << "Available Operations:" << std::endl;
        std::cout << "   1. Login as a regular user" << std::endl;
        if (std::get<0>(authTuple)) {
            std::cout << "   2. Login as an administrator" << std::endl;
        }
        if (std::get<1>(authTuple)) {
            std::cout << "   3. Login as a collector" << std::endl;
        }
        if (std::get<2>(authTuple)) {
            std::cout << "   4. Login as a recorder" << std::endl;
        }
        std::cout << "   5. Logout" << std::endl;
        std::cout << "   6. Quit" << std::endl;
        std::cout << "Please input an integer: " << std::endl;
        return;
    }
}