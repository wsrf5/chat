#pragma once
#include "user.hpp"

//继承自user,多了role职责
class GroupUser : public User
{
public:
    void setRole(std::string role) { this->role = role; }
    std::string getRole() { return this->role; }

private:
    std::string role;
};