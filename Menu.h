#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include "Chat.h"

using std::vector;
using std::string;


void CreateUser(const string username, const string password, const string name);
void DeleteUser();
User* Login(const string username, const string password);
void Logout();
const bool FindUser(const string username);
User* GetUser(const string username);
void LoginMenu();
void UserMenu();
void ShowUserDataBase();
void CreateMessage();
void ShowMessage();

static bool HasLoggedIn = false;
static bool Terminator = false;
static vector<User> UserDataBase;
static vector<Chat> ChatDataBase;
static User* currentUser = nullptr;


void CreateUser(const string username, const string password, const string name)
{
    if (FindUser(username))
    {
        std::cout << "This user already exists!\n";
    }
    else
    {
        std::cout << "User has been created!\n";
        UserDataBase.push_back(User(username, password, name));
    }
}

void DeleteUser()
{
    UserDataBase.erase(std::find(UserDataBase.begin(), UserDataBase.end(), User(currentUser->GetUserName())));
    currentUser = nullptr;
    HasLoggedIn = false;
}

User* Login(const string username, const string password)
{
    if (FindUser(username))
    {
        auto search_index = std::find(UserDataBase.begin(), UserDataBase.end(), User(username));
        if (search_index->CheckUser(username, password))
        {
            std::cout << "Welcome to CLI Chat!\n";
            HasLoggedIn = true;
            return &(UserDataBase[search_index - UserDataBase.begin()]);
        }
        else
        {
            std::cout << "Wrong Password!\n";
            return nullptr;
        }

    }
    else
    {
        std::cout << "Such user does not exist! Please register or enter correct username!\n";
        return nullptr;
    }
}

void Logout()
{
    currentUser = nullptr;
    HasLoggedIn = false;
}

const bool FindUser(const string username)
{
    if (std::find(UserDataBase.begin(), UserDataBase.end(), User(username)) != UserDataBase.end())
    {
        return true;
    }
    else
    {
        return false;
    }

}

User* GetUser(const string username)
{
    if (FindUser(username))
    {
        auto search_index = std::find(UserDataBase.begin(), UserDataBase.end(), User(username));
        return &(UserDataBase[search_index - UserDataBase.begin()]);
    }
    {
        std::cout << "User not exist!\n";
        return nullptr;
    }

}

void LoginMenu()
{
    string username, password, name;
    int menuOperator = 0;
    std::cout << "Welcome to CLI Chat, please choose your option:\n";
    std::cout << "\t0 - Exit\n"
        << "\t1 - Login\n"
        << "\t2 - Create User\n"
        << "\t3 - Forgot Password\n"
        << "\t4 - Show User Data Base\n";    
      
    while (!(std::cin >> menuOperator))
    {

        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid input! Please try again with valid input: ";
    }

    switch (menuOperator)
    {
    case 0:
        std::cout << "Closing application!\n";
        Terminator = true;
        break;
    case 1:
        std::cout << "Please enter username: ";
        std::cin >> username;
        std::cout << "Please enter password: ";
        std::cin >> password;
        currentUser = Login(username, password);
        break;
    case 2:
        std::cout << "Please enter username: ";
        std::cin >> username;
        std::cout << "Please enter password: ";
        std::cin >> password;
        std::cout << "Please enter your name: ";
        std::cin >> name;
        CreateUser(username, password, name);
        break;
    case 4:
        ShowUserDataBase();
        break;
    default:
        std::cout << "Wrong statement!\n";
        break;
    }
}

void UserMenu()
{
    string username, password;
    int menuOperator;
    std::cout << "Welcome user: " << currentUser->GetName() << "\nPlease choose your option:\n";
    std::cout << "\t1 - Show Messages\n"
        << "\t2 - Send Message\n"
        << "\t3 - Logout\n"
        << "\t4 - Delete User\n"
        << "\t5 - Change Password\n"
        << "\t0 - Exit\n";
    std::cin >> menuOperator;
    switch (menuOperator)
    {
    case 0:
        Terminator = true;
        break;
    case 1:
        std::cout << "Messages: \n";
        ShowMessage();
        break;
    case 2:
        std::cout << "Send message\n";
        CreateMessage();
        break;
    case 3:
        std::cout << "You has logout\n";
        Logout();
        break;
    case 4:
    {
        std::cout << "Are you sure you want to delete your user?(Y/N): ";
        char choise = 'Y';        
        std::cin >> choise;
        if (toupper(choise) == 'Y')
        {
            DeleteUser();
            std::cout << "User has been successfuly deleted!\n";
            break;
        }        
        break;
    }
    case 5:
        std::cout << "Please enter old password: ";
        std::cin >> password;
        if (password == currentUser->GetPassword())
        {
            std::cout << "Please enter new password: ";
            std::cin >> password;
            currentUser->SetPassword(password);
            std::cout << "Your password has been changed to: " << currentUser->GetPassword() << std::endl;
        }
        else
        {
            std::cout << "Wrong old password!\n";
        }
        break;
    default:
        std::cout << "Wrong statement!\n";
        break;
    }

}

void ShowUserDataBase()
{
    if (UserDataBase.empty())
    {
        std::cout << "User data base is empty!\n";
    }
    else
    {
        for (auto user : UserDataBase)
        {
            std::cout << user << '\n';
        }
    }    
}

void CreateMessage()
{
    string username;
    string message;
    vector<User> recipients;
    char choise = 'Y';
    std::cout << "Do you want to send this message to all users?(Y/N): ";
    std::cin >> choise;
    if (toupper(choise) == 'Y')
    {
        std::cout << "Enter message: \n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, message);
        for (auto reciever : UserDataBase)
        {
            if (reciever == *currentUser)
            {
                continue;
            }
            else
            {
                recipients.push_back(reciever);
            }
        }
        ChatDataBase.push_back(Chat(currentUser, recipients, message));
        
    }
    else if (toupper(choise) == 'N')
    {
        std::cout << "Enter user name: ";
        std::cin >> username;
        if (FindUser(username))
        {
                if (ChatDataBase.empty())
            {
                std::cout << "Enter message:\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, message);
                ChatDataBase.push_back(Chat(currentUser, GetUser(username), message));
            }
            else
            {
                for (int i = 0; i < ChatDataBase.size(); i++)
                {
                    if ((*currentUser == ChatDataBase[i].GetFromUser() || *currentUser == ChatDataBase[i].GetToUser())
                        && (*GetUser(username) == ChatDataBase[i].GetFromUser() || *GetUser(username) == ChatDataBase[i].GetToUser()))
                    {
                        std::cout << "Enter message: \n";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::getline(std::cin, message);
                        ChatDataBase[i].AddMessage(message);
                        break;
                    }
                    else
                    {
                        std::cout << "Enter message: \n";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::getline(std::cin, message);
                        ChatDataBase.push_back(Chat(currentUser, GetUser(username), message));
                        break;
                    }
                }
            }      

        }
        else
        {
            std::cout << "User does not exist!\n";
        }

    }
    else
    {
        std::cout << "Incorrect input!\n";
    }

}

void ShowMessage()
{
    for (auto checkMessage : ChatDataBase)
    {
        if (*currentUser == checkMessage.GetFromUser() || *currentUser == checkMessage.GetToUser())
        {
            checkMessage.ShowMessages();
        }
        else if (checkMessage.HasRecipient(currentUser->GetUserName()))
        {
            checkMessage.ShowMessages();
        }
    }

}