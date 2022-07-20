/*************************************************************************
【文件名】User.cpp
【功能模块和目的】用户类定义
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

#include "User.hpp"

User::User(std::string id, std::string name, std::string password)
    : m_ID(id), m_Name(name) {
    m_Password = MD5(password);
    m_Admin = nullptr;
    m_Collector = nullptr;
    m_Recorder = nullptr;
    if (m_AllUsers.empty()) {
        m_Admin = new Admin();
    }
    m_AllUsers.push_back(std::make_shared<User>(*this));
}

bool User::ResetPassword(std::string oldPassword, std::string newPassword) {
    if (oldPassword == newPassword) {
        return false;
    }
    if (MD5(oldPassword) == m_Password) {
        m_Password = MD5(newPassword);
        return true;
    } else {
        return false;
    }
}

UserAuth User::GetStatus() const {
    return std::make_tuple((m_Admin != nullptr), (m_Collector != nullptr),
                           (m_Recorder != nullptr));
}

pUser User::FindUser(std::string id) {
    for (auto user : m_AllUsers) {
        if (user->m_ID == id) {
            return user;
        }
    }
    return nullptr;
}

bool User::Admin::ResetPassword(pUser user, std::string newPassword) {
    user->m_Password = MD5(newPassword);
}

bool User::Admin::DeleteUser(pUser user) {
    for (auto it : m_AllUsers) {
        if (*it == user) {
            m_AllUsers.erase(it);
            return true;
        }
    }
    return false;
}

bool User::Admin::AddRole(pUser user, std::string role) {
    if (role == "admin") {
        user->m_Admin = new Admin();
        return true;
    } else if (role == "collector") {
        user->m_Collector = new Collector();
        return true;
    } else if (role == "recorder") {
        user->m_Recorder = new Recorder();
        return true;
    } else {
        return false;
    }
}

bool User::Admin::DeleteRole(pUser user, std::string role) {
    if (role == "admin") {
        delete user->m_Admin;
        user->m_Admin = nullptr;
        return true;
    } else if (role == "collector") {
        delete user->m_Collector;
        user->m_Collector = nullptr;
        return true;
    } else if (role == "recorder") {
        delete user->m_Recorder;
        user->m_Recorder = nullptr;
        return true;
    } else {
        return false;
    }
}