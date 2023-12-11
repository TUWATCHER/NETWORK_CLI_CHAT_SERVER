#pragma once

#include <vector>
#include <map>
#include "User.h"

using std::string, std::vector;

bool RegisterUser(const string& _username, const string& _password, std::vector<User>& _UserDB);
void UserParser(const char request[], string& _username, string& _password);
const bool FindUser(const string& _username, const vector<User>& _UserDB);
User* GetUser(const string& _username, vector<User>& _UserDB);
bool LoginUser(const string& _username, const string& _password, vector<User>& _UserDB); 


const bool FindUser(const string& _username, const vector<User>& _UserDB)
{
    if (std::find(_UserDB.begin(), _UserDB.end(), User(_username)) != _UserDB.end())
    {
        return true;
    }
    else
    {
        return false;
    }

}

User* GetUser(const string& _username, vector<User>& _UserDB)
{
    if (FindUser(_username, _UserDB))
    {
        auto search_index = std::find(_UserDB.begin(), _UserDB.end(), User(_username));
        return &(_UserDB[search_index - _UserDB.begin()]);
    }
    {
        std::cout << "User not exist!\n";
        return nullptr;
    }

}

bool LoginUser(const string& _username, const string& _password, vector<User> &_UserDB)
{
    if (FindUser(_username, _UserDB))
    {
        auto search_index = std::find(_UserDB.begin(), _UserDB.end(), User(_username));
        if(search_index->CheckUser(_username, _password))
        {
            std::cout << "Login has been successfull!\n";
            GetUser(_username, _UserDB)->SetToken(reinterpret_cast<uint64_t>(GetUser(_username, _UserDB)));
            GetUser(_username, _UserDB)->SetStatus(true);
            std::cout << "User security token: " << GetUser(_username, _UserDB)->GetToken() << std::endl;     
            return true;
        }
        else
        {
            std::cout << "Wrong password!\n";
            return false;
        }
        
    }
    else
    {
        std::cout << "User does not exist!\n";
        return false;
    }
}

bool RegisterUser(const string& _username, const string& _password, std::vector<User>& _UserDB)
{
    if (FindUser(_username, _UserDB))
    {
        std::cout << "This user already exists!\n";
        return false;
    }
    else
    {
        std::cout << "User has been created!\n";
        _UserDB.push_back(User(_username, _password));
        return true;
    }
}

void UserParser(const char request[], string& _username, string& _password)
{    
    std::string UID = request;
    UID.erase(0, 9);     
    _username = UID.substr(0, UID.find("#UIDE#"));
    
    UID.erase(0, UID.find("#PWDB#") + 6);        
    _password = UID.substr(0, UID.find("#PWDE#"));
}