/*************************************************************************
【文件名】main.cpp
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

// 定义用户智能指针的别名
class User;
using pUser = std::shared_ptr<User>;
// 声明TestResult枚举类
enum class TestResult;

int main(int argc, const char* argv[]) {
    // 程序开始提示
    std::cout << "Welcome to TCY's Covid Nucleic Acid Test MIS!" << std::endl
              << std::endl;
    // 读取数据文件
    const char* UserFilename;
    const char* TubeFilename;
    std::cout << "---------------------------------------" << std::endl;
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
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Parsing data files..." << std::endl;
    if (controller.ParseUserFile(UserFilename)) {
        std::cout << "----Parsing user data files successfully!" << std::endl;
    } else {
        std::cout << "----Parsing user data files failed! \n----There maybe "
                     "errors in "
                     "your "
                     "file path, or no default file found.\n----The program "
                     "will still run "
                     "as an empty system. Make sure the path is available for "
                     "file saving!"
                  << std::endl;
    }

    if (controller.ParseTubeFile(TubeFilename)) {
        std::cout << "------Parsing tube data files successfully!" << std::endl;
    } else {
        std::cout
            << "------Parsing tube data files failed! \n------There maybe "
               "errors in "
               "your "
               "file path, or no default file found.\n------The program "
               "will still run "
               "as an empty system. Make sure the path is available for "
               "file saving!"
            << std::endl;
    }
    // 登陆界面
    while (true) {
        int i = 0;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "Available Operations:" << std::endl;
        std::cout << "   1. Login" << std::endl;
        std::cout << "   2. Register" << std::endl;
        std::cout << "   3. Quit" << std::endl;
        std::cout << "Please input an integer: ";
        fflush(stdin);
        std::cin >> i;
        fflush(stdin);
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
                    id.clear();
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
                    password.clear();
                } else {
                    break;
                }
            }
            if (controller.Register(id, name, password) == nullptr) {
                std::cout << "Your ID has been registered before, try to login?"
                          << std::endl;
                name.clear();
                id.clear();
                password.clear();
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
                id.clear();
                password.clear();
                continue;
            } else {
                // 登陆后选择身份
                std::cout << "Login success." << std::endl;
                std::cout << controller.ShowUserAuth(current_user);
                std::tuple<bool, bool, bool> authTuple =
                    current_user->GetStatus();
                while (true) {
                    std::cout << "---------------------------------------"
                              << std::endl;
                    std::cout << "Available Operations:" << std::endl;
                    std::cout << "   1. Login as a regular user" << std::endl;
                    if (std::get<0>(authTuple)) {
                        std::cout << "   2. Login as an administrator"
                                  << std::endl;
                    }
                    if (std::get<1>(authTuple)) {
                        std::cout << "   3. Login as a collector" << std::endl;
                    }
                    if (std::get<2>(authTuple)) {
                        std::cout << "   4. Login as a recorder" << std::endl;
                    }
                    std::cout << "   5. Logout" << std::endl;
                    std::cout << "Please input an integer: ";

                    int j = 0;
                    std::cin >> j;
                    // 选择对应身份的功能
                    if (j == 1) {
                        // 作为被试者的功能
                        while (true) {
                            std::cout
                                << "---------------------------------------"
                                << std::endl;
                            std::cout << "Available Operations:" << std::endl;
                            std::cout << "   1. Check Latest Test Result"
                                      << std::endl;
                            std::cout << "   2. Change Password" << std::endl;
                            std::cout << "   3. Return to the previous level"
                                      << std::endl;
                            std::cout << "Please input an integer: ";
                            int k = 0;
                            std::cin >> k;
                            if (k == 1) {
                                // 查询最新的测试结果
                                std::cout
                                    << controller.ShowUserResult(current_user);
                                continue;
                            } else if (k == 2) {
                                // 修改密码
                                std::string new_pw;
                                std::string confirm_pw;
                                while (true) {
                                    std::cout
                                        << "Please input your new password: ";
                                    std::cin >> new_pw;
                                    std::cout << "Confirm your new password: ";
                                    std::cin >> confirm_pw;
                                    if (new_pw != confirm_pw) {
                                        std::cout << "Password not match, "
                                                     "please input again:";
                                    } else {
                                        break;
                                    }
                                }
                                if (current_user->ResetPassword(password,
                                                                new_pw)) {
                                    std::cout
                                        << "Password changed successfully."
                                        << std::endl;
                                } else {
                                    std::cout
                                        << "Failed to change your password."
                                        << std::endl;
                                }
                            } else if (k == 3) {
                                // 返回上一级
                                break;
                            } else {
                                std::cout
                                    << "Invalid input, please input again."
                                    << std::endl;
                                continue;
                            }
                        }

                    } else if (j == 2) {
                        // 作为管理员的功能
                        if (current_user->m_pAdmin == nullptr) {
                            std::cout
                                << "---------------------------------------"
                                << std::endl;
                            std::cout << "Access denied, you are not an "
                                         "administrator. Try again:";
                            continue;
                        }
                        while (true) {
                            std::cout
                                << "---------------------------------------"
                                << std::endl;
                            std::cout << "Available Operations:" << std::endl;
                            std::cout << "   1. Reset Password for a User"
                                      << std::endl;
                            std::cout << "   2. Delete a User" << std::endl;
                            std::cout << "   3. Add Role for a User"
                                      << std::endl;
                            std::cout << "   4. Delete Role for a User"
                                      << std::endl;
                            std::cout << "   5. Return to the previous level"
                                      << std::endl;
                            std::cout << "Please input an integer: ";
                            int k = 0;
                            std::cin >> k;
                            if (k == 1) {
                                // 为用户重置密码
                                //首先获取用户的ID
                                std::string id;
                                while (true) {
                                    std::cout << "Please input the ID of the "
                                                 "user: ";

                                    std::cin >> id;
                                    if (!User::HaveUser(id)) {
                                        std::cout << "User not found, "
                                                     "please input again:";
                                    } else {
                                        break;
                                    }
                                }
                                // 获取用户的新密码
                                std::string new_pw;
                                std::string confirm_pw;
                                while (true) {
                                    std::cout
                                        << "Please input the new password: ";
                                    std::cin >> new_pw;
                                    std::cout << "Confirm the new password: ";
                                    std::cin >> confirm_pw;
                                    if (new_pw != confirm_pw) {
                                        std::cout << "Password not match, "
                                                     "please input again:";
                                    } else {
                                        break;
                                    }
                                }
                                if (current_user->m_pAdmin->ResetPassword(
                                        id, new_pw)) {
                                    std::cout
                                        << "Password changed successfully."
                                        << std::endl;
                                } else {
                                    std::cout
                                        << "Failed to change your password."
                                        << std::endl;
                                }
                                continue;
                            } else if (k == 2) {
                                // 删除用户
                                // 获取用户的ID
                                std::string id;
                                while (true) {
                                    std::cout << "Please input the ID of the "
                                                 "user: ";

                                    std::cin >> id;
                                    if (!User::HaveUser(id)) {
                                        std::cout << "User not found, "
                                                     "please input again:";
                                    } else {
                                        break;
                                    }
                                }
                                current_user->m_pAdmin->DeleteUser(id);
                            } else if (k == 3) {
                                std::string id;
                                std::string role;
                                //首先获取用户的ID
                                while (true) {
                                    std::cout << "Please input the ID of the "
                                                 "user: ";

                                    std::cin >> id;
                                    if (!User::HaveUser(id)) {
                                        std::cout << "User not found, "
                                                     "please input again:";
                                    } else {
                                        break;
                                    }
                                }
                                // 获取角色
                                while (true) {
                                    std::cout << "Please enter a role "
                                                 "(admin/collector/recorder): "
                                              << std::endl;
                                    std::cin >> role;
                                    if (current_user->m_pAdmin->AddRole(id,
                                                                        role)) {
                                        std::cout << "Role added successfully. "
                                                     "\nRelogin to take effect "
                                                     "if you're "
                                                     "adding roles to yourself."
                                                  << std::endl;
                                        break;
                                    } else {
                                        std::cout
                                            << "Invalid Role input, try again."
                                            << std::endl;
                                        continue;
                                    }
                                }

                            } else if (k == 4) {
                                std::string id;
                                std::string role;
                                //首先获取用户的ID
                                while (true) {
                                    std::cout << "Please input the ID of the "
                                                 "user: ";

                                    std::cin >> id;
                                    if (!User::HaveUser(id)) {
                                        std::cout << "User not found, "
                                                     "please input again:";
                                    } else {
                                        break;
                                    }
                                }
                                // 获取角色
                                while (true) {
                                    std::cout << "Please enter a role "
                                                 "(admin/collector/recorder): "
                                              << std::endl;
                                    std::cin >> role;
                                    if (current_user->m_pAdmin->DeleteRole(
                                            id, role)) {
                                        std::cout
                                            << "Role removed "
                                               "successfully. \nRelogin to "
                                               "take effect if you're "
                                               "adding roles to yourself."
                                            << std::endl;
                                        break;
                                    } else {
                                        std::cout
                                            << "Invalid Role input, try again."
                                            << std::endl;
                                        continue;
                                    }
                                }

                            } else if (k == 5) {
                                // 返回上一级
                                break;
                            } else {
                                std::cout
                                    << "Invalid input, please input again."
                                    << std::endl;
                                continue;
                            }
                        }

                    } else if (j == 3) {
                        std::string SerialNumber;
                        // 作为采集员的功能
                        if (current_user->m_pCollector == nullptr) {
                            std::cout << "Access denied, you are not a "
                                         "collector. Try again:"
                                      << std::endl;
                            continue;
                        }
                        while (true) {
                            std::cout
                                << "---------------------------------------"
                                << std::endl;
                            std::cout << "Available Operations:" << std::endl;
                            std::cout << "   1. Create a Tube" << std::endl;
                            std::cout << "   2. Collect Users of a Tube"
                                      << std::endl;
                            std::cout << "   3. Return to the previous level"
                                      << std::endl;
                            std::cout << "Please input an integer: ";
                            int k = 0;
                            std::cin >> k;
                            if (k == 1) {
                                //首先获取试管序列号
                                while (true) {
                                    std::cout
                                        << "Please input SerialNumber of the "
                                           "tube: ";

                                    std::cin >> SerialNumber;
                                    if (SerialNumber.size() != 20) {
                                        std::cout << "Invalid Serial number, "
                                                     "enter another one:";
                                    } else {
                                        break;
                                    }
                                }
                                // 创建试管
                                current_user->m_pCollector->CreateTube(
                                    SerialNumber);
                                std::cout << "Tube created successfully."
                                          << std::endl;
                            } else if (k == 2) {
                                std::string o_SerialNumber;
                                pTube tube;
                                // 检查内存中是否有可以直接使用的试管编号
                                if (!SerialNumber.empty()) {
                                    std::cout
                                        << "Last tube is still in memory, "
                                           "use it to collect users?(y/n)";
                                    while (true) {
                                        char yorn;
                                        std::cin >> yorn;
                                        if (yorn == 'n') {
                                            //获取试管序列号
                                            while (true) {
                                                std::cout
                                                    << "Please input "
                                                       "SerialNumber of the "
                                                       "tube: ";

                                                std::cin >> o_SerialNumber;
                                                if (current_user->m_pCollector
                                                        ->FindTube(
                                                            o_SerialNumber) ==
                                                    nullptr) {
                                                    std::cout
                                                        << "Serial "
                                                           "number not found, "
                                                           "enter another one:";
                                                } else {
                                                    break;
                                                }
                                            }
                                            break;
                                        } else if (yorn == 'y') {
                                            o_SerialNumber = SerialNumber;
                                            break;
                                        } else {
                                            std::cout << "Invalid input, "
                                                         "try again:";
                                            continue;
                                        }
                                    }
                                } else {
                                    //获取试管序列号
                                    while (true) {
                                        std::cout << "Please input "
                                                     "SerialNumber of the "
                                                     "tube: ";

                                        std::cin >> o_SerialNumber;
                                        if (current_user->m_pCollector
                                                ->FindTube(o_SerialNumber) ==
                                            nullptr) {
                                            std::cout << "Serial "
                                                         "number not found, "
                                                         "enter another one:";
                                        } else {
                                            break;
                                        }
                                    }
                                }
                                SerialNumber = o_SerialNumber;
                                tube = current_user->m_pCollector->FindTube(
                                    o_SerialNumber);
                                std::cout << "Tube found successfully."
                                          << std::endl;
                                // 时间日期录入
                                int year, month, day, hour, minute, second;
                                std::cout << "Please input time (YYYY MM DD hh "
                                             "mm ss): ";
                                std::cin >> year >> month >> day >> hour >>
                                    minute >> second;
                                DateTime dateTime(year, month, day, hour,
                                                  minute, second);
                                // 获取用户ID
                                std::string id;
                                while (true) {
                                    std::cout << "Please input the ID of the "
                                                 "user: ";

                                    std::cin >> id;
                                    if (!User::HaveUser(id)) {
                                        std::cout << "User not found, "
                                                     "please input again:";
                                    } else {
                                        break;
                                    }
                                }
                                // 信息录入
                                if (current_user->m_pCollector->CollectUsers(
                                        tube, id, dateTime)) {
                                    std::cout << "User collected successfully."
                                              << std::endl;
                                } else {
                                    std::cout << "User collected failed."
                                              << std::endl;
                                }
                            } else if (k == 3) {
                                break;
                            } else {
                                std::cout
                                    << "Invalid input, please input again."
                                    << std::endl;
                                continue;
                            }
                        }
                    } else if (j == 4) {
                        if (current_user->m_pRecorder == nullptr) {
                            std::cout << "Access denied, you are not a "
                                         "recorder. Try again:"
                                      << std::endl;
                            continue;
                        }
                        while (true) {
                            std::cout
                                << "---------------------------------------"
                                << std::endl;
                            std::cout << "Available Operations:" << std::endl;
                            std::cout << "   1. Record Result for a Tube"
                                      << std::endl;
                            std::cout << "   2. Return to the previous level"
                                      << std::endl;
                            std::cout << "Please input an integer: ";
                            int k = 0;
                            std::cin >> k;
                            if (k == 1) {
                                std::string SerialNumber;
                                TestResult result;
                                // 获取试管序列号
                                while (true) {
                                    std::cout
                                        << "Please input SerialNumber of the "
                                           "tube: ";

                                    std::cin >> SerialNumber;
                                    if (SerialNumber.size() != 20) {
                                        std::cout << "Invalid Serial number, "
                                                     "enter another one:";
                                    } else {
                                        break;
                                    }
                                }
                                // 获取试管状态

                                while (true) {
                                    int res_int;
                                    std::cout
                                        << "Please input test result of the "
                                           "tube (0.Negative / 1.Positive): ";
                                    std::cin >> res_int;
                                    if (res_int != 0 && res_int != 1) {
                                        std::cout << "Invalid input, "
                                                     "please enter again:";
                                    } else {
                                        result = (res_int == 0)
                                                     ? TestResult::NEGATIVE
                                                     : TestResult::POSITIVE;
                                        break;
                                    }
                                }
                                // 录入试管状态
                                current_user->m_pRecorder->RecordTubeStatus(
                                    SerialNumber, result);
                                std::cout
                                    << "Test result recorded successfully."
                                    << std::endl;
                            } else if (k == 2) {
                                break;
                            } else {
                                std::cout
                                    << "Invalid input, please input again."
                                    << std::endl;
                                continue;
                            }
                        }
                    } else if (j == 5) {
                        break;
                    } else {
                        std::cout << "Invalid input, please input again:";
                        continue;
                    }
                }
            }
        } else {
            std::cout << "Invalid input, please input again:";
            i = 0;
            continue;
        }
    }
    // 程序退出前将数据写入文件
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Writing to data files..." << std::endl;
    if (!controller.SavetoUserFile(UserFilename)) {
        std::cout << "----User data saved successfully." << std::endl;
    } else {
        std::cout << "----User data saved failed." << std::endl;
    }
    if (!controller.SavetoTubeFile(TubeFilename)) {
        std::cout << "----Tube data saved successfully." << std::endl;
    } else {
        std::cout << "----Tube data saved failed." << std::endl;
    }
    return 0;
}
