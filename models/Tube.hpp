/*************************************************************************
【文件名】Tube.hpp
【功能模块和目的】试管类声明
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

#ifndef Tube_hpp
#define Tube_hpp

#include "../controllers/ControllerBase.hpp"
#include "DateTime.hpp"
#include "User.hpp"
#include <list>
#include <memory>
#include <string>
#include <vector>

// 定义用户智能指针的别名
class User;
using pUser = std::shared_ptr<User>;
using pwUser = std::weak_ptr<User>;
// 定义试管智能指针的别名
class Tube;
using pTube = std::shared_ptr<Tube>;

class ControllerBase;
enum class TestResult;

/*************************************************************************
【类名】Tube
【功能】表示试管的类
【接口说明】
    构造函数：Tube(std::string SerialNumber, unsigned
MaxCapasity)用序列号与最大容量初始化试管
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-07-20
【更改记录】
     2022-07-20 由唐春洋创建该类
*************************************************************************/
class Tube {
private:
    // 声明控制器类为友元，为与文件交换数据
    friend class ControllerBase;
    // 友元函数声明，只有解析、保存文件函数可以访问试管
    // friend int ControllerBase::ParseTubeFile(const char* filename);
    // friend int ControllerBase::SavetoTubeFile(const char* filename);
    // 友元类声明，只有Collector、Recorder才可以管理试管
    friend class User;
    // 使用序列号构造试管
    Tube(std::string SerialNumber);
    // 查找试管
    static pTube FindTube(std::string SerialNumber);
    // 试管编号
    std::string m_SerialNumber;
    // 试管包含的用户与采集时间
    std::vector<std::pair<pwUser, DateTime>> m_CollectedUsers;

    // 试管检测结果
    TestResult m_TubeResult;
    // 静态变量，储存全部试管指针的list
    static std::list<pTube> m_AllTubes;
};

#endif