/*************************************************************************
【文件名】ControllerBase.hpp
【功能模块和目的】业务流程类基类声明
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

#ifndef ControllerBase_hpp
#define ControllerBase_hpp

#include "../models/Tube.hpp"
#include "../models/User.hpp"
#include "../models/tinyxml2.h"
#include <memory>
#include <string>
#include <vector>

using namespace tinyxml2;

// 定义用户智能指针的别名
using pUser = std::shared_ptr<User>;

// 定义试管智能指针的别名
using pTube = std::shared_ptr<Tube>;

// 定义函数返回值对应的错误类型
enum class ControllerError {
    EMPTY_FILE,     // 解析的文件为空文件
    FILE_ERROR,     //解析文件出错
    ID_EXISTED,     // 注册时用户已存在的错误
    ID_NOT_FOUND,   //登陆时未找到用户
    WRONG_PASSWORD, //登陆时密码错误
    SUCCESS
};

class ControllerBase {
public:
    // 解析已存在的用户文件
    ControllerError ParseUserFile(const char* filename);
    // 解析已存在的试管文件
    ControllerError ParseTubeFile(const char* filename);
    // 保存程序信息到用户文件
    ControllerError SavetoUserFile(const char* filename);
    // 保存程序信息到试管文件
    ControllerError SavetoTubeFile(const char* filename);
    // 展示用户权限信息
    virtual std::string ShowUserAuth(const pUser& user) const = 0;
    // 用户注册
    virtual pUser Register(std::string id, std::string name,
                           std::string password) = 0;
    // 登录与角色选择
    virtual pUser Login(std::string id, std::string password) = 0;
    // 被试者可执行的操作
    virtual void RoleRegular(pUser& user) = 0;
    // 管理员可执行的操作
    virtual void RoleAdmin(pUser& user) = 0;
    // 采集员可执行的操作
    virtual void RoleCollector(pUser& user) = 0;
    // 录入员可执行的操作
    virtual void RoleRecorder(pUser& user) = 0;
};

#endif /* ControllerBase_hpp */