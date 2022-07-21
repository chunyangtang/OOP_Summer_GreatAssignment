/*************************************************************************
【文件名】ControllerCommandline.hpp
【功能模块和目的】业务流程类命令行派生类声明
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

#ifndef ControllerCommandline_hpp
#define ControllerCommandline_hpp

#include "ControllerBase.hpp"

class ControllerCommandline : public ControllerBase {
public:
    // 展示用户权限信息
    virtual void ShowUserAuth(const pUser& user) const override;
    // 展示可用操作
    void ShowAvailableOperations(const pUser& user = nullptr) const;
    // 按分支选择操作
    void ChooseOperation(const pUser& user = nullptr);
    // 用户注册
    virtual ControllerError Register(std::string id, std::string password);
    // 登录与角色选择
    virtual ControllerError Login(std::string id, std::string password);
    // 被试者可执行的操作
    virtual void RoleRegular(pUser& user) = 0;
    // 管理员可执行的操作
    virtual void RoleAdmin(pUser& user) = 0;
    // 采集员可执行的操作
    virtual void RoleCollector(pUser& user) = 0;
    // 录入员可执行的操作
    virtual void RoleRecorder(pUser& user) = 0;
};

#endif