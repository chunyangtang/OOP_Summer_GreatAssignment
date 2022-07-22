/*************************************************************************
【文件名】ControllerCommandline.cpp
【功能模块和目的】业务流程类命令行派生类实现
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-13
【版权信息】以下代码由唐春洋根据清华大学自动化系2022年暑期“面向对象程序设计训练”课程要求独立编写，
    开发者唐春洋(tangcy21@mails.tsinghua.edu.cn)声明放弃对修改部分的任何版权诉求，任何使用者可做出任何修改、用于任何目的
    本代码遵守 CC 4.0 BY-SA 版权协议
    CC BY-SA 4.0 是一种许可协议，赋予遵守者两项重要权利：
    一、共享的权利。允许通过任何媒介和任何形式复制、发行作品。
    二、改编的权利。允许二次加工、转换和基于作品进行创作，不限制用途，甚至是商业应用。
【更改记录】
    2022-07-13 由唐春洋完善了类中功能的代码实现
    2020-07-20 由唐春洋增加注释，并完善了功能
*************************************************************************/

#include "ControllerCommandline.hpp"
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>

/*************************************************************************
【函数名称】ControllerCommandline::ShowUserAuth
【函数功能】包装了User的GetStatus，用可输出展示的字符串表示用户权限信息
【参数】pUser: 用户指针
【返回值】std::string: 用户权限信息字符串
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-13
【更改记录】
    2022-07-13 由唐春洋完善了类中功能的代码实现
    2020-07-20 由唐春洋增加注释
*************************************************************************/
std::string ControllerCommandline::ShowUserAuth(const pUser& user) const {
    std::map<bool, std::string> authMap = {{true, "YES"}, {false, "NO"}};
    std::tuple<bool, bool, bool> authTuple = user->GetStatus();
    std::ostringstream oss;
    oss << "------------------------------------------" << std::endl;
    oss << "   User: " << user->Name << ", ID: " << user->ID << "   "
        << std::endl;
    oss << "------------------------------------------" << std::endl;
    oss << "|  Role   | Admin | Collector | Recorder |" << std::endl;
    oss << "|Authority|  " << setw(5) << left << authMap[std::get<0>(authTuple)]
        << "|    " << setw(7) << left << authMap[std::get<1>(authTuple)]
        << "|    " << setw(6) << left << authMap[std::get<2>(authTuple)] << '|'
        << std::endl
        << "------------------------------------------" << std::endl;
    return oss.str();
}

/*************************************************************************
【函数名称】ControllerCommandline::ShowUserResult
【函数功能】包装了User的GetTestResult，用可输出展示的字符串表示用户检测结果
【参数】pUser: 用户指针
【返回值】std::string: 用户检测结果信息字符串
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-13
【更改记录】
    2022-07-13 由唐春洋完善了类中功能的代码实现
    2020-07-20 由唐春洋增加注释
*************************************************************************/
std::string ControllerCommandline::ShowUserResult(const pUser& user) const {
    std::ostringstream oss;
    oss << "------------------------------------------" << std::endl;
    oss << "   User: " << user->Name << ", ID: " << user->ID << "   "
        << std::endl;
    auto result = user->GetTestResult();
    oss << "------------------------------------------" << std::endl;
    if (result.first == TestResult::UNTESTED) {
        oss << "         No Result Available              " << std::endl;
        oss << "------------------------------------------" << std::endl;
    } else {
        DateTime::SetFormat(false);

        oss << "  Lastest Test Time: " << result.second.GetFormatString()
            << std::endl;
        oss << "  Test Result      : "
            << (result.first == TestResult::POSITIVE ? "POSITIVE" : "NEGATIVE")
            << std::endl;
        oss << "------------------------------------------" << std::endl;
        DateTime::SetFormat(true);
    }
    return oss.str();
}