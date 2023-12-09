#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "User.h"

using std::string;
using std::vector;
static int _ID = 0;

class Chat
{
public:
    Chat() = default;
    Chat(User* fromUser, User* toUser, string message);
    Chat(User* fromUser, vector<User> toUsers, string message);
    User& GetFromUser();
    User& GetToUser();
    bool HasRecipient(string username);
    void ShowMessages();
    void AddMessage(string message);

private:
    User _fromUser;
    User _toUser;
    vector<User> _toUsers;
    vector<string> _message;
};