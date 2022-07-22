/*************************************************************************
【文件名】User.cpp
【功能模块和目的】用户类定义
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

#include "User.hpp"

// 静态vector初始化
std::vector<pUser> User::m_AllUsers = {};

/*************************************************************************
【函数名称】User::User
【函数功能】构造函数
【参数】id：用户id，name：用户名，password：用户密码
【返回值】无
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-2
【更改记录】
    2022-07-03 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
User::User(std::string id, std::string name, std::string password)
    : ID(m_ID), Name(m_Name), m_ID(id), m_Name(name) {
    m_Password = MD5(password);
    m_pAdmin = nullptr;
    m_pCollector = nullptr;
    m_pRecorder = nullptr;
    m_LastResult = TestResult::UNTESTED;
    if (m_AllUsers.empty()) {
        m_pAdmin = new Admin();
    }
    m_AllUsers.push_back(std::make_shared<User>(*this));
}

/*************************************************************************
【函数名称】User::ResetPassword
【函数功能】重置用户密码
【参数】oldPassword：旧密码，newPassword：新密码
【返回值】bool类型：是否重置成功
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-2
【更改记录】
    2022-07-03 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool User::ResetPassword(std::string oldPassword, std::string newPassword) {
    if (oldPassword == newPassword) {
        return false;
    }
    if (MD5(oldPassword) == m_Password) {
        m_Password.Update(newPassword);
        return true;
    } else {
        return false;
    }
}

/*************************************************************************
【函数名称】User::GetStatus
【函数功能】获取用户权限状态
【参数】无
【返回值】UserAuth类型，为tuple<bool, bool,
bool>的别名，代表Admin、Collector、Recorder权限状态
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-2
【更改记录】
    2022-07-03 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
UserAuth User::GetStatus() const {
    return std::make_tuple((m_pAdmin != nullptr), (m_pCollector != nullptr),
                           (m_pRecorder != nullptr));
}

/*************************************************************************
【函数名称】User::GetTestResult
【函数功能】获取最新检测结果
【参数】无
【返回值】pair<TestResult,
DateTime>类型，TestResult为枚举类，代表检测结果，DateTime为时间类，代表检测时间
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-2
【更改记录】
    2022-07-03 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
std::pair<TestResult, DateTime> User::GetTestResult() const {
    return std::make_pair(m_LastResult, m_LastTime);
}

/*************************************************************************
【函数名称】User::HaveUser
【函数功能】判断是否存在指定用户
【参数】id：用户id
【返回值】bool值，是否存在指定用户（与private: FindUser返回User指针不同）
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-2
【更改记录】
    2022-07-05 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool User::HaveUser(std::string id) {
    for (auto user : m_AllUsers) {
        if (user->m_ID == id) {
            return true;
        }
    }
    return false;
}

/*************************************************************************
【函数名称】User::GetUser
【函数功能】查找用户并获得用户指针
【参数】id：用户id，password：用户密码
【返回值】pUser类型，为shared_ptr<User>的别名，代表用户指针，若不存在该用户则返回nullptr
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-2
【更改记录】
    2022-07-05 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
pUser User::GetUser(std::string id, std::string password) {
    for (auto& user : m_AllUsers) {
        if (user->m_ID == id && user->m_Password == MD5(password)) {
            return user;
        }
    }
    return nullptr;
}

/*************************************************************************
【函数名称】User::LoadFile
【函数功能】将文件的信息解析到用户列表中
【参数】filename：文件的相对路径
【返回值】bool值，是否成功解析文件
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-2
【更改记录】
    2022-07-05 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool User::LoadFile(const char* filename) {
    using namespace tinyxml2;
    if (fopen(filename, "r") == NULL) {
        return false;
    } else {
        fclose(fopen(filename, "r"));
    }
    try {
        // 用TinyXML2解析用户文件
        XMLDocument doc(true, COLLAPSE_WHITESPACE);
        doc.LoadFile(filename);
        if (doc.Error()) {
            return false;
        }
        XMLHandle docHandle(&doc);
        // 获取子节点信息并加载到User对象中
        XMLElement* user_child =
            docHandle.FirstChildElement().FirstChildElement().ToElement();
        while (user_child) {
            // 初始化用户姓名、ID、密码
            std::string ID(user_child->FirstChildElement("ID")->GetText());
            std::string Name(user_child->FirstChildElement("Name")->GetText());
            std::string Password = "fake";

            new User(ID, Name, Password);
            pUser user = User::FindUser(ID);
            user->m_Password = MD5::FromCipherText(std::string(
                user_child->FirstChildElement("EncyptedPassword")->GetText()));

            // 初始化用户核酸检测结果
            std::string result(
                user_child->FirstChildElement("LastTest")->Attribute("Result"));
            if (result == "POSITIVE") {
                user->m_LastResult = TestResult::POSITIVE;
                user->m_LastTime = DateTime(std::string(
                    user_child->FirstChildElement("LastTest")->GetText()));
            } else if (result == "NEGATIVE") {
                user->m_LastResult = TestResult::NEGATIVE;
                user->m_LastTime = DateTime(std::string(
                    user_child->FirstChildElement("LastTest")->GetText()));
            } else {
                user->m_LastResult = TestResult::UNTESTED;
            }
            // 为用户添加权限信息
            bool authority = user_child->BoolAttribute("IsAdmin");
            if (authority) {
                user->m_pAdmin = new User::Admin;
            } else {
                user->m_pAdmin = nullptr;
            }
            authority = user_child->BoolAttribute("IsCollector");
            if (authority) {
                user->m_pCollector = new User::Collector;
            } else {
                user->m_pCollector = nullptr;
            }
            authority = user_child->BoolAttribute("IsRecorder");
            if (authority) {
                user->m_pRecorder = new User::Recorder;
            } else {
                user->m_pRecorder = nullptr;
            }
            user_child = user_child->NextSiblingElement();
        }
    } catch (...) {
        return false;
    }

    return true;
}

/*************************************************************************
【函数名称】User::SaveFile
【函数功能】将用户数据录入到文件中
【参数】filename：储存试管数据文件的文件名
【返回值】bool类型：反映保存是否成功
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-2
【更改记录】
    2022-07-05 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool User::SaveFile(const char* filename) {
    using namespace tinyxml2;
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    XMLDeclaration* decl =
        doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    doc.InsertFirstChild(decl);
    XMLComment* comment = doc.NewComment("This is the user-data-storing file.");
    doc.InsertEndChild(comment);
    XMLElement* root = doc.NewElement("AllUsers");
    doc.InsertEndChild(root);
    for (auto& user : User::m_AllUsers) {
        XMLElement* user_child = doc.NewElement("User");
        root->InsertEndChild(user_child);
        XMLElement* Name = doc.NewElement("Name");
        Name->SetText(user->m_Name.c_str());
        user_child->InsertEndChild(Name);
        XMLElement* ID = doc.NewElement("ID");
        ID->SetText(user->m_ID.c_str());
        user_child->InsertEndChild(ID);
        XMLElement* EncyptedPassword = doc.NewElement("EncyptedPassword");
        stringstream ss;
        ss << user->m_Password;
        EncyptedPassword->SetText(ss.str().c_str());
        user_child->InsertEndChild(EncyptedPassword);

        XMLElement* LastTest = doc.NewElement("LastTest");

        std::string str_result;
        DateTime::SetFormat(true);
        if (user->m_LastResult == TestResult::POSITIVE) {
            str_result = "POSITIVE";
            LastTest->SetText(user->m_LastTime.GetFormatString().c_str());
        } else if (user->m_LastResult == TestResult::NEGATIVE) {
            str_result = "NEGATIVE";
            LastTest->SetText(user->m_LastTime.GetFormatString().c_str());
        } else {
            str_result = "UNTESTED";
        }
        LastTest->SetAttribute("Result", str_result.c_str());
        user_child->InsertEndChild(LastTest);

        user_child->SetAttribute("IsAdmin", user->m_pAdmin != nullptr);
        user_child->SetAttribute("IsCollector", user->m_pCollector != nullptr);
        user_child->SetAttribute("IsRecorder", user->m_pRecorder != nullptr);
    }
    if (doc.SaveFile(filename)) {
        return true;
    } else {
        return false;
    }
}

/*************************************************************************
【函数名称】Admin::ResetPassword
【函数功能】重置用户密码
【参数】id：用户id，password：用户密码
【返回值】bool类型，查找到用户即可以重置密码返回true，否则返回false
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-10
【更改记录】
    2022-07-11 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool User::Admin::ResetPassword(std::string ID, std::string newPassword) {
    pUser user = User::FindUser(ID);
    if (user == nullptr) {
        return false;
    } else {
        user->m_Password = MD5(newPassword);
        return true;
    }
}

/*************************************************************************
【函数名称】Admin::DeleteUser
【函数功能】删除用户
【参数】id：用户id
【返回值】bool类型，查找到用户即可以删除并返回true，否则返回false
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-10
【更改记录】
    2022-07-11 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool User::Admin::DeleteUser(std::string ID) {
    pUser user = User::FindUser(ID);
    if (user != nullptr) {
        for (auto it = m_AllUsers.begin(); it != m_AllUsers.end(); ++it) {
            if (*it == user) {
                it = m_AllUsers.erase(it);
                return true;
            }
        }
    }
    return false;
}

/*************************************************************************
【函数名称】Admin::AddRole
【函数功能】为用户添加角色
【参数】id：用户id，role：角色字符串（admin/collector/recorder合法）
【返回值】bool类型，查找到用户、角色字符串合法即可以添加角色并返回true，否则返回false
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-10
【更改记录】
    2022-07-11 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool User::Admin::AddRole(std::string ID, std::string role) {
    pUser user = User::FindUser(ID);
    if (user != nullptr) {
        if (role == "admin") {
            user->m_pAdmin = new Admin();
            return true;
        } else if (role == "collector") {
            user->m_pCollector = new Collector();
            return true;
        } else if (role == "recorder") {
            user->m_pRecorder = new Recorder();
            return true;
        } else {
            return false;
        }
    }
    return false;
}

/*************************************************************************
【函数名称】Admin::DeleteRole
【函数功能】为用户删除角色
【参数】id：用户id，role：角色字符串（admin/collector/recorder合法）
【返回值】bool类型，查找到用户、角色字符串合法即可以删除角色并返回true，否则返回false
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-10
【更改记录】
    2022-07-11 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool User::Admin::DeleteRole(std::string ID, std::string role) {
    pUser user = User::FindUser(ID);
    if (user != nullptr) {
        if (role == "admin") {
            delete user->m_pAdmin;
            user->m_pAdmin = nullptr;
            return true;
        } else if (role == "collector") {
            delete user->m_pCollector;
            user->m_pCollector = nullptr;
            return true;
        } else if (role == "recorder") {
            delete user->m_pRecorder;
            user->m_pRecorder = nullptr;
            return true;
        } else {
            return false;
        }
    }
    return false;
}

/*************************************************************************
【函数名称】Collector::CreateTube
【函数功能】录入试管
【参数】SerialNumber： 试管序列号
【返回值】pTube类型，为shared_ptr<Tube>的别名，创建试管返回试管指针，已存在返回nullptr
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-10
【更改记录】
    2022-07-11 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
pTube User::Collector::CreateTube(std::string SerialNumber) {
    if (FindTube(SerialNumber) != nullptr) {
        return nullptr;
    }
    pTube p1(new Tube(SerialNumber));
    return p1;
}

/*************************************************************************
【函数名称】Collector::CollectUsers
【函数功能】将用户添加到试管中
【参数】tube 试管指针, id 用户ID, time 录入时间
【返回值】bool类型，查找到用户即可以添加数据并返回true，否则返回false
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-10
【更改记录】
    2022-07-11 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool User::Collector::CollectUsers(const pTube& tube, std::string id,
                                   DateTime time) {
    pUser temp = User::FindUser(id);
    if (temp == nullptr) {
        return false;
    } else {
        tube->m_CollectedUsers.push_back(std::make_pair(temp, time));
        return true;
    }
}

/*************************************************************************
【函数名称】Collector::FindTube
【函数功能】用序列号查找试管
【参数】SerialNumber： 试管序列号字符串
【返回值】pTube类型，找到返回试管指针，未找到返回nullptr
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-10
【更改记录】
    2022-07-11 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
pTube User::Collector::FindTube(std::string SerialNumber) {
    return Tube::FindTube(SerialNumber);
}

/*************************************************************************
【函数名称】Recorder::RecordTubeStatus
【函数功能】录入试管检测结果
【参数】SerialNumber： 试管序列号字符串， TetsResult：检测结果
【返回值】bool类型，找到试管返回true，未找到返回false
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-10
【更改记录】
    2022-07-11 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool User::Recorder::RecordTubeStatus(std::string SerialNumber,
                                      TestResult result) {
    pTube tube = Tube::FindTube(SerialNumber);
    if (tube != nullptr) {
        tube->m_TubeResult = result;
        this->UpdateRecord(tube);
        return true;
    } else {
        return false;
    }
}

/*************************************************************************
【函数名称】Recorder::UpdateRecord
【函数功能】更新试管检测记录到用户，此函数已在RecordTubeStatus中调用，无需单独调用
【参数】pTube：录入后的试管指针
【返回值】无
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-10
【更改记录】
    2022-07-11 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
void User::Recorder::UpdateRecord(const pTube& tube) {
    using std::begin;
    using std::end;
    for (auto it : tube->m_CollectedUsers) {
        for (auto user : m_AllUsers) {
            if (it.first.lock() == user) {
                user->m_LastTime = it.second;
                user->m_LastResult = tube->m_TubeResult;
            }
        }
    }
}

/*************************************************************************
【函数名称】User::FindUser
【函数功能】通过id查找用户，不需密码，不可在外部调用
【参数】id：用户id
【返回值】pUser类型，找到返回用户指针，未找到返回nullptr
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-10
【更改记录】
    2022-07-05 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
pUser User::FindUser(std::string id) {
    for (auto user : m_AllUsers) {
        if (user->m_ID == id) {
            return user;
        }
    }
    return nullptr;
}