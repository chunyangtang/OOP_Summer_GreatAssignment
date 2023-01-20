# OOP_Summer_GreatAssignment

TCY 2022年夏季学期 OOP 课程大作业 —— 核酸检测系统
这个仓库中包含全部源码、测试数据和其他的介绍类文件。

## Coding Environment

| Function |               Name                |
| :------: | :-------------------------------: |
|  Editor  | Visual Studio Code Version 1.68.1 |
| Compiler |         gcc version 9.4.0         |
|    OS    |    Ubuntu 20.04 LTS (Over WSL)    |

## Compile Command

```bash
g++ -o main interfaces/Commandline/main.cpp controllers/ControllerBase.cpp controllers/ControllerCommandline.cpp models/Date.cpp models/DateTime.cpp models/MD5.cpp models/Time.cpp models/tinyxml2.cpp models/Tube.cpp models/User.cpp
```

**主程序的结构示意如图：structure_main.vsdx**
**其中 main.exe 在 Windows 下编译得到，main 在 Linux 下编译得到**
**已预先创建的 user.xml 中三个用户的密码均为 123**

## 项目中运用的第三方代码

1. MD5.hpp, MD5.cpp \
   来源：范老师提供的代码 \
   说明：按找老师要求，没有进行修改
2. tinyxml2.h, tinyxml2.cpp \
   来源：https://github.com/leethomason/tinyxml2 \
   说明：作者已在文件开头加入了版权声明，因此未对这两个文件进行任何改动。

## 项目各类功能介绍

1. 时间日期的储存： \
   时间日期运用了课堂中小作业的 Date、Time 与继承自 Time 类的 DateTime 类。 \
   其中 Date 类重载了各类运算符，功能很完善，其余二者满足了本大作业中其他类的基本要求。

2. 用户数据与操作的实现： \
   User 类存储用户姓名、ID、密码（MD5 加密）、上次测试时间与结果、全部用户的指针 vector \
   其通过内嵌类的方式实现了权限的管理，具备文件存取功能。

3. 试管数据的存储：\
   Tube 类存储试管的编号、受检用户的指针与检测时间、检测结果、全部试管的指针 vector \
   对其的操作与管理主要由特殊身份的用户来完成，具备文件存取功能。

4. 操作流程的实现： \
   ControllerBase 类实现了用户注册、登录的功能 \
   ControllerCommandline 作为命令行接口含有用户查询自身权限、检测结果的功能。 \
   流程的实现与内部的 Tube、User 类耦合度很低，如需修改不易互相干扰。

## 项目在一些功能上的考量

1. User 内嵌类设计的目的？\
   希望通过内嵌类的方式实现：对于每个 User，不具有的权限完全不存在相应实现的函数。 \
   为了实现这样的目的，我将这些内嵌类的构造函数定义为私有防止被外部调用。 \
   这样，这些内嵌类与指针就可以设为 public，方便其他位置的调用。（也因此，这些类中不含静态成员防止被外部调用）

2. 控制器类为什么只定义了各函数而没有整个流程？\
   这样定义的原因是在最终的用户输入界面除了各种操作外还需要各种提示输出，这些输出要在主函数中体现，因此控制器类只定义了核心的操作而没办法定义许多完整的操作。
