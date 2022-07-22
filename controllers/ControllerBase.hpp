/*************************************************************************
【文件名】ControllerBase.hpp
【功能模块和目的】业务流程类基类声明
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

#ifndef ControllerBase_hpp
#define ControllerBase_hpp

#include "../models/DateTime.hpp"
#include "../models/Tube.hpp"
#include "../models/User.hpp"
#include <memory>
#include <string>
#include <tuple>
#include <vector>

// 定义用户智能指针的别名
class User;
using pUser = std::shared_ptr<User>;
using pwUser = std::weak_ptr<User>;

// 定义试管智能指针的别名
class Tube;
using pTube = std::shared_ptr<Tube>;

/*************************************************************************
【类名】ControllerBase
【功能】业务流程基类，定义了业务流程的基本操作
【接口说明】
    展示用户权限 ShowUserAuth(const pUser& user) const 纯虚函数未实现
    展示用户检测结果 ShowUserResult(const pTube& tube) const 纯虚函数未实现
    用户注册 Register(std::string id, std::string name, std::string password)
    用户登录 Login(std::string id, std::string password);
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-13
【更改记录】
    2022-07-13 由唐春洋完善了类中功能的代码实现
    2020-07-20 由唐春洋增加注释，并完善了功能
*************************************************************************/
class ControllerBase {
public:
    // 展示用户权限信息
    virtual std::string ShowUserAuth(const pUser& user) const = 0;
    // 展示用户核酸检测结果
    virtual std::string ShowUserResult(const pUser& user) const = 0;
    // 用户注册
    virtual pUser Register(std::string id, std::string name,
                           std::string password);
    // 用户登录
    virtual pUser Login(std::string id, std::string password) const;
};

#endif /* ControllerBase_hpp */