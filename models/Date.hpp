/*************************************************************************
【文件名】Date.hpp
【功能模块和目的】日期类声明
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

#ifndef Date_hpp
#define Date_hpp
#include <string>

/*************************************************************************
【类名】Date
【功能】日期类，用于构造、储存、操作、输出一个日期
【接口说明】
    构造函数：Date(int year, int month, int day)按日期构造Date对象
    拷贝构造函数：Date(const Date& date)拷贝构造Date对象
    设置日期函数：Set(unsigned int Year, unsigned int Month, unsigned int
Day)按年月日设置日期
    设置范围函数：SetRange(unsigned int Year, unsigned int
Month, unsigned int Day)设置最大最小年份范围
    设置格式函数：SetFormat(const
string& Format)设置获取的格式化日期字符串格式

【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-18 由唐春洋增加注释，并为各功能添加了是否符合日期格式的检查
*************************************************************************/

class Date {
public:
    // 按传入的日期构造一个日期对象
    Date(unsigned int Year = 1900, unsigned int Month = 1,
         unsigned int Day = 1);
    // 拷贝构造函数
    Date(const Date& src);

    // Setters
    bool Set(unsigned int Year, unsigned int Month, unsigned int Day);
    static bool SetRange(unsigned int minimum_Year, unsigned int maximum_Year);
    static void SetFormat(bool is_regular_format = false);

    // Checkers
    static bool IsLeapYear(unsigned int Year);
    static bool IsLeapYear(const Date& src);
    static bool IsValidDate(unsigned int Year, unsigned int Month,
                            unsigned int Day);
    static bool IsValidDate(const Date& date);
    bool IsLeapYear() const;
    bool IsValid() const;

    // Getters
    unsigned int DaysInYear() const;
    std::string GetFormatString() const;

    // 对日期的运算符重载函数
    Date& operator=(const Date& src);
    Date& operator+(const int& days) const;
    Date& operator+=(const int& days);
    Date& operator++();
    Date& operator++(int);
    bool operator!=(const Date& src) const;
    bool operator==(const Date& src) const;
    int operator-(const Date& src) const;
    Date& operator-(const int& days) const;
    Date& operator-=(const int& days);
    Date& operator--();
    Date& operator--(int);
    bool operator<(const Date& src) const;
    bool operator>(const Date& src) const;
    bool operator<=(const Date& src) const;
    bool operator>=(const Date& src) const;
    // 用于外界访问的常量引用的年
    const unsigned int& Year;
    // 用于外界访问的常量引用的月
    const unsigned int& Month;
    // 用于外界访问的常量引用的日
    const unsigned int& Day;

private:
    void DaysToDate(const int days);
    unsigned int m_Day;
    unsigned int m_Month;
    unsigned int m_Year;
    static unsigned int maxium_Year;
    static unsigned int minimum_Year;
    static bool regular_format;
    static const unsigned int days_in_month[12];
};

#endif /* Date_hpp */
