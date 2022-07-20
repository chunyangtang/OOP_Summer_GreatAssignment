/*************************************************************************
【文件名】Time.hpp
【功能模块和目的】时间类声明
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【版权信息】以下代码由唐春洋根据清华大学自动化系2022年暑期“面向对象程序设计训练”课程要求独立编写，
    开发者唐春洋(tangcy21@mails.tsinghua.edu.cn)声明放弃对修改部分的任何版权诉求，任何使用者可做出任何修改、用于任何目的
    本代码遵守 CC 4.0 BY-SA 版权协议
    CC BY-SA 4.0 是一种许可协议，赋予遵守者两项重要权利：
    一、共享的权利。允许通过任何媒介和任何形式复制、发行作品。
    二、改编的权利。允许二次加工、转换和基于作品进行创作，不限制用途，甚至是商业应用。
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-20 由唐春洋增加注释，并完善了功能
*************************************************************************/

#ifndef Time_hpp
#define Time_hpp
#include <string>

/*************************************************************************
【类名】Time
【功能】时间类，用于构造、储存、操作、输出一个时间
【接口说明】
    构造函数：Date(int year, int month, int day)按日期构造Date对象
    拷贝构造函数：Date(const Date& date)拷贝构造Date对象
    ......
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-6-28
【更改记录】
    2022-6-29 由唐春洋完善了类中功能的代码实现
    2020-07-20 由唐春洋增加注释，并完善了功能
*************************************************************************/
class Time
{
public:
    // 用小时、分钟、秒构造Time对象
    Time(unsigned int Hour = 0, unsigned int Minute = 0, unsigned int Second = 0);
    // 拷贝构造Time对象
    Time(const Time &src);

    // 检查一个时分秒是否合法
    static bool IsValidTime(unsigned int Hour, unsigned int Minute, unsigned int Second);
    // 检查一个Time对象是否合法
    static bool IsValidTime(const Time &time);
    // 检查自身是否合法
    bool IsValid() const;

    // 整体设置时分秒
    bool Set(unsigned int Hour, unsigned int Miniute, unsigned int Second);
    // 单独设置小时
    bool SetHour(unsigned int Hour);
    // 单独设置分钟
    bool SetMinute(unsigned int Minute);
    // 单独设置秒
    bool SetSecond(unsigned int Second);
    // 设置输出字符串是否为24小时制
    static void Set24Hours(bool Is24Hours);
    // 设置输出字符串是否带冒号
    static void SetFormat(bool IsRegularFormat);    

    // 获取自0：0：0的总秒数
    unsigned int Seconds() const;
    // 获取格式化的时间字符串
    std::string GetFormatString() const;

    // Operators
    Time &operator=(const Time &src);

    // 用于外界访问的常量引用的小时
    const unsigned int &Hour;
    // 用于外界访问的常量引用的分钟
    const unsigned int &Minute;
    // 用于外界访问的常量引用的秒
    const unsigned int &Second;

private:
    // 无符号整数，表示小时
    unsigned int m_Hour;
    // 无符号整数，表示分钟
    unsigned int m_Minute;
    // 无符号整数，表示秒
    unsigned int m_Second;
    // 静态变量，表示是否为24小时制
    static bool Is24Hours;
    // 静态变量，表示是否为标准格式
    static bool regular_format;
};

#endif /* Time_hpp */
