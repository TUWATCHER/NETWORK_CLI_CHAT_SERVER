
#include "User.h"
#include <string>
#include <iostream>
#include <algorithm>
#include "Chat.h"

Chat::Chat(User* fromUser, User* toUser, string message)
{
    _fromUser = *fromUser;
    _toUser = *toUser;
    _message.push_back(_fromUser.GetUserName()+":\n"+message+'\n');
}
Chat::Chat(User* fromUser, vector<User> toUsers, string message)
{
    _fromUser = *fromUser;
    _toUsers = toUsers;
    _message.push_back(_fromUser.GetUserName()+":\n"+message+'\n');
}

User& Chat::GetFromUser()
{
    return _fromUser;
}

User& Chat::GetToUser()
{
    return _toUser;
}

bool Chat::HasRecipient(string username)
{
    {
        if (std::find(_toUsers.begin(), _toUsers.end(), User(username)) != _toUsers.end())
        {
            return true;
        }
        else
        {
            return false;
        }

    }
}

void Chat::ShowMessages()
{
    for (auto message : _message)
    {
        std::cout << message;
    }
}

void Chat::AddMessage(string message)
{
    _message.push_back(_fromUser.GetUserName()+":\n"+message+'\n');
}
