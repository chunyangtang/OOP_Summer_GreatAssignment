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
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

// 类静态成员初始化，表示默认最大年份为9999年
unsigned int Date::maxium_Year = 9999;
// 类静态成员初始化，表示默认最小年份为1900年
// 请注意，只有不过大或过小的年份才能保证日期的准确性
unsigned int Date::minimum_Year = 1900;
// 类静态成员初始化，表示日期默认输出格式是标准的
bool Date::regular_format = true;
// 类静态成员初始化，表示非闰年时对应月份的天数
const unsigned int Date::days_in_month[12] = {31, 28, 31, 30, 31, 30,
                                              31, 31, 30, 31, 30, 31};

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
Date::Date(unsigned int Year, unsigned int Miniute, unsigned int Day)
    : Year(m_Year), Month(m_Month), Day(m_Day) {
    if (!Set(Year, Miniute, Day)) {
        Set(1900, 1, 1);
    }
}

/*************************************************************************
【函数名称】Date::Date(const Date& src)
【函数功能】拷贝构造函数，拷贝一个日期，将私有成员与公有常量引用关联
【参数】src：源日期
【返回值】构造函数不可有返回值
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
Date::Date(const Date& src) : Year(m_Year), Month(m_Month), Day(m_Day) {
    if (!IsValidDate(src)) {
        throw std::range_error("Invalid date");
    }
    m_Year = src.m_Year;
    m_Month = src.m_Month;
    m_Day = src.m_Day;
}

/*************************************************************************
【函数名称】Date::Set
【函数功能】通过单独的年月日设置日期，并进行日期的合法性检查
【参数】Year：年份，Month：月份，Day：日期
【返回值】bool型，表示是否设置成功
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
bool Date::Set(unsigned int Year, unsigned int Month, unsigned int Day) {
    if (!IsValidDate(Year, Month, Day)) {
        return false;
    } else {
        m_Year = Year;
        m_Month = Month;
        m_Day = Day;
        return true;
    }
}

/*************************************************************************
【函数名称】Date::SetRange
【函数功能】设置日期类最大最小年份范围
【参数】minimum_Year, maximum_Year：最小最大年份
【返回值】bool型，表示是否设置成功
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
bool Date::SetRange(unsigned int minimum_Year, unsigned int maximum_Year) {
    if (minimum_Year > maximum_Year) {
        return false;
    } else {
        Date::minimum_Year = minimum_Year;
        Date::maxium_Year = maximum_Year;
        return true;
    }
}

/*************************************************************************
【函数名称】Date::SetFormat
【函数功能】设置格式化日期字符串格式
【参数】is_regular_format：是否为标准格式，如果为正常格式，则格式为YYYYMMDD，如果为非正常格式，则格式为YYYY-MM-DD
【返回值】无
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
void Date::SetFormat(bool is_regular_format) {
    Date::regular_format = is_regular_format;
}

/*************************************************************************
【函数名称】Date::IsLeapYear
【函数功能】检查给定年份是否为闰年
【参数】Year：年份
【返回值】bool型，表示是否为闰年
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
bool Date::IsLeapYear(unsigned int Year) {
    if (Year < minimum_Year || Year > maxium_Year) {
        throw std::range_error("Invalid year");
    }
    return (Year % 4 == 0) && (Year % 100 != 0 || Year % 400 == 0);
}

/*************************************************************************
【函数名称】Date::IsLeapYear
【函数功能】检查一个日期是否为闰年
【参数】src：日期类对象
【返回值】bool型，表示是否为闰年
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
bool Date::IsLeapYear(const Date& src) {
    if (!IsValidDate(src)) {
        throw std::range_error("Invalid date");
    }
    return IsLeapYear(src.m_Year);
}

/*************************************************************************
【函数名称】Date::IsValidDate
【函数功能】检查一个年月日是否合法
【参数】Year：年份，Month：月份，Day：日期
【返回值】bool型，表示是否合法
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
bool Date::IsValidDate(unsigned int Year, unsigned int Month,
                       unsigned int Day) {
    if (Year < minimum_Year || Year > maxium_Year) {
        return false;
    }
    if (Month < 1 || Month > 12) {
        return false;
    }
    if (Day < 1 || Day > 31) {
        return false;
    }
    if (Month == 2) {
        if (Date::IsLeapYear(Year)) {
            return Day <= 29;
        } else {
            return Day <= 28;
        }
    } else if (Month == 4 || Month == 6 || Month == 9 || Month == 11) {
        return Day <= 30;
    } else {
        return true;
    }
}

/*************************************************************************
【函数名称】Date::IsValidDate
【函数功能】检查一个日期是否合法
【参数】date：日期类对象
【返回值】bool型，表示是否合法
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
bool Date::IsValidDate(const Date& date) {
    return IsValidDate(date.m_Year, date.m_Month, date.m_Day);
}

/*************************************************************************
【函数名称】Date::IsLeapYear
【函数功能】检查自身的年份是否为闰年
【参数】无
【返回值】bool型，表示是否是闰年
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
bool Date::IsLeapYear() const {
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    return IsLeapYear(m_Year);
}

/*************************************************************************
【函数名称】Date::IsValid
【函数功能】检查自身日期是否合法
【参数】无
【返回值】bool型，表示是否合法
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
bool Date::IsValid() const { return IsValidDate(m_Year, m_Month, m_Day); }

/*************************************************************************
【函数名称】Date::DaysInYear
【函数功能】获取日期中当年经过的天数
【参数】无
【返回值】unsigned int型，表示当年经过的天数
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
unsigned int Date::DaysInYear() const {
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    unsigned int days = 0;
    for (int i = 1; i < m_Month; i++) {
        days += days_in_month[i - 1];
        if (i == 2 && Date::IsLeapYear(m_Year)) {
            days++;
        }
    }
    return days + m_Day;
}

/*************************************************************************
【函数名称】Date::GetFormatString
【函数功能】获取日期的字符串
【参数】无
【返回值】string型，表示日期的字符串
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
std::string Date::GetFormatString() const {
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    std::ostringstream ostr;
    if (regular_format) {
        ostr << m_Year << std::setw(2) << std::setfill('0') << m_Month
             << std::setw(2) << std::setfill('0') << m_Day;
    } else {
        ostr << m_Year << "-" << m_Month << "-" << m_Day;
    }
    return ostr.str();
}

/*************************************************************************
【函数名称】Date::operator=
【函数功能】赋值运算符重载
【参数】src：Date型源日期
【返回值】Date型，表示自身的引用
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
Date& Date::operator=(const Date& src) {
    if (!(IsValidDate(src) && IsValid())) {
        throw std::range_error("Invalid date");
    }
    if (this != &src) {
        m_Year = src.m_Year;
        m_Month = src.m_Month;
        m_Day = src.m_Day;
    }
    return *this;
}

/*************************************************************************
【函数名称】Date::operator+
【函数功能】加号运算符重载
【参数】days 表示天数的整数
【返回值】Date型，表示相加后的结果
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
Date& Date::operator+(const int& days) const {
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    Date* temp = new Date(*this);
    int temp_days = temp->DaysInYear() + days;
    temp->DaysToDate(temp_days);
    if (!IsValidDate(*temp)) {
        throw std::range_error("Invalid date");
    }
    return *temp;
}

/*************************************************************************
【函数名称】Date::operator+=
【函数功能】自增运算符重载
【参数】days 表示增加天数的整数
【返回值】Date型，表示相加后自身的引用
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
Date& Date::operator+=(const int& days) {
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    int temp_days = DaysInYear() + days;
    DaysToDate(temp_days);
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    return *this;
}

/*************************************************************************
【函数名称】Date::operator++
【函数功能】自增运算符重载
【参数】无
【返回值】Date型，表示增加一天前的引用
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
Date& Date::operator++() {
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    Date* temp = new Date(*this);
    *this += 1;
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    return *temp;
}

/*************************************************************************
【函数名称】Date::operator++
【函数功能】自增运算符重载
【参数】无
【返回值】Date型，表示增加一天后自身的引用
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
Date& Date::operator++(int) {
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    *this += 1;
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    return *this;
}

/*************************************************************************
【函数名称】Date::operator!=
【函数功能】不等于运算符重载
【参数】src 表示另一个Date型的对象
【返回值】bool型，表示两个对象是否不等于
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
bool Date::operator!=(const Date& src) const {
    if (!(IsValidDate(src) && IsValid())) {
        throw std::range_error("Invalid date");
    }
    return !(*this == src);
}

/*************************************************************************
【函数名称】Date::operator==
【函数功能】等于判断运算符重载
【参数】src 表示另一个Date型的对象
【返回值】bool型，表示两个对象是否相等
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
bool Date::operator==(const Date& src) const {
    if (!(IsValidDate(src) && IsValid())) {
        throw std::range_error("Invalid date");
    }
    return m_Year == src.m_Year && m_Month == src.m_Month && m_Day == src.m_Day;
}

/*************************************************************************
【函数名称】Date::operator-
【函数功能】减法运算符重载
【参数】src 表示另一个Date型的对象
【返回值】int型，表示两个对象的日期差
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
int Date::operator-(const Date& src) const {
    if (!(IsValidDate(src) && IsValid())) {
        throw std::range_error("Invalid date");
    }
    int days = 0;
    for (int i = src.m_Year; i != m_Year;) {
        if (m_Year > src.m_Year) {
            days += IsLeapYear(i) ? 366 : 365;
            i++;
        } else {
            days -= IsLeapYear(i - 1) ? 366 : 365;
            i--;
        }
    }
    return days + DaysInYear() - src.DaysInYear();
}

/*************************************************************************
【函数名称】Date::operator-
【函数功能】减法运算符重载
【参数】days 表示一个天数
【返回值】Date型，表示当前日期减去days天后的日期
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
Date& Date::operator-(const int& days) const {
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    if (!IsValidDate(*this + (-days))) {
        throw std::range_error("Invalid date");
    }
    return *this + (-days);
}

/*************************************************************************
【函数名称】Date::operator-=
【函数功能】自减运算符重载
【参数】days 表示一个天数
【返回值】Date型，表示当前日期减去days天后自身的引用
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
Date& Date::operator-=(const int& days) {
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    *this += (-days);
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    return *this;
}

/*************************************************************************
【函数名称】Date::operator--
【函数功能】自减运算符重载
【参数】无
【返回值】Date型，表示当前日期减去一天前的引用
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
Date& Date::operator--() {
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    Date* temp = new Date(*this);
    *this -= 1;
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    return *temp;
}

/*************************************************************************
【函数名称】Date::operator--
【函数功能】自减运算符重载
【参数】无
【返回值】Date型，表示当前日期减去一天后自身的引用
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
Date& Date::operator--(int) {
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    *this -= 1;
    if (!IsValid()) {
        throw std::range_error("Invalid date");
    }
    return *this;
}

/*************************************************************************
【函数名称】Date::operator<
【函数功能】小于运算符重载
【参数】src 表示一个日期
【返回值】bool型，表示当前日期是否在src之前
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
bool Date::operator<(const Date& src) const {
    if (!(IsValid() && IsValidDate(src))) {
        throw std::range_error("Invalid date");
    }
    if (m_Year < src.m_Year) {
        return true;
    } else if (m_Year == src.m_Year) {
        if (m_Month < src.m_Month) {
            return true;
        } else if (m_Month == src.m_Month) {
            return m_Day < src.m_Day;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

/*************************************************************************
【函数名称】Date::operator>
【函数功能】大于运算符重载
【参数】src 表示一个日期
【返回值】bool型，表示当前日期是否在src之后
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
bool Date::operator>(const Date& src) const {
    if (!(IsValid() && IsValidDate(src))) {
        throw std::range_error("Invalid date");
    }
    if (m_Year > src.m_Year) {
        return true;
    } else if (m_Year == src.m_Year) {
        if (m_Month > src.m_Month) {
            return true;
        } else if (m_Month == src.m_Month) {
            return m_Day > src.m_Day;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

/*************************************************************************
【函数名称】Date::operator<=
【函数功能】小于等于运算符重载
【参数】src 表示一个日期
【返回值】bool型，表示当前日期是否在src之前或等于src
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
bool Date::operator<=(const Date& src) const {
    if (!(IsValid() && IsValidDate(src))) {
        throw std::range_error("Invalid date");
    }
    return !(*this > src);
}

/*************************************************************************
【函数名称】Date::operator>=
【函数功能】大于等于运算符重载
【参数】src 表示一个日期
【返回值】bool型，表示当前日期是否在src之后或等于src
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
bool Date::operator>=(const Date& src) const {
    if (!(IsValid() && IsValidDate(src))) {
        throw std::range_error("Invalid date");
    }
    return !(*this < src);
}

/*************************************************************************
【函数名称】Date::DaysToDate
【函数功能】将一个天数写入本对象当年的日期，本函数会忽略原日期
【参数】day 表示天数
【返回值】无
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/
void Date::DaysToDate(const int day) {
    int days = day;
    m_Day = 0;
    m_Month = 1;
    while (days <= 0) {
        m_Year--;
        days += (IsLeapYear(m_Year) ? 366 : 365);
    }
    while (days > (IsLeapYear(m_Year) ? 366 : 365)) {
        if (IsLeapYear(m_Year)) {
            days -= 366;
        } else {
            days -= 365;
        }
        m_Year++;
    }
    for (int i = 1; i < 12; i++) {
        if (i == 2 && IsLeapYear(m_Year)) {
            if (days > 29) {
                m_Month = i + 1;
                days -= 29;
            } else {
                break;
            }
        } else {
            if (days > days_in_month[i - 1]) {
                days -= days_in_month[i - 1];
                m_Month = i + 1;
            } else {
                break;
            }
        }
    }
    m_Day = days;
}