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
#include "DateTime.hpp"
#include "MD5.hpp"
#include "Tube.hpp"
#include <string>
#include <tuple>

// 核酸检测结果枚举类
enum class TestResult {
    UNTESTED = -1, // 未检测为-1
    NEGATIVE = 0,  // 阴性为0
    POSITIVE = 1   // 阳性为1
};

// 定义用户权限元组别名
using UserAuth = std::tuple<bool, bool, bool>;
// 定义用户智能指针的别名
using pUser = std::shared_ptr<User>;

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
    // 构造函数
    User(std::string id, std::string name, std::string password);
    // 普通用户重置password
    bool ResetPassword(std::string oldPassword, std::string newPassword);
    // 获取用户权限状态
    UserAuth GetStatus() const;
    // 通过ID查找用户
    static pUser FindUser(std::string id);

private:
    // 友元类声明
    friend class Tube;
    // 存储全部用户指针的vector
    static std::vector<pUser> m_AllUsers;
    std::string m_Name;
    MD5 m_Password;
    std::string m_ID;

    class Admin {
        // 重置任意用户password
        bool ResetPassword(pUser user, std::string newPassword);
        // 删除用户
        bool DeleteUser(pUser user);
        // 为用户添加身份
        bool AddRole(pUser user, std::string role);
        // 为用户删除身份
        bool DeleteRole(pUser user, std::string role);
    };

    class Collector {};
    class Recorder {};
    Admin* m_Admin;
    Collector* m_Collector;
    Recorder* m_Recorder;
    // 上次检测结果
    TestResult m_LastUserResult;
    // 上次检测时间
    DateTime m_LastTestDate;
};

#endif /* User_hpp */