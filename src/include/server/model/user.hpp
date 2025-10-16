#pragma once
#include <string>
class User
{
public:
    User(int id = -1, std::string name = "", std::string pwd = "", std::string state = "offline"):
        id_(id), name_(name), password_(pwd), state_(state) {}
    void set_id(int id) { id_ = id; }
    void set_name(std::string name) { name_ = name; }
    void set_pwd(std::string pwd) { password_ = pwd; }
    void set_state(std::string state) { state_ = state; }

    int get_id() { return id_; }
    std::string get_name() { return name_; }
    std::string get_pwd() { return password_; }
    std::string get_state() { return state_; }
private:
    int id_;
    std::string name_;
    std::string password_;
    std::string state_;
};