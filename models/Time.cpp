/*************************************************************************
【文件名】Time.cpp
【功能模块和目的】时间类实现
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【版权信息】以下代码由唐春洋根据清华大学自动化系2022年暑期“面向对象程序设计训练”课程要求独立编写，
    开发者唐春洋(tangcy21@mails.tsinghua.edu.cn)声明放弃对修改部分的任何版权诉求，任何使用者可做出任何修改、用于任何目的
    本代码遵守 CC 4.0 BY-SA 版权协议
    CC BY-SA 4.0 是一种许可协议，赋予遵守者两项重要权利：
    一、共享的权利。允许通过任何媒介和任何形式复制、发行作品。
    二、改编的权利。允许二次加工、转换和基于作品进行创作，不限制用途，甚至是商业应用。
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-20 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/

#include "Time.hpp"
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

// 类静态成员初始化，默认24小时制表示
bool Time::Is24Hours = true;
// 类静态成员初始化，默认格式化输出
bool Time::regular_format = true;

/*************************************************************************
【函数名称】Time::Time
【函数功能】构造函数，创建一个时间，将私有成员与公有常量引用关联
【参数】Hour：小时， Minute：分钟， Second：秒
【返回值】构造函数不可有返回值
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了功能的代码实现
*************************************************************************/
Time::Time(unsigned int Hour, unsigned int Minute, unsigned int Second)
    : Hour(m_Hour), Minute(m_Minute), Second(m_Second) {
    if (!Set(Hour, Minute, Second)) {
        Set(0, 0, 0);
    }
}

/*************************************************************************
【函数名称】Time::Time
【函数功能】拷贝构造函数
【参数】const Time&：一个时间对象
【返回值】构造函数不可有返回值
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了功能的代码实现
*************************************************************************/
Time::Time(const Time& src) : Hour(m_Hour), Minute(m_Minute), Second(m_Second) {
    if (!IsValidTime(src)) {
        throw std::range_error("Invalid time");
    }
    m_Hour = src.m_Hour;
    m_Minute = src.m_Minute;
    m_Second = src.m_Second;
}

/*************************************************************************
【函数名称】Time::IsValidTime
【函数功能】判断时间是否合法
【参数】Hour：小时， Minute：分钟， Second：秒
【返回值】bool类型，合法为真，非法为假
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了功能的代码实现
*************************************************************************/
bool Time::IsValidTime(unsigned int Hour, unsigned int Minute,
                       unsigned int Second) {
    if (Hour > 23 || Minute > 59 || Second > 59) {
        return false;
    }
    return true;
}

/*************************************************************************
【函数名称】Time::IsValidTime
【函数功能】判断时间是否合法
【参数】const Time&：一个时间对象
【返回值】bool类型，合法为真，非法为假
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了功能的代码实现
*************************************************************************/
bool Time::IsValidTime(const Time& time) {
    return IsValidTime(time.m_Hour, time.m_Minute, time.m_Second);
}

/*************************************************************************
【函数名称】Time::IsValidTime
【函数功能】判断自身时间是否合法
【参数】无
【返回值】bool类型，合法为真，非法为假
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了功能的代码实现
*************************************************************************/
bool Time::IsValid() const { return IsValidTime(m_Hour, m_Minute, m_Second); }

/*************************************************************************
【函数名称】Time::Set
【函数功能】若时间合法则设置时间
【参数】Hour：小时， Minute：分钟， Second：秒
【返回值】bool类型，输入时间合法为真，非法为假
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了功能的代码实现
*************************************************************************/
bool Time::Set(unsigned int Hour, unsigned int Miniute, unsigned int Second) {
    return SetHour(Hour) && SetMinute(Miniute) && SetSecond(Second);
}

/*************************************************************************
【函数名称】Time::SetHour
【函数功能】若时间合法则设置小时
【参数】Hour：小时
【返回值】bool类型，输入时间合法为真，非法为假
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了功能的代码实现
*************************************************************************/
bool Time::SetHour(unsigned int Hour) {
    bool IsRight = Hour < 24;
    m_Hour = IsRight ? Hour : m_Hour;
    return IsRight;
}

/*************************************************************************
【函数名称】Time::SetMinute
【函数功能】若时间合法则设置分钟
【参数】Minute：分钟
【返回值】bool类型，输入时间合法为真，非法为假
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了功能的代码实现
*************************************************************************/
bool Time::SetMinute(unsigned int Minute) {
    bool IsRight = Minute < 60;
    m_Minute = IsRight ? Minute : m_Minute;
    return IsRight;
}

/*************************************************************************
【函数名称】Time::SetSecond
【函数功能】若时间合法则设置秒
【参数】Second：秒
【返回值】bool类型，输入时间合法为真，非法为假
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了功能的代码实现
*************************************************************************/
bool Time::SetSecond(unsigned int Second) {
    bool IsRight = Second < 60;
    m_Second = IsRight ? Second : m_Second;
    return IsRight;
}

/*************************************************************************
【函数名称】Time::Set24Hours
【函数功能】设置输出的format-string时间是否为24小时制
【参数】Is24Hours 真表示以24小时制输出时间，假表示以12小时制输出时间
【返回值】无
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了功能的代码实现
*************************************************************************/
void Time::Set24Hours(bool Is24Hours) { Time::Is24Hours = Is24Hours; }

/*************************************************************************
【函数名称】Time::SetFormat
【函数功能】设置输出的format-string时间是否含“:”
【参数】IsRegularFormat 真表示输出时不含“：”，假表示输出时含“：”
【返回值】无
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-7-20 由唐春洋完善了功能的代码实现
*************************************************************************/
void Time::SetFormat(bool IsRegularFormat) {
    Time::regular_format = IsRegularFormat;
}

/*************************************************************************
【函数名称】Time::Seconds
【函数功能】计算某一时间对应自0：0：0到此刻经过的秒数
【参数】无
【返回值】unsigned int类型，为计算得的秒数
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-7-20 由唐春洋完善了功能的代码实现
*************************************************************************/
unsigned int Time::Seconds() const {
    if (!IsValid()) {
        throw std::range_error("Invalid time");
    }
    return m_Hour * 3600u + m_Minute * 60u + m_Second;
}

/*************************************************************************
【函数名称】Time::GetFormatString
【函数功能】获取格式化的表示当前时间的字符串
【参数】无
【返回值】std::string类型，表示当前时间的格式化字符串
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-7-20 由唐春洋完善了功能的代码实现
*************************************************************************/
std::string Time::GetFormatString() const {
    if (!IsValid()) {
        throw std::range_error("Invalid time");
    }
    std::ostringstream ostr;
    unsigned int Temp_Hour;
    if (Is24Hours) {
        Temp_Hour = m_Hour;
    } else {
        Temp_Hour = m_Hour < 12 ? m_Hour : m_Hour - 12;
    }

    if (regular_format) {
        ostr << std::setw(2) << std::setfill('0') << Temp_Hour << std::setw(2)
             << std::setfill('0') << m_Minute << std::setw(2)
             << std::setfill('0') << m_Second;
    } else {
        ostr << std::setfill('0') << std::setw(2) << Temp_Hour << ":"
             << std::setfill('0') << std::setw(2) << m_Minute << ":"
             << std::setfill('0') << std::setw(2) << m_Second;
    }
    return ostr.str();
}

/*************************************************************************
【函数名称】Time::operator=
【函数功能】赋值运算符重载
【参数】const Time& 时间对象
【返回值】被赋值后的对象
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-7-20 由唐春洋完善了功能的代码实现
*************************************************************************/
Time& Time::operator=(const Time& src) {
    if (!(IsValidTime(src) && IsValid())) {
        throw std::range_error("Invalid time");
    }
    if (this != &src) {
        m_Hour = src.m_Hour;
        m_Minute = src.m_Minute;
        m_Second = src.m_Second;
    }
    return *this;
}