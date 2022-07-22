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
    判断给定年份是否为闰年 IsLeapYear(unsigned int Year)
    判断给定的年月日是否符合格式 IsValidDate(unsigned int Year, unsigned int
Month, unsigned int Day)
    判断给定的日期是否符合格式 IsValidDate(const Date& date)
    判断自身是否是闰年 IsLeapYear() const
    判断自身是否符合格式IsValid() const
    获取当前日期在今年的天数 DaysInYear() const
    获取格式化字符串 GetFormatString() const
    =运算符重载，将右侧的日期赋值给左侧的日期 operator=(const Date& src)
    +运算符重载，将左侧的日期加上给定的天数，返回新的日期 operator+(const int&
days) const
    +=运算符重载， 将自身加上给定的天数，返回自身 operator+=(const int& days)
    ++运算符重载，先返回自身，再将自身加上1天 operator++()
    ++运算符重载，先将自身加上1天，再返回自身 operator++(int)
    !=运算符重载， 判断两个日期是否不同 operator!=(const Date& src) const
    ==运算符重载， 判断两个日期是否相同 operator==(const Date& src) const
    -运算符重载， 计算两个日期相差的天数 operator-(const Date& src) const
    -运算符重载， 将左侧的日期减去给定的天数，返回新的日期 operator-(const int&
days) const
    -=运算符重载， 将自身减去给定的天数，返回自身 operator-=(const int& days)
    --运算符重载， 先返回自身，再将自身减去1天 operator--()
    --运算符重载， 先将自身减去1天，再返回自身 operator--(int)
    <运算符重载， 判断左侧的日期是否小于右侧的日期 operator<(const Date& src)
const
    >运算符重载， 判断左侧的日期是否大于右侧的日期 operator>(const Date& src)
const
    <=运算符重载， 判断左侧的日期是否小于等于右侧的日期 operator<=(const Date&
src) const
    >=运算符重载， 判断左侧的日期是否大于等于右侧的日期 operator>=(const Date&
src) const
    用于外界访问的常量引用的年 const unsigned int& Year
    用于外界访问的常量引用的月 const unsigned int& Month
    用于外界访问的常量引用的日 const unsigned int& Day
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

    // 通过单独的年月日设置日期
    bool Set(unsigned int Year, unsigned int Month, unsigned int Day);
    // 设置最大最小年份范围
    static bool SetRange(unsigned int minimum_Year, unsigned int maximum_Year);
    // 设置格式化日期字符串格式
    static void SetFormat(bool is_regular_format = false);

    // 判断给定年份是否为闰年
    static bool IsLeapYear(unsigned int Year);
    // 判断给定的日期是否为闰年
    static bool IsLeapYear(const Date& src);
    // 判断给定的年月日是否符合格式
    static bool IsValidDate(unsigned int Year, unsigned int Month,
                            unsigned int Day);
    // 判断给定的日期是否符合格式
    static bool IsValidDate(const Date& date);
    // 判断自身是否是闰年
    bool IsLeapYear() const;
    // 判断自身是否符合格式
    bool IsValid() const;

    // 获取当前日期在今年的天数
    unsigned int DaysInYear() const;
    // 获取格式化字符串
    std::string GetFormatString() const;

    // =运算符重载， 将右侧的日期赋值给左侧的日期
    Date& operator=(const Date& src);
    // +运算符重载， 将左侧的日期加上给定的天数，返回新的日期
    Date& operator+(const int& days) const;
    // +=运算符重载， 将自身加上给定的天数，返回自身
    Date& operator+=(const int& days);
    // ++运算符重载，先返回自身，再将自身加上1天
    Date& operator++();
    // ++运算符重载，先将自身加上1天，再返回自身
    Date& operator++(int);
    // !=运算符重载， 判断两个日期是否不同
    bool operator!=(const Date& src) const;
    // ==运算符重载， 判断两个日期是否相同
    bool operator==(const Date& src) const;
    // -运算符重载， 计算两个日期相差的天数
    int operator-(const Date& src) const;
    // -运算符重载， 将左侧的日期减去给定的天数，返回新的日期
    Date& operator-(const int& days) const;
    // -=运算符重载， 将自身减去给定的天数，返回自身
    Date& operator-=(const int& days);
    // --运算符重载， 先返回自身，再将自身减去1天
    Date& operator--();
    // --运算符重载， 先将自身减去1天，再返回自身
    Date& operator--(int);
    // <运算符重载， 判断左侧的日期是否小于右侧的日期
    bool operator<(const Date& src) const;
    // >运算符重载， 判断左侧的日期是否大于右侧的日期
    bool operator>(const Date& src) const;
    // <=运算符重载， 判断左侧的日期是否小于等于右侧的日期
    bool operator<=(const Date& src) const;
    // >=运算符重载， 判断左侧的日期是否大于等于右侧的日期
    bool operator>=(const Date& src) const;
    // 用于外界访问的常量引用的年
    const unsigned int& Year;
    // 用于外界访问的常量引用的月
    const unsigned int& Month;
    // 用于外界访问的常量引用的日
    const unsigned int& Day;

private:
    // 将传入的天数转换为月和日
    // 此函数只应被DaysInYear()调用
    void DaysToDate(const int days);
    // 私有的变量天
    unsigned int m_Day;
    // 私有的变量月
    unsigned int m_Month;
    // 私有的变量年
    unsigned int m_Year;
    // 静态变量最大年份
    static unsigned int maxium_Year;
    // 静态变量最小年份
    static unsigned int minimum_Year;
    // 静态变量设置日期字符串格式
    static bool regular_format;
    // 静态常量，存储每月天数
    static const unsigned int days_in_month[12];
};

#endif /* Date_hpp */
