/*************************************************************************
【文件名】Tube.cpp
【功能模块和目的】试管类实现
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-20
【版权信息】以下代码由唐春洋根据清华大学自动化系2022年暑期“面向对象程序设计训练”课程要求独立编写，
    开发者唐春洋(tangcy21@mails.tsinghua.edu.cn)声明放弃对修改部分的任何版权诉求，任何使用者可做出任何修改、用于任何目的
    本代码遵守 CC 4.0 BY-SA 版权协议
    CC BY-SA 4.0 是一种许可协议，赋予遵守者两项重要权利：
    一、共享的权利。允许通过任何媒介和任何形式复制、发行作品。
    二、改编的权利。允许二次加工、转换和基于作品进行创作，不限制用途，甚至是商业应用。
【更改记录】
     2022-07-11 由唐春洋创建该类
     2022-07-20 由唐春洋添加注释
*************************************************************************/

#include "Tube.hpp"

// 静态列表初始化
std::list<pTube> Tube::m_AllTubes = {};

/*************************************************************************
【函数名称】Tube::LoadFile
【函数功能】将试管数据从文件解析到内存中，构建相应对象
【参数】filename：储存试管数据文件的文件名
【返回值】bool类型：反映解析是否成功
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-10
【更改记录】
    2022-07-05 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool Tube::LoadFile(const char* filename) {
    using namespace tinyxml2;
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
    try {
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
                DateTime date(std::string(
                    child->FirstChildElement("DateTime")->GetText()));

                pwUser pw_User = User::FindUser(ID);
                tube->m_CollectedUsers.push_back(std::make_pair(pw_User, date));
                child = child->NextSiblingElement();
            }
            tube_child = tube_child->NextSiblingElement();
        }
    } catch (...) {
        return false;
    }

    return true;
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
bool Tube::SaveFile(const char* filename) {
    using namespace tinyxml2;
    // 新建文档对象
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    // 添加声明
    XMLDeclaration* decl =
        doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    doc.InsertFirstChild(decl);
    // 添加注释
    XMLComment* comment1 =
        doc.NewComment("This is the tube-data-storing file.");
    doc.InsertEndChild(comment1);
    // 添加根节点
    XMLElement* root = doc.NewElement("AllTubes");
    XMLComment* comment2 = doc.NewComment("Only UNTESTED tubes are stored.");
    root->InsertEndChild(comment2);
    doc.InsertEndChild(root);
    // 循环添加试管子节点
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
                // 插入ID元素
                XMLElement* ID = doc.NewElement("ID");
                ID->SetText((user.first.lock())->ID.c_str());
                user_child->InsertEndChild(ID);
                // 插入检测时间元素
                DateTime::SetFormat(true);
                XMLElement* date_time = doc.NewElement("DateTime");
                date_time->SetText(user.second.GetFormatString().c_str());
                user_child->InsertEndChild(date_time);
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
【函数名称】Tube::Tube
【函数功能】构造试管，只有Collector、Controller可调用
【参数】SerialNumber 20位试管编号（时间+6位流水YYYYMMDDhhmmssXXXXXX）
【返回值】无
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-10
【更改记录】
    2022-07-05 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
Tube::Tube(std::string SerialNumber)
    : m_SerialNumber(SerialNumber),
      m_ProductionTime(DateTime(SerialNumber.substr(0, 14))) {
    m_TubeResult = TestResult::UNTESTED;
    m_AllTubes.push_back(std::make_shared<Tube>(*this));
    m_CollectedUsers.clear();
}

/*************************************************************************
【函数名称】Tube::FindTube
【函数功能】查找试管，由序列号得到试管指针
【参数】SerialNumber 20位试管编号（时间+6位流水YYYYMMDDhhmmssXXXXXX）
【返回值】pTube类型，为share_ptr<Tube>的别名，指向试管
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-10
【更改记录】
    2022-07-05 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
pTube Tube::FindTube(std::string SerialNumber) {
    for (auto& tube : m_AllTubes) {
        if (tube->m_SerialNumber == SerialNumber) {
            return tube;
        }
    }
    return nullptr;
}