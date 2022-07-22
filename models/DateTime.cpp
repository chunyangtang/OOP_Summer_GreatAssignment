/*************************************************************************
【文件名】DateTime.cpp
【功能模块和目的】日期时间类实现
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-06-29
【版权信息】以下代码由唐春洋根据清华大学自动化系2022年暑期“面向对象程序设计训练”课程要求独立编写，
    开发者唐春洋(tangcy21@mails.tsinghua.edu.cn)声明放弃对修改部分的任何版权诉求，任何使用者可做出任何修改、用于任何目的
    本代码遵守 CC 4.0 BY-SA 版权协议
    CC BY-SA 4.0 是一种许可协议，赋予遵守者两项重要权利：
    一、共享的权利。允许通过任何媒介和任何形式复制、发行作品。
    二、改编的权利。允许二次加工、转换和基于作品进行创作，不限制用途，甚至是商业应用。
【更改记录】
    2022-07-20 由唐春洋创建
*************************************************************************/

#include "DateTime.hpp"
#include <stdexcept>
#include <string>

/*************************************************************************
【函数名称】DateTime::DateTime
【函数功能】构造函数，若传入时间不合法则使用1900-01-01 00:00:00
【参数】Year：年 Month：月 Day：日 Hour：时 Minute：分 Second：秒
【返回值】无
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-06-29
【更改记录】
    2022-06-29 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
DateTime::DateTime(unsigned int Year, unsigned int Month, unsigned int Day,
                   unsigned int Hour, unsigned int Minute, unsigned int Second)
    : Hour(m_Hour), Minute(m_Minute), Second(m_Second) {
    if (!(Set(Hour, Minute, Second) && m_Date.Set(Year, Month, Day))) {
        Set(1900, 1, 1, 0, 0, 0);
    }
}

/*************************************************************************
【函数名称】DateTime::DateTime
【函数功能】拷贝构造函数
【参数】src：源对象
【返回值】无
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-06-29
【更改记录】
    2022-06-29 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
DateTime::DateTime(const DateTime& src)
    : Hour(m_Hour), Minute(m_Minute), Second(m_Second) {
    if (!IsValidDateTime(src)) {
        throw std::invalid_argument("Invalid DateTime");
    }
    m_Date = src.m_Date;
    m_Hour = src.m_Hour;
    m_Minute = src.m_Minute;
    m_Second = src.m_Second;
}

/*************************************************************************
【函数名称】DateTime::Set
【函数功能】设置时间日期函数
【参数】Year：年 Month：月 Day：日 Hour：时 Minute：分 Second：秒
【返回值】bool型，传入时间合法则设置成功返回true，否则返回false
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-06-29
【更改记录】
    2022-06-29 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool DateTime::Set(unsigned int Year, unsigned int Month, unsigned int Day,
                   unsigned int Hour, unsigned int Minute,
                   unsigned int Second) {
    return m_Date.Set(Year, Month, Day) && Set(Hour, Minute, Second);
}

/*************************************************************************
【函数名称】DateTime::SetDate
【函数功能】设置日期函数
【参数】Year：年 Month：月 Day：日
【返回值】bool型，传入日期合法则设置成功返回true，否则返回false
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-06-29
【更改记录】
    2022-06-29 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool DateTime::SetDate(unsigned int Year, unsigned int Month,
                       unsigned int Day) {
    return m_Date.Set(Year, Month, Day);
}

/*************************************************************************
【函数名称】DateTime::SetTime
【函数功能】设置时间函数
【参数】Hour：时 Minute：分 Second：秒
【返回值】bool型，传入时间合法则设置成功返回true，否则返回false
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-06-29
【更改记录】
    2022-06-29 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool DateTime::SetTime(unsigned int Hour, unsigned int Minute,
                       unsigned int Second) {
    return Time::Set(Hour, Minute, Second);
}

/*************************************************************************
【函数名称】DateTime::SetDate
【函数功能】设置日期函数
【参数】Date：日期
【返回值】无
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-06-29
【更改记录】
    2022-06-29 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
void DateTime::SetDate(const Date& date) {
    if (!Date::IsValidDate(date)) {
        throw std::invalid_argument("Invalid Date");
    }
    m_Date = date;
}

/*************************************************************************
【函数名称】DateTime::SetTime
【函数功能】设置时间函数
【参数】Time：时间
【返回值】无
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-06-29
【更改记录】
    2022-06-29 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
void DateTime::SetTime(const Time& time) {
    if (!Time::IsValidTime(time)) {
        throw std::invalid_argument("Invalid Time");
    }
    Time::Set(time.Hour, time.Minute, time.Second);
}

/*************************************************************************
【函数名称】DateTime::SetFormat
【函数功能】设置输出字符串的格式
【参数】is_regular_format：true表示格式为YYYYMMDDhhmmss，false表示格式为YYYY-MM-DD
hh:mm:ss
【返回值】无
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-06-29
【更改记录】
    2022-06-29 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
void DateTime::SetFormat(bool is_regular_format) {
    regular_format = is_regular_format;
    Date::SetFormat(is_regular_format);
}

/*************************************************************************
【函数名称】DateTime::IsValidDateTime
【函数功能】判断时间日期是否合法
【参数】Year：年 Month：月 Day：日 Hour：时 Minute：分 Second：秒
【返回值】bool型，合法则返回true，否则返回false
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-06-29
【更改记录】
    2022-06-29 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool DateTime::IsValidDateTime(unsigned int Year, unsigned int Month,
                               unsigned int Day, unsigned int Hour,
                               unsigned int Minute, unsigned int Second) {
    return Date::IsValidDate(Year, Month, Day) &&
           Time::IsValidTime(Hour, Minute, Second);
}

/*************************************************************************
【函数名称】DateTime::IsValidDateTime
【函数功能】判断时间日期是否合法
【参数】datetime：时间日期对象
【返回值】bool型，合法则返回true，否则返回false
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-06-29
【更改记录】
    2022-06-29 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool DateTime::IsValidDateTime(const DateTime& dateTime) {
    return dateTime.IsValid();
}

/*************************************************************************
【函数名称】DateTime::IsValid
【函数功能】判断自身是否合法
【参数】无
【返回值】bool型，合法则返回true，否则返回false
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-06-29
【更改记录】
    2022-06-29 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
bool DateTime::IsValid() const { return m_Date.IsValid() && Time::IsValid(); }

/*************************************************************************
【函数名称】DateTime::GetFormatString
【函数功能】获取日期时间输出的字符串
【参数】无
【返回值】string型，日期时间输出的字符串
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-06-29
【更改记录】
    2022-06-29 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
std::string DateTime::GetFormatString() const {
    if (!IsValid()) {
        throw std::invalid_argument("Invalid DateTime");
    }
    if (regular_format) {
        return m_Date.GetFormatString() + Time::GetFormatString();
    } else {
        return m_Date.GetFormatString() + ' ' + Time::GetFormatString();
    }
}

/*************************************************************************
【函数名称】DateTime::operator=
【函数功能】赋值运算符重载
【参数】src：源时间日期对象
【返回值】DateTime型，自身对象
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-06-29
【更改记录】
    2022-06-29 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释
*************************************************************************/
DateTime& DateTime::operator=(const DateTime& src) {
    if (!(IsValidDateTime(src) && IsValid())) {
        throw std::invalid_argument("Invalid DateTime");
    }
    if (this != &src) {
        m_Date = src.m_Date;
        m_Hour = src.m_Hour;
        m_Minute = src.m_Minute;
        m_Second = src.m_Second;
    }
    return *this;
}