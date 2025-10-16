#include "usermodel.hpp"
#include "db.h"
#include <iostream>



bool UserModel::insert(User &user)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into user(name, password, state) values('%s', '%s', '%s')",
            user.get_name().c_str(), user.get_pwd().c_str(), user.get_state().c_str());

    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            // 获取插入成功的用户数据生成的主键id
            user.set_id(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }

    return false;
}


User UserModel::query(int id)
{
    char sql[1024] = {0};
    sprintf(sql, "select * from user where id = %d", id);

    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                User user;
                user.set_id(atoi(row[0]));
                user.set_name(row[1]);
                user.set_pwd(row[2]);
                user.set_state(row[3]);
                mysql_free_result(res);
                return user;
            }
        }
    }

    return User();
}

bool UserModel::updateState(User user)
{

    char sql[1024] = {0};
    sprintf(sql, "update user set state = '%s' where id = %d", user.get_state().c_str(), user.get_id());

    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            return true;
        }
    }
    return false;
}


void UserModel::resetState()
{

    char sql[1024] = "update user set state = 'offline' where state = 'online'";

    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}