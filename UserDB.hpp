#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <pqxx/pqxx>

class UserDB final
{
    public:
    static UserDB& getInstance();
    bool loginUser(const std::string& username, const std::string& password);
    bool registerUser(const std::string& username, const std::string& password);
    bool deleteUser(const std::string& username);
    bool createMessage(const std::string& fromUser, const std::string& toUser, const std::string& message);
    std::vector<std::string> checkMessage(const std::string& username);
    private:
        UserDB() = default;
        UserDB(const UserDB&) = delete;
        UserDB(UserDB&&) = delete;
        UserDB& operator=(const UserDB&) = delete;
        UserDB& operator=(UserDB&&) = delete;

};