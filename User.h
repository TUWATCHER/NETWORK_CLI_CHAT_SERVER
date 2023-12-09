#pragma once
#include <string>

using std::string;

class User
{
    public:
        User() = default;
        User(string username);
        User(string user, string pass);
        User(string user, string pass, string name);
        User(const User& user);
        ~User() = default;
        string GetUserName();
        string GetName();
        void SetUserName(const string username);
        void SetName(const string name);
        void SetStatus(const bool status);
        void SetToken(const uint32_t token);
        const uint32_t GetToken() const;
        const string GetPassword() const;
        const bool GetStatus() const;
        void SetPassword(const string password);
        bool CheckUser(string username, string password);
        bool operator==(const User& user) const;
        User& operator=(const User& user);
        friend std::ostream& operator<<(std::ostream& os, const User& user);
        
    private:
        string _username;
        string _name;
        string _password;
        uint32_t _token;
        bool hasLoggedIn;
};