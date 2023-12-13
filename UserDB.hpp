#pragma once
#include <string>
#include <iostream>
#include <pqxx/pqxx>

class UserDB final
{
    public:
    static UserDB& getInstance();
    bool checkUser(const std::string& username, const std::string& password);
    private:
        UserDB() = default;
        UserDB(const UserDB&) = delete;
        UserDB(UserDB&&) = delete;
        UserDB& operator=(const UserDB&) = delete;
        UserDB& operator=(UserDB&&) = delete;

};