#pragma once
#include <string>
#include <iostream>
#include <pqxx/pqxx>

class UserDB final
{
    public:
    static UserDB& getInstance();
    bool loginUser(const std::string& username, const std::string& password);
    bool registerUser(const std::string& username, const std::string& password);
    bool deleteUser(const std::string& username);
    private:
        UserDB() = default;
        UserDB(const UserDB&) = delete;
        UserDB(UserDB&&) = delete;
        UserDB& operator=(const UserDB&) = delete;
        UserDB& operator=(UserDB&&) = delete;

};