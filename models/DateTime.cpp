/*************************************************************************
【文件名】DateTime.cpp
【功能模块和目的】日期时间类实现
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-07-20
【版权信息】以下代码由唐春洋根据清华大学自动化系2022年暑期“面向对象程序设计训练”课程要求独立编写，
    开发者唐春洋(tangcy21@mails.tsinghua.edu.cn)声明放弃对修改部分的任何版权诉求，任何使用者可做出任何修改、用于任何目的
    本代码遵守 CC 4.0 BY-SA 版权协议
    CC BY-SA 4.0 是一种许可协议，赋予遵守者两项重要权利：
    一、共享的权利。允许通过任何媒介和任何形式复制、发行作品。
    二、改编的权利。允许二次加工、转换和基于作品进行创作，不限制用途，甚至是商业应用。
【更改记录】
    2020-07-20 由唐春洋创建
*************************************************************************/

#include "DateTime.hpp"
#include <stdexcept>
#include <string>

DateTime::DateTime(unsigned int Year, unsigned int Month, unsigned int Day,
                   unsigned int Hour, unsigned int Minute, unsigned int Second)
    : Hour(m_Hour), Minute(m_Minute), Second(m_Second) {
    if (!(Set(Hour, Minute, Second) && m_Date.Set(Year, Month, Day))) {
        Set(1900, 1, 1, 0, 0, 0);
    }
}

DateTime::DateTime(const DateTime& src) {
    if (!IsValidDateTime(src)) {
        throw std::invalid_argument("Invalid DateTime");
    }
    m_Date = src.m_Date;
    m_Hour = src.m_Hour;
    m_Minute = src.m_Minute;
    m_Second = src.m_Second;
}

DateTime::DateTime(const Date& date, const Time& time) {
    m_Date = date;
    Time::Time(time);
}

bool DateTime::Set(unsigned int Year, unsigned int Month, unsigned int Day,
                   unsigned int Hour, unsigned int Minute,
                   unsigned int Second) {
    return m_Date.Set(Year, Month, Day) && Set(Hour, Minute, Second);
}
bool DateTime::SetDate(unsigned int Year, unsigned int Month,
                       unsigned int Day) {
    return m_Date.Set(Year, Month, Day);
}
bool DateTime::SetTime(unsigned int Hour, unsigned int Minute,
                       unsigned int Second) {
    return Time::Set(Hour, Minute, Second);
}
void DateTime::SetDate(const Date& date) {
    if (!Date::IsValidDate(date)) {
        throw std::invalid_argument("Invalid Date");
    }
    m_Date = date;
}
void DateTime::SetTime(const Time& time) {
    if (!Time::IsValidTime(time)) {
        throw std::invalid_argument("Invalid Time");
    }
    Time::Set(time.Hour, time.Minute, time.Second);
}

bool DateTime::IsValidDateTime(unsigned int Year, unsigned int Month,
                               unsigned int Day, unsigned int Hour,
                               unsigned int Minute, unsigned int Second) {
    return Date::IsValidDate(Year, Month, Day) &&
           Time::IsValidTime(Hour, Minute, Second);
}

bool DateTime::IsValidDateTime(const DateTime& dateTime) {
    return dateTime.IsValid();
}

bool DateTime::IsValid() const { return m_Date.IsValid() && Time::IsValid(); }

std::string DateTime::GetFormatString() const {
    if (!IsValid()) {
        throw std::invalid_argument("Invalid DateTime");
    }
    return m_Date.GetFormatString() + Time::GetFormatString();
}

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