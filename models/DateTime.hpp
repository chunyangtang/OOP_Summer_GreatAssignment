/*************************************************************************
【文件名】DateTime.hpp
【功能模块和目的】日期时间类声明
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

#ifndef DateTime_hpp
#define DateTime_hpp

#include "Date.hpp"
#include "Time.hpp"
#include <string>

/*************************************************************************
【类名】DateTime
【功能】日期时间类，用于构造、储存、操作、输出一个日期时间
【接口说明】
    构造函数：DateTime(unsigned int Year, unsigned int Month, unsigned int Day,
unsigned int Hour, unsigned int Minute, unsigned int
Second)用单独的6个数字构造一个日期时间 拷贝构造函数：DateTime(const DateTime&
src)拷贝构造DateTime对象 构造函数：DateTime(const Date& date, const Time&
time)构造一个日期时间，其中日期和时间分别由Date和Time类构造
    ......
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-20 由唐春洋增加注释，并完善了功能
*************************************************************************/
class DateTime : public Time {
public:
    // 用单独的6个数字构造一个日期时间
    DateTime(unsigned int Year = 1900, unsigned int Month = 1,
             unsigned int Day = 1, unsigned int Hour = 0,
             unsigned int Minute = 0, unsigned int Second = 0);
    // 拷贝构造函数
    DateTime(const DateTime& src);
    // 构造一个日期时间，其中日期和时间分别由Date和Time类构造
    // DateTime(const Date& date, const Time& time = Time());
    //
    using Time::Set;
    bool Set(unsigned int Year, unsigned int Month, unsigned int Day,
             unsigned int Hour, unsigned int Minute, unsigned int Second);
    bool SetDate(unsigned int Year, unsigned int Month, unsigned int Day);
    bool SetTime(unsigned int Hour, unsigned int Minute, unsigned int Second);
    void SetDate(const Date& date);
    void SetTime(const Time& time);
    static void SetFormat(bool is_regular_format = true);

    // Checkers
    static bool IsValidDateTime(unsigned int Year, unsigned int Month,
                                unsigned int Day, unsigned int Hour,
                                unsigned int Minute, unsigned int Second);
    static bool IsValidDateTime(const DateTime& dateTime);
    bool IsValid() const;

    // Getters
    std::string GetFormatString() const;

    // Operators
    DateTime& operator=(const DateTime& src);

    // Data references for read-only access
    const unsigned int& Hour;
    const unsigned int& Minute;
    const unsigned int& Second;

    // 一个日期对象
    // 由于Date本身已经对权限进行了控制，本变量也被设为公有类型
    Date m_Date;
};

#endif /* DateTime_hpp */