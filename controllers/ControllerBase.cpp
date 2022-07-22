/*************************************************************************
【文件名】ControllerBase.cpp
【功能模块和目的】业务流程类基类实现
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-13
【版权信息】以下代码由唐春洋根据清华大学自动化系2022年暑期“面向对象程序设计训练”课程要求独立编写，
    开发者唐春洋(tangcy21@mails.tsinghua.edu.cn)声明放弃对修改部分的任何版权诉求，任何使用者可做出任何修改、用于任何目的
    本代码遵守 CC 4.0 BY-SA 版权协议
    CC BY-SA 4.0 是一种许可协议，赋予遵守者两项重要权利：
    一、共享的权利。允许通过任何媒介和任何形式复制、发行作品。
    二、改编的权利。允许二次加工、转换和基于作品进行创作，不限制用途，甚至是商业应用。
【更改记录】
    2022-07-13 由唐春洋创建该文件
    2022-07-20 由唐春洋添加注释
*************************************************************************/

#include "ControllerBase.hpp"

/*************************************************************************
【函数名称】ControllerBase::Register
【函数功能】包装了User的构造过程，实现用户注册
【参数】id：用户的ID，name：用户的姓名，password：用户的密码
【返回值】pUser类型：注册成功返回用户指针，否则返回nullptr
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-13
【更改记录】
    2022-07-13 由唐春洋完善了类中功能的代码实现
    2020-07-20 由唐春洋增加注释
*************************************************************************/
pUser ControllerBase::Register(std::string id, std::string name,
                               std::string password) {
    if (User::HaveUser(id)) {
        return nullptr;
    } else {
        return std::make_shared<User>(id, name, password);
    }
}

/*************************************************************************
【函数名称】ControllerBase::Login
【函数功能】包装了User的验证、获取过程，实现用户登录
【参数】id：用户的ID，password：用户的密码
【返回值】pUser类型：登录成功返回用户指针，否则返回nullptr
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-13
【更改记录】
    2022-07-13 由唐春洋完善了类中功能的代码实现
    2020-07-20 由唐春洋增加注释
*************************************************************************/
pUser ControllerBase::Login(std::string id, std::string password) const {
    if (User::HaveUser(id)) {
        return User::GetUser(id, password);
    } else {
        return nullptr;
    }
}