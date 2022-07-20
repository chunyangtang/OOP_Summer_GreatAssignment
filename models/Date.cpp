/*************************************************************************
【文件名】Date.cpp
【功能模块和目的】日期类实现
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【版权信息】以下代码由唐春洋根据清华大学自动化系2022年暑期“面向对象程序设计训练”课程要求独立编写，
    开发者唐春洋(tangcy21@mails.tsinghua.edu.cn)声明放弃对修改部分的任何版权诉求，任何使用者可做出任何修改、用于任何目的
    本代码遵守 CC 4.0 BY-SA 版权协议
    CC BY-SA 4.0 是一种许可协议，赋予遵守者两项重要权利：
    一、共享的权利。允许通过任何媒介和任何形式复制、发行作品。
    二、改编的权利。允许二次加工、转换和基于作品进行创作，不限制用途，甚至是商业应用。
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/

#include "Date.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

// 类静态成员初始化，表示默认最大年份为9999年
unsigned int Date::maxium_Year = 9999;
// 类静态成员初始化，表示默认最小年份为1900年
// 请注意，只有不过大或过小的年份才能保证日期的准确性
unsigned int Date::minimum_Year = 1900;
// 类静态成员初始化，表示日期默认输出格式是标准的
bool Date::regular_format = true;
// 类静态成员初始化，表示非闰年时对应月份的天数
const unsigned int Date::days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/*************************************************************************
【函数名称】Date::Date
【函数功能】构造函数，创建一个日期，将私有成员与公有常量引用关联
【参数】Year：年份，Month：月份，Day：日期
【返回值】构造函数不可有返回值
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
Date::Date(unsigned int Year, unsigned int Miniute, unsigned int Day) : Year(m_Year), Month(m_Month), Day(m_Day)
{
    if (!Set(Year, Miniute, Day))
    {
        Set(1900, 1, 1);
    }
}

Date::Date(const Date &src) : Year(m_Year), Month(m_Month), Day(m_Day)
{
    if (!IsValidDate(src))
    {
        throw std::range_error("Invalid date");
    }
    m_Year = src.m_Year;
    m_Month = src.m_Month;
    m_Day = src.m_Day;
}

// Setters
bool Date::Set(unsigned int Year, unsigned int Month, unsigned int Day)
{
    if (!IsValidDate(Year, Month, Day))
    {
        return false;
    }
    else
    {
        m_Year = Year;
        m_Month = Month;
        m_Day = Day;
        return true;
    }
}

bool Date::SetRange(unsigned int minimum_Year, unsigned int maximum_Year)
{
    if (minimum_Year > maximum_Year)
    {
        return false;
    }
    else
    {
        Date::minimum_Year = minimum_Year;
        Date::maxium_Year = maximum_Year;
        return true;
    }
}

void Date::SetFormat(bool is_regular_format)
{
    Date::regular_format = is_regular_format;
}

// Checkers
bool Date::IsLeapYear(unsigned int Year)
{
    if (Year < minimum_Year || Year > maxium_Year)
    {
        throw std::range_error("Invalid year");
    }
    return (Year % 4 == 0) && (Year % 100 != 0 || Year % 400 == 0);
}

bool Date::IsLeapYear(const Date &src)
{
    if (!IsValidDate(src))
    {
        throw std::range_error("Invalid date");
    }
    return IsLeapYear(src.m_Year);
}

bool Date::IsValidDate(unsigned int Year, unsigned int Month, unsigned int Day)
{
    if (Year < minimum_Year || Year > maxium_Year)
    {
        return false;
    }
    if (Month < 1 || Month > 12)
    {
        return false;
    }
    if (Day < 1 || Day > 31)
    {
        return false;
    }
    if (Month == 2)
    {
        if (Date::IsLeapYear(Year))
        {
            return Day <= 29;
        }
        else
        {
            return Day <= 28;
        }
    }
    else if (Month == 4 || Month == 6 || Month == 9 || Month == 11)
    {
        return Day <= 30;
    }
    else
    {
        return true;
    }
}

bool Date::IsValidDate(const Date &date)
{
    return IsValidDate(date.m_Year, date.m_Month, date.m_Day);
}

bool Date::IsLeapYear() const
{
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    return IsLeapYear(m_Year);
}

bool Date::IsValid() const
{
    return IsValidDate(m_Year, m_Month, m_Day);
}

// Getters
unsigned int Date::DaysInYear() const
{
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    unsigned int days = 0;
    for (int i = 1; i < m_Month; i++)
    {
        days += days_in_month[i - 1];
        if (i == 2 && Date::IsLeapYear(m_Year))
        {
            days++;
        }
    }
    return days + m_Day;
}

std::string Date::GetFormatString() const
{
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    std::ostringstream ostr;
    if (regular_format)
    {
        ostr << m_Year << std::setw(2) << std::setfill('0') << m_Month << std::setw(2) << std::setfill('0') << m_Day;
    }
    else
    {
        ostr << m_Year << "-" << m_Month << "-" << m_Day;
    }
    return ostr.str();
}

// Operators
Date &Date::operator=(const Date &src)
{
    if (!(IsValidDate(src) && IsValid()))
    {
        throw std::range_error("Invalid date");
    }
    if (this != &src)
    {
        m_Year = src.m_Year;
        m_Month = src.m_Month;
        m_Day = src.m_Day;
    }
    return *this;
}

Date &Date::operator+(const int &days) const
{
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    Date temp(*this);
    int temp_days = temp.DaysInYear() + days;
    temp.DaysToDate(temp_days);
    if (!IsValidDate(temp))
    {
        throw std::range_error("Invalid date");
    }
    return temp;
}

Date &Date::operator+=(const int &days)
{
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    int temp_days = DaysInYear() + days;
    DaysToDate(temp_days);
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    return *this;
}

Date &Date::operator++()
{
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    Date temp(*this);
    *this += 1;
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    return temp;
}

Date &Date::operator++(int)
{
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    *this += 1;
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    return *this;
}

bool Date::operator!=(const Date &src) const
{
    if (!(IsValidDate(src) && IsValid()))
    {
        throw std::range_error("Invalid date");
    }
    return !(*this == src);
}

bool Date::operator==(const Date &src) const
{
    if (!(IsValidDate(src) && IsValid()))
    {
        throw std::range_error("Invalid date");
    }
    return m_Year == src.m_Year && m_Month == src.m_Month && m_Day == src.m_Day;
}

int Date::operator-(const Date &src) const
{
    if (!(IsValidDate(src) && IsValid()))
    {
        throw std::range_error("Invalid date");
    }
    int days = 0;
    for (int i = src.m_Year; i != m_Year;)
    {
        if (m_Year > src.m_Year)
        {
            days += IsLeapYear(i) ? 366 : 365;
            i++;
        }
        else
        {
            days -= IsLeapYear(i - 1) ? 366 : 365;
            i--;
        }
    }
    return days + DaysInYear() - src.DaysInYear();
}

Date &Date::operator-(const int &days) const
{
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    if (!IsValidDate(*this + (-days)))
    {
        throw std::range_error("Invalid date");
    }
    return *this + (-days);
}

Date &Date::operator-=(const int &days)
{
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    *this += (-days);
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    return *this;
}

Date &Date::operator--()
{
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    Date temp = *this;
    *this -= 1;
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    return temp;
}

Date &Date::operator--(int)
{
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    *this -= 1;
    if (!IsValid())
    {
        throw std::range_error("Invalid date");
    }
    return *this;
}

bool Date::operator<(const Date &src) const
{
    if (!(IsValid() && IsValidDate(src)))
    {
        throw std::range_error("Invalid date");
    }
    if (m_Year < src.m_Year)
    {
        return true;
    }
    else if (m_Year == src.m_Year)
    {
        if (m_Month < src.m_Month)
        {
            return true;
        }
        else if (m_Month == src.m_Month)
        {
            return m_Day < src.m_Day;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Date::operator>(const Date &src) const
{
    if (!(IsValid() && IsValidDate(src)))
    {
        throw std::range_error("Invalid date");
    }
    if (m_Year > src.m_Year)
    {
        return true;
    }
    else if (m_Year == src.m_Year)
    {
        if (m_Month > src.m_Month)
        {
            return true;
        }
        else if (m_Month == src.m_Month)
        {
            return m_Day > src.m_Day;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Date::operator<=(const Date &src) const
{
    if (!(IsValid() && IsValidDate(src)))
    {
        throw std::range_error("Invalid date");
    }
    return !(*this > src);
}

bool Date::operator>=(const Date &src) const
{
    if (!(IsValid() && IsValidDate(src)))
    {
        throw std::range_error("Invalid date");
    }
    return !(*this < src);
}

// This function should be always used together with DaysInYear()
// The Current days and months value will be ignored
void Date::DaysToDate(const int day)
{
    int days = day;
    m_Day = 0;
    m_Month = 1;
    while (days <= 0)
    {
        m_Year--;
        days += (IsLeapYear(m_Year) ? 366 : 365);
    }
    while (days > (IsLeapYear(m_Year) ? 366 : 365))
    {
        if (IsLeapYear(m_Year))
        {
            days -= 366;
        }
        else
        {
            days -= 365;
        }
        m_Year++;
    }
    for (int i = 1; i < 12; i++)
    {
        if (i == 2 && IsLeapYear(m_Year))
        {
            if (days > 29)
            {
                m_Month = i + 1;
                days -= 29;
            }
            else
            {
                break;
            }
        }
        else
        {
            if (days > days_in_month[i - 1])
            {
                days -= days_in_month[i - 1];
                m_Month = i + 1;
            }
            else
            {
                break;
            }
        }
    }
    m_Day = days;
}