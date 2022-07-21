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

#include "../../controllers/ControllerCommandline.hpp"
#include <iostream>

int main(int argc, const char* argv[]) {
    // 程序开始提示
    std::cout << "Welcome to TCY's Covid Nucleic Acid Test MIS!" << std::endl
              << std::endl;
    // 读取数据文件
    const char* UserFilename;
    const char* TubeFilename;
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
        UserFilename = argv[1];
        TubeFilename = argv[2];
    }
    // 如果未传入参数
    else {
        UserFilename = "data/user.xml";
        TubeFilename = "data/tube.xml";
    }

    // 初始化控制器
    ControllerCommandline controller;

    // 解析数据文件，读入到类的对象中
    std::cout << "Parsing data files..." << std::endl;
    // TODO
    // 登陆界面
    while (true) {
        int i = 0;
        std::cout << controller.ShowAvailableOperations();
        std::cin >> i;
        if (i == 3) {
            // 退出程序
            break;
        } else if (i == 2) {
            // 注册流程
            std::string name;
            std::string id;
            std::string password;

            std ::cout << "To create an account, we need your name, ID and a "
                          "password. \n Please input your "
                          "FULL name: ";
            std::cin >> name;
            while (true) {
                std::cout << "Please input your ID: ";

                std::cin >> id;
                if (id.length() != 18) {
                    std::cout << "Invalid ID, please input again." << std::endl;
                } else {
                    break;
                }
            }
            while (true) {
                std::cout << "Please input your password: ";
                std::cin >> password;
                std::string confirm_pw;
                std::cout << "Confirm your password: ";
                std::cin >> confirm_pw;
                if (password != confirm_pw) {
                    std::cout << "Password not match, please input again."
                              << std::endl;
                } else {
                    break;
                }
            }
            if (controller.Register(id, name, password) == nullptr) {
                std::cout << "Your ID has been registered before, try to login?"
                          << std::endl;
            } else {
                std::cout << "Register success." << std::endl;
            }

        } else if (i == 1) {
            // 登陆流程
            std::string id;
            std::string password;
            std::cout << "Please input your ID: ";
            std::cin >> id;
            std::cout << "Please input your password: ";
            std::cin >> password;
            pUser current_user = controller.Login(id, password);
            if (current_user == nullptr) {
                std::cout << "Login failed, please try again." << std::endl;
                continue;
            } else {
                // 登陆后选择身份
                std::cout << "Login success." << std::endl;

                while (true) {
                    std::cout
                        << controller.ShowAvailableOperations(current_user);
                    int j = 0;
                    std::cin >> j;
                    // 选择对应身份的功能
                    if (j == 1) {
                        std::cout << "Available Operations:" << std::endl;
                        std::cout << "   1. Check Latest Test Result"
                                  << std::endl;
                        std::cout << "   2. Change Password" << std::endl;
                        std::cout << "   3. Logout" << std::endl;
                        std::cout << "Please input an integer: " << std::endl;
                    } else if (j == 2) {
                        if (current_user->m_Admin == nullptr) {
                            std::cout
                                << "Access denied, you are not an administrator"
                                << std::endl;
                            continue;
                        }
                        std::cout << "Available Operations:" << std::endl;
                        std::cout << "   1. Reset Password for a User"
                                  << std::endl;
                        std::cout << "   2. Delete a User" << std::endl;
                        std::cout << "   3. Add Role for a User" << std::endl;
                        std::cout << "   4. Delete Role for a User"
                                  << std::endl;
                        std::cout << "   5. Logout" << std::endl;
                        std::cout << "Please input an integer: " << std::endl;
                    } else if (j == 3) {
                        if (current_user->m_Collector == nullptr) {
                            std::cout
                                << "Access denied, you are not a collector"
                                << std::endl;
                            continue;
                        }
                        std::cout << "Available Operations:" << std::endl;
                        std::cout << "   1. Create a Tube" << std::endl;
                        std::cout << "   2. Collect Users of a Tube"
                                  << std::endl;
                        std::cout << "   3. Logout" << std::endl;
                        std::cout << "Please input an integer: " << std::endl;
                    } else if (j == 4) {
                        if (current_user->m_Recorder == nullptr) {
                            std::cout << "Access denied, you are not a recorder"
                                      << std::endl;
                            continue;
                        }
                        std::cout << "Available Operations:" << std::endl;
                        std::cout << "   1. Record Result for a Tube"
                                  << std::endl;
                        std::cout << "   2. Logout" << std::endl;
                        std::cout << "Please input an integer: " << std::endl;
                    } else {
                        std::cout << "Invalid input, please input again:"
                                  << std::endl;
                        continue;
                    }
                }
            }
        }
    }
    // 程序退出前将数据写入文件
    std::cout << "Writing to data files..." << std::endl;
    // TODO
    return 0;
}
