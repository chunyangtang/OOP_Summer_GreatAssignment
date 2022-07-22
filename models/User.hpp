/*************************************************************************
【文件名】User.hpp
【功能模块和目的】用户类声明
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-2
【版权信息】以下代码由唐春洋根据清华大学自动化系2022年暑期“面向对象程序设计训练”课程要求独立编写，
    开发者唐春洋(tangcy21@mails.tsinghua.edu.cn)声明放弃对修改部分的任何版权诉求，任何使用者可做出任何修改、用于任何目的
    本代码遵守 CC 4.0 BY-SA 版权协议
    CC BY-SA 4.0 是一种许可协议，赋予遵守者两项重要权利：
    一、共享的权利。允许通过任何媒介和任何形式复制、发行作品。
    二、改编的权利。允许二次加工、转换和基于作品进行创作，不限制用途，甚至是商业应用。
【更改记录】
    2022-07-02 由唐春洋创建该文件
    2022-07-10 由唐春洋创建了Admin、Collector、Recorder内嵌类
    2022-07-20 由唐春洋添加注释
*************************************************************************/

#ifndef User_hpp
#define User_hpp
#include "DateTime.hpp"
#include "MD5.hpp"
#include "Tube.hpp"
#include "tinyxml2.h"
#include <memory>
#include <string>
#include <tuple>
#include <vector>

// 核酸检测结果枚举类
enum class TestResult {
    UNTESTED = -1, // 未检测为-1
    NEGATIVE = 0,  // 阴性为0
    POSITIVE = 1   // 阳性为1
};

// 定义用户权限元组别名
using UserAuth = std::tuple<bool, bool, bool>;
// 定义用户智能指针的别名
class User;
using pUser = std::shared_ptr<User>;
// 定义试管智能指针的别名
class Tube;
using pTube = std::shared_ptr<Tube>;

/*************************************************************************
【类名】User
【功能】储存用户信息的类
【接口说明】
    构造函数User(std::string id, std::string name, std::string
password)按id、姓名、密码创建账户 重置密码函数ResetPassword(std::string
oldPassword, std::string newPassword)通过旧密码重置密码
    获取用户权限状态GetStatus()返回tuple获取三个特殊身份的权限状态
    获取核酸检测状态GetTestResult()获取检测结果与日期
    判断是否存在指定用户HaveUser(std::string id)返回bool结果
    查找指定用户GetUser(std::string id, std::string password)返回用户指针
    从文件加载全部用户信息 static bool LoadFile(const char* filename)
    保存全部用户信息到文件 static bool SaveFile(const char* filename)
    管理员指针Admin* m_pAdmin
    采集员指针Collector* m_pCollector
    录入员指针Recorder* m_pRecorder
    用户id（只读） ID
    用户姓名（只读） Name
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-07-02
【更改记录】
     2022-07-02 由唐春洋创建该类
     2022-07-10 由唐春洋新增了权限管理功能
     2022-07-20 由唐春洋完善了注释
*************************************************************************/
class User {
public:
    // 构造函数
    User(std::string id, std::string name, std::string password);
    // 普通用户重置password
    bool ResetPassword(std::string oldPassword, std::string newPassword);
    // 获取用户权限状态
    UserAuth GetStatus() const;
    // 获取核酸检测状态
    std::pair<TestResult, DateTime> GetTestResult() const;
    // 静态成员，判断是否存在某User，供外部调用
    static bool HaveUser(std::string id);
    // 静态成员，通过ID、密码查找用户
    static pUser GetUser(std::string id, std::string password);
    // 从文件加载全部用户信息
    static bool LoadFile(const char* filename);
    // 保存全部用户信息到文件
    static bool SaveFile(const char* filename);

    /*************************************************************************
    【类名】Admin
    【功能】管理员权限类
    【接口说明】
        重置任意用户密码 ResetPassword(std::string ID, std::string
    newPassword)使用id查找后重置密码
        删除用户 DeleteUser(std::string ID)删除指定id的用户
        添加权限 AddRole(std::string ID, std::string
    role)为某一用户添加指定的权限
        删除权限 DeleteRole(std::string ID,
    std::string role)为某一用户删除指定的权限
    【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-07-10
    【更改记录】
        2022-07-10 由唐春洋创建该类
        2022-07-20 由唐春洋完善了注释
    *************************************************************************/
    class Admin {
    public:
        // 重置任意用户password
        bool ResetPassword(std::string ID, std::string newPassword);
        // 删除用户
        bool DeleteUser(std::string ID);
        // 为用户添加身份
        bool AddRole(std::string ID, std::string role);
        // 为用户删除身份
        bool DeleteRole(std::string ID, std::string role);

    private:
        // 将文件加载函数设置为友元函数
        friend bool User::LoadFile(const char* filename);
        // 将用户类构造函数声明为友元函数
        friend User::User(std::string, std::string, std::string);

        // 将构造函数定义为私有
        Admin() = default;
    };

    /*************************************************************************
    【类名】Collector
    【功能】采集员权限类
    【接口说明】
        录入试管 CreateTube(std::string SerialNumber)
    输入序列号、容量，返回试管指针
        为试管添加用户 CollectUsers(pTube tube, std::string id, DateTime time)
     试管、用户均合法即返回true
        查找试管 FindTube(std::string SerialNumber)返回试管指针
    【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-07-10
    【更改记录】
        2022-07-10 由唐春洋创建该类
        2022-07-20 由唐春洋完善了注释
    *************************************************************************/
    class Collector {
    public:
        // 新建试管
        pTube CreateTube(std::string SerialNumber);
        // 录入采集信息
        bool CollectUsers(const pTube& tube, std::string id, DateTime time);
        // 查找试管函数
        pTube FindTube(std::string SerialNumber);

    private:
        // 将Admin设为友元类
        friend class Admin;
        // 将文件加载函数设置为友元函数
        friend bool User::LoadFile(const char* filename);
        // 将构造函数定义为私有
        Collector() = default;
    };

    /*************************************************************************
    【类名】Recorder
    【功能】录入员权限类
    【接口说明】
        录入检测结果 RecordTubeStatus(std::string SerialNumber, TestResult
    result)找到试管即录入并返回true
        更新用户的检测状态 UpdateRecord(pTube tube) 用传入的试管更新用户检测结果
    【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-07-10
    【更改记录】
        2022-07-10 由唐春洋创建该类
        2022-07-20 由唐春洋完善了注释
    *************************************************************************/
    class Recorder {
    public:
        // 录入试管状态
        bool RecordTubeStatus(std::string SerialNumber, TestResult result);

        // 根据试管结果更新用户结果，在录入试管状态时调用
        void UpdateRecord(const pTube& tube);

    private:
        // 将Admin设为友元类
        friend class Admin;
        // 将文件加载函数设置为友元函数
        friend bool User::LoadFile(const char* filename);

        // 将构造函数定义为私有
        Recorder() = default;
    };

    Admin* m_pAdmin;
    Collector* m_pCollector;
    Recorder* m_pRecorder;

    // 常量引用只读读取用户信息
    const std::string& ID;
    const std::string& Name;

private:
    // 将试管类声明为友元类使用文件加载
    friend class Tube;

    // 通过ID查找用户，仅供类内使用
    static pUser FindUser(std::string id);

    // 存储全部用户指针的vector
    static std::vector<pUser> m_AllUsers;

    // 用户ID
    std::string m_ID;
    // 用户姓名
    std::string m_Name;
    // 用户密码(Encypted)
    MD5 m_Password;

    // 上次检测结果
    TestResult m_LastResult;
    // 上次检测时间
    DateTime m_LastTime;
};

#endif /* User_hpp */