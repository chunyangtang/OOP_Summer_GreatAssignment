/*************************************************************************
【文件名】DateTime.hpp
【功能模块和目的】日期时间类声明
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-06-29
【版权信息】以下代码由唐春洋根据清华大学自动化系2022年暑期“面向对象程序设计训练”课程要求独立编写，
    开发者唐春洋(tangcy21@mails.tsinghua.edu.cn)声明放弃对修改部分的任何版权诉求，任何使用者可做出任何修改、用于任何目的
    本代码遵守 CC 4.0 BY-SA 版权协议
    CC BY-SA 4.0 是一种许可协议，赋予遵守者两项重要权利：
    一、共享的权利。允许通过任何媒介和任何形式复制、发行作品。
    二、改编的权利。允许二次加工、转换和基于作品进行创作，不限制用途，甚至是商业应用。
【更改记录】
    2022-06-29 由唐春洋创建
    2022-07-20 由唐春洋增加注释
*************************************************************************/

#ifndef DateTime_hpp
#define DateTime_hpp

#include "Date.hpp"
#include "Time.hpp"
#include <sstream>
#include <string>

/*************************************************************************
【类名】DateTime
【功能】日期时间类，用于构造、储存、操作、输出一个日期时间
【接口说明】
    构造函数：DateTime(unsigned int Year, unsigned int Month, unsigned int Day,
unsigned int Hour, unsigned int Minute, unsigned int
Second)用单独的6个数字构造一个日期时间
    构造函数：DateTime(std::string str)用一个字符串构造一个日期时间
    拷贝构造函数：DateTime(const DateTime&
src)拷贝构造DateTime对象
    单独设置时间Time::Set
    年月日时分秒设置时间日期 Set(unsigned int Year, unsigned int Month, unsigned
int Day, unsigned int Hour, unsigned int Minute, unsigned int Second)
    年月日设置日期 SetDate(unsigned int Year, unsigned int Month, unsigned int
Day)
    时分秒设置时间 SetTime(unsigned int Hour, unsigned int Minute, unsigned int
Second)
    日期类对象设置日期 SetDate(const Date& date)
    时间类对象设置时间 SetTime(const Time& time)
    设置日期时间的字符串样式 SetFormat(boolis_regular_format)
    判断一个日期时间是否合法 IsValidDateTime(unsigned int Year, unsigned int
Month, unsigned int Day, unsigned int Hour, unsigned int Minute, unsigned int
Second)
    判断一个日期时间对象是否合法 IsValidDateTime(const DateTime& dateTime)
    判断自身是否合法 IsValid() const
    获取时间日期字符串 GetFormatString() const
    =运算符重载 operator=(const DateTime& src)
    >=运算符重载 operator>=(const DateTime& src) const
    日期时间的时分秒引用 const unsigned Hour, Minute, Second
    日期类的对象 m_Date
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2022-07-20 由唐春洋增加注释，并完善了功能
*************************************************************************/
class DateTime : public Time {
public:
    // 用单独的6个数字构造一个日期时间
    DateTime(unsigned int Year = 1900, unsigned int Month = 1,
             unsigned int Day = 1, unsigned int Hour = 0,
             unsigned int Minute = 0, unsigned int Second = 0);
    // 从一个长字符串构造日期时间
    DateTime(std::string str);
    // 拷贝构造函数
    DateTime(const DateTime& src);

    // 声明使用基类的Set函数
    using Time::Set;
    // 年月日时分秒设置时间日期
    bool Set(unsigned int Year, unsigned int Month, unsigned int Day,
             unsigned int Hour, unsigned int Minute, unsigned int Second);
    // 用年月日设置日期
    bool SetDate(unsigned int Year, unsigned int Month, unsigned int Day);
    // 用时分秒设置时间
    bool SetTime(unsigned int Hour, unsigned int Minute, unsigned int Second);
    // 日期类对象设置日期
    void SetDate(const Date& date);
    // 时间类对象设置时间
    void SetTime(const Time& time);
    // 设置日期时间的字符串表示
    static void SetFormat(bool is_regular_format = true);

    // 判断一个日期时间是否合法
    static bool IsValidDateTime(unsigned int Year, unsigned int Month,
                                unsigned int Day, unsigned int Hour,
                                unsigned int Minute, unsigned int Second);
    // 判断一个日期时间对象是否合法
    static bool IsValidDateTime(const DateTime& dateTime);
    // 判断自身是否合法
    bool IsValid() const;

    // 获取时间日期字符串
    std::string GetFormatString() const;

    // =运算符重载，返回自身的引用
    DateTime& operator=(const DateTime& src);
    // >=运算符重载，返回布尔值
    bool operator>=(const DateTime& src) const;

    // 只读访问器，日期时间的时分秒
    const unsigned int& Hour;
    const unsigned int& Minute;
    const unsigned int& Second;

    // 一个日期对象
    // 由于Date本身已经对权限进行了控制，本变量也被设为公有类型
    Date m_Date;
};

#endif /* DateTime_hpp */