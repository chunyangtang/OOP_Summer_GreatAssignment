

#include "../models/Tube.hpp"
#include "../models/User.hpp"
#include "../models/tinyxml2.h"
#include <memory>
#include <string>
#include <vector>

using namespace tinyxml2;

// 定义用户智能指针的别名
using pUser = std::shared_ptr<User>;

// 定义试管智能指针的别名
using pTube = std::shared_ptr<Tube>;

class Controller {
public:
private:
    // 存储所有试管的容器
    std::vector<pTube> m_AllTubes;
    // 存储所有用户的容器
    std::vector<pUser> m_AllUsers;
};