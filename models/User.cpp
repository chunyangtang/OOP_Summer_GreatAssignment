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

// 静态vector初始化
std::vector<pUser> User::m_AllUsers = {};

User::User(std::string id, std::string name, std::string password)
    : ID(m_ID), Name(m_Name), m_ID(id), m_Name(name) {
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

std::pair<TestResult, DateTime> User::GetTestResult() const {
    return std::make_pair(m_LastResult, m_LastTime);
}

pUser User::GetUser(std::string id, std::string password) {
    for (auto& user : m_AllUsers) {
        if (user->m_ID == id && user->m_Password == MD5(password)) {
            return user;
        }
    }
    return nullptr;
}

bool User::Admin::ResetPassword(pUser user, std::string newPassword) {
    user->m_Password = MD5(newPassword);
}

bool User::Admin::DeleteUser(pUser user) {
    for (auto it = m_AllUsers.begin(); it != m_AllUsers.end(); ++it) {
        if (*it == user) {
            it = m_AllUsers.erase(it);
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

pTube User::Collector::CreateTube(std::string SerialNumber,
                                  unsigned MaxCapasity = 10) {
    new Tube(SerialNumber, MaxCapasity);
}

bool User::Collector::CollectUsers(pTube tube, std::string id, DateTime time) {
    if (tube->m_CollectedUsers.size() >= tube->m_MaxCapasity) {
        return false;
    }
    pUser temp = User::FindUser(id);
    if (temp == nullptr) {
        return false;
    } else {
        tube->m_CollectedUsers.push_back(std::make_pair(temp, time));
    }
}

bool User::Recorder::RecordTubeStatus(std::string SerialNumber,
                                      TestResult result) {
    pTube tube = Tube::FindTube(SerialNumber);
    if (tube != nullptr) {
        tube->m_TubeResult = result;
        User::Recorder::UpdateRecord(tube);
        return true;
    } else {
        return false;
    }
}

void User::Recorder::UpdateRecord(pTube tube) {
    for (auto it : tube->m_CollectedUsers) {
        pUser temp = User::FindUser(it.first());
        if (temp != nullptr) {
            temp->m_LastTime = it.second();
            temp->m_LastResult = tube->m_TubeResult;
        }
    }
}

pUser User::FindUser(std::string id) {
    for (auto user : m_AllUsers) {
        if (user->m_ID == id) {
            return user;
        }
    }
    return nullptr;
}