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
【函数名称】ControllerBase::ParseUserFile
【函数功能】将用户数据从文件解析到内存中，构建相应对象
【参数】filename：储存用户数据文件的文件名
【返回值】bool类型：反映解析是否成功
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-13
【更改记录】
    2022-07-13 由唐春洋完善了类中功能的代码实现
    2020-07-20 由唐春洋增加注释
*************************************************************************/
bool ControllerBase::ParseUserFile(const char* filename) {
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
                std::string TestTime(
                    user_child->FirstChildElement("LastTest")->GetText());
                unsigned int year, month, day, hour, minute, second;
                stringstream ss(TestTime);
                ss >> year >> month >> day >> hour >> minute >> second;
                user->m_LastTime =
                    DateTime(year, month, day, hour, minute, second);
            } else if (result == "NEGATIVE") {
                user->m_LastResult = TestResult::NEGATIVE;
                std::string TestTime(
                    user_child->FirstChildElement("LastTest")->GetText());
                unsigned int year, month, day, hour, minute, second;
                stringstream ss(TestTime);
                ss >> year >> month >> day >> hour >> minute >> second;
                user->m_LastTime =
                    DateTime(year, month, day, hour, minute, second);
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
【函数名称】ControllerBase::ParseTubeFile
【函数功能】将试管数据从文件解析到内存中，构建相应对象
【参数】filename：储存试管数据文件的文件名
【返回值】bool类型：反映解析是否成功
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-13
【更改记录】
    2022-07-13 由唐春洋完善了类中功能的代码实现
    2020-07-20 由唐春洋增加注释
*************************************************************************/
bool ControllerBase::ParseTubeFile(const char* filename) {
    if (fopen(filename, "r") == NULL) {
        return false;
    } else {
        fclose(fopen(filename, "r"));
    }
    // 用TinyXML2解析用户文件
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    doc.LoadFile(filename);
    if (doc.Error()) {
        return false;
    }
    XMLHandle docHandle(&doc);
    // 获取子节点信息并加载到Tube对象中
    XMLElement* tube_child =
        docHandle.FirstChildElement().FirstChildElement().ToElement();
    while (tube_child) {
        std::string SerialNumber(
            tube_child->FirstChildElement("SerialNumber")->GetText());
        new Tube(SerialNumber);
        pTube tube = Tube::FindTube(SerialNumber);
        XMLElement* child = tube_child->FirstChildElement("User");
        while (child) {
            std::string ID(child->FirstChildElement("ID")->GetText());
            std::string str_datetime(
                child->FirstChildElement("DateTime")->GetText());
            unsigned int year, month, day, hour, minute, second;
            stringstream ss(str_datetime);
            ss >> year >> month >> day >> hour >> minute >> second;
            DateTime date(year, month, day, hour, minute, second);
            pwUser pw_User = User::FindUser(ID);
            tube->m_CollectedUsers.push_back(std::make_pair(pw_User, date));
            child = child->NextSiblingElement();
        }
        tube_child = tube_child->NextSiblingElement();
    }
    return true;
}

/*************************************************************************
【函数名称】ControllerBase::SavetoUserFile
【函数功能】将用户数据录入到文件中
【参数】filename：储存试管数据文件的文件名
【返回值】bool类型：反映保存是否成功
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-13
【更改记录】
    2022-07-13 由唐春洋完善了类中功能的代码实现
    2020-07-20 由唐春洋增加注释
*************************************************************************/
bool ControllerBase::SavetoUserFile(const char* filename) {
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
        stringstream ss2;
        ss2 << user->m_LastTime.m_Date.Year << " "
            << user->m_LastTime.m_Date.Month << " "
            << user->m_LastTime.m_Date.Day << " " << user->m_LastTime.Hour
            << " " << user->m_LastTime.Minute << " " << user->m_LastTime.Second;
        std::string str_result;
        if (user->m_LastResult == TestResult::POSITIVE) {
            str_result = "POSITIVE";
            LastTest->SetText(ss2.str().c_str());
        } else if (user->m_LastResult == TestResult::NEGATIVE) {
            str_result = "NEGATIVE";
            LastTest->SetText(ss2.str().c_str());
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
【函数名称】ControllerBase::SavetoTubeFile
【函数功能】将试管数据录入到文件中
【参数】filename：储存试管数据文件的文件名
【返回值】bool类型：反映保存是否成功
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-13
【更改记录】
    2022-07-13 由唐春洋完善了类中功能的代码实现
    2020-07-20 由唐春洋增加注释
*************************************************************************/
bool ControllerBase::SavetoTubeFile(const char* filename) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    XMLDeclaration* decl =
        doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    doc.InsertFirstChild(decl);
    XMLComment* comment1 =
        doc.NewComment("This is the tube-data-storing file.");
    doc.InsertEndChild(comment1);
    XMLElement* root = doc.NewElement("AllTubes");
    XMLComment* comment2 = doc.NewComment("Only UNTESTED tubes are stored.");
    root->InsertEndChild(comment2);
    doc.InsertEndChild(root);
    for (auto& tube : Tube::m_AllTubes) {
        if (tube->m_TubeResult == TestResult::UNTESTED) {
            // 新建Tube元素
            XMLElement* tube_child = doc.NewElement("Tube");
            root->InsertEndChild(tube_child);
            // 插入SerialNumber元素
            XMLElement* SerialNumber = doc.NewElement("SerialNumber");
            SerialNumber->SetText(tube->m_SerialNumber.c_str());
            tube_child->InsertEndChild(SerialNumber);
            // 插入User元素
            for (auto& user : tube->m_CollectedUsers) {
                XMLElement* user_child = doc.NewElement("User");
                tube_child->InsertEndChild(user_child);
                XMLElement* ID = doc.NewElement("ID");
                ID->SetText((user.first.lock())->m_ID.c_str());
                user_child->InsertEndChild(ID);
                stringstream ss;
                ss << user.second.m_Date.Year << " " << user.second.m_Date.Month
                   << " " << user.second.m_Date.Day << " " << user.second.Hour
                   << " " << user.second.Minute << " " << user.second.Second;
                XMLElement* DateTime = doc.NewElement("DateTime");
                DateTime->SetText(ss.str().c_str());
                user_child->InsertEndChild(DateTime);
            }
        }
    }
    if (doc.SaveFile(filename)) {
        return true;
    } else {
        return false;
    }
}

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