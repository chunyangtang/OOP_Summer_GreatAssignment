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
【函数名称】Tube::Tube
【函数功能】构造试管，只有Collector、Controller可调用
【参数】SerialNumber 20位试管编号（时间+6位流水YYYYMMDDhhmmssXXXXXX）
【返回值】无
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-10
【更改记录】
    2022-07-05 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
Tube::Tube(std::string SerialNumber) : m_SerialNumber(SerialNumber) {
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