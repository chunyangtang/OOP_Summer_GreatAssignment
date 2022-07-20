/*************************************************************************
【文件名】main.hpp
【功能模块和目的】命令行窗口运行的主函数
【开发者及日期】唐春洋(tangcy21@mails.tsinghua.edu.cn) 2022-7-20
【版权信息】以下代码由唐春洋根据清华大学自动化系2022年暑期“面向对象程序设计训练”课程要求独立编写，
    开发者唐春洋(tangcy21@mails.tsinghua.edu.cn)声明放弃对修改部分的任何版权诉求，任何使用者可做出任何修改、用于任何目的
    本代码遵守 CC 4.0 BY-SA 版权协议
    CC BY-SA 4.0 是一种许可协议，赋予遵守者两项重要权利：
    一、共享的权利。允许通过任何媒介和任何形式复制、发行作品。
    二、改编的权利。允许二次加工、转换和基于作品进行创作，不限制用途，甚至是商业应用。
【更改记录】
    2022-07-20 由唐春洋创建该文件
*************************************************************************/

#include "../../controllers/Controller.hpp"
#include <iostream>

int main(int argc, const char* argv[]) {
    // 程序开始提示
    std::cout << "Welcome to TCY's Covid Nucleic Acid Test MIS!" << std::endl
              << std::endl;
    // 读取数据文件
    FILE* UserFile;
    FILE* TubeFile;
    std::cout << "Initializing..." << std::endl;
    // 如果传入过多参数则提示错误
    if (argc > 3) {
        std::cout << "Invalid arguments, use \"-h\" or \"--help\" to see usage."
                  << std::endl;
        return 0;
    }
    // 如果传入一个参数
    if (argc == 2) {
        // 如果传入-h或--help参数
        if (argv[1] == "-h" || argv[1] == "--help") {
            std::cout << "Usage: " << argv[0] << " [UserFile] [TubeFile]"
                      << std::endl;
            std::cout << "UserFile: the file path of user data." << std::endl;
            std::cout << "TubeFile: the file path of tube data." << std::endl;
            std::cout << "Pass no argument to use the default files in the "
                         "data folder."
                      << std::endl;
            return 0;
        }
        // 如果传入其他参数则提示错误
        else {
            std::cout << "Invalid arguments, use \"-h\" or \"--help\" to see "
                         "usage."
                      << std::endl;
            return 0;
        }
    }
    // 如果传入两个参数
    if (argc == 3) {

    }
    // 如果未传入参数
    else{

    }
}