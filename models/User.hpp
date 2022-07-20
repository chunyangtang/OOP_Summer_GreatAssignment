/*************************************************************************
【文件名】User.hpp
【功能模块和目的】用户类声明
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-20
【版权信息】以下代码由唐春洋根据清华大学自动化系2022年暑期“面向对象程序设计训练”课程要求独立编写，
    开发者唐春洋(tangcy21@mails.tsinghua.edu.cn)声明放弃对修改部分的任何版权诉求，任何使用者可做出任何修改、用于任何目的
    本代码遵守 CC 4.0 BY-SA 版权协议
    CC BY-SA 4.0 是一种许可协议，赋予遵守者两项重要权利：
    一、共享的权利。允许通过任何媒介和任何形式复制、发行作品。
    二、改编的权利。允许二次加工、转换和基于作品进行创作，不限制用途，甚至是商业应用。
【更改记录】
    2022-07-20 由唐春洋创建该文件
*************************************************************************/

#ifndef User_hpp
#define User_hpp
#include "MD5.hpp"
#include "Tube.hpp"
#include <string>

// 核酸检测结果枚举类
enum class TestResult {
    UNTESTED = -1, // 未检测为-1
    NEGATIVE = 0,  // 阴性为0
    POSITIVE = 1   // 阳性为1
};

/*************************************************************************
【类名】User
【功能】储存用户信息的类
【接口说明】
    构造函数：Date(int year, int month, int day)按日期构造Date对象
    拷贝构造函数：Date(const Date& date)拷贝构造Date对象
    重置密码函数：ResetPassword(std::string oldPassword, std::string
newPassword)用旧密码变更新密码
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-07-20
【更改记录】
     2022-07-20 由唐春洋创建该类
*************************************************************************/
class User {
public:
    bool ResetPassword(std::string oldPassword, std::string newPassword);

private:
    std::string m_Name;
    MD5 m_Password;
    std::string m_ID;

    class Admin {
        bool ResetPassword(User* user, std::string newPassword);
        bool AddRole(User* user, std::string role);
        bool TakeRole(User* user, std::string role);
    };

    class Collector {};
    class Recorder {};
    Admin* m_Admin;
    Collector* m_Collector;
    Recorder* m_Recorder;
    // 上次检测信息
    TestResult m_LastTestResult;
};

#endif /* User_hpp */