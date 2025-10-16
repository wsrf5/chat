#pragma once 
#include "user.hpp"
#include <vector>


class FriendModel
{
public:
    // 添加好友关系
    void insert(int userid, int friendid);

    // 返回用户好友列表
    std::vector<User> query(int userid);
};