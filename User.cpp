#include <iostream>
#include "User.h"

User::User(string username) : _username(username){hasLoggedIn = false;}

User::User(string user, string pass) : _username(user), _password(pass) {hasLoggedIn = false;}

User::User(string user, string pass, string name) : _username(user), _password(pass), _name(name) {hasLoggedIn = false;}

User::User(const User &user) : _username(user._username), _password(user._password), _name(user._name) {hasLoggedIn = false;}


string User::GetUserName()
{
    return _username;
}

string User::GetName()
{
    return _name;
}

void User::SetUserName(const string username)
{
    _username = username;
}

void User::SetName(const string name)
{
    _name = name;
}

void User::SetStatus(const bool status)
{
    hasLoggedIn = status;
}

void User::SetToken(const uint32_t token)
{
    _token = token;
}

const uint32_t User::GetToken() const
{
    return _token;
}

const string User::GetPassword() const
{
    return _password;
}

const bool User::GetStatus() const
{
    return hasLoggedIn;
}

void User::SetPassword(const string password)
{
    _password = password;
}

bool User::CheckUser(string username, string password)
{
    if (this->_username == username && this->_password == password)
    {
        return true;
    }
    else
    {
        return false;
    }  
    
}

bool User::operator==(const User &user) const
{
    return (this->_username == user._username);
}

User &User::operator=(const User &user)
{
    if(&user == this)
        return *this;
          

    this->_username = user._username;
    this->_password = user._password;
    this->_name = user._name;
    
    return *this;
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
    return os << "Username: " << user._username << std::endl
                << "Name: " << user._name << std::endl;
}