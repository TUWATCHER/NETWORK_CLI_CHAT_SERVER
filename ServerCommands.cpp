#include "ServerCommands.hpp"


UserDB &UserDB::getInstance()
{
    static UserDB theInstance {};
    return theInstance;
}

bool UserDB::loginUser(const std::string &username, const std::string &password)
{
    std::string query = {
                        "select * from chatdb.usertb where usernm = \'"
                        + username + 
                        "\' and passwd = \'" 
                        + password + 
                        "\'"};
    try
    {
        pqxx::connection conn("user=postgres password=<Rv567%00> host=127.0.0.1 port=5432 dbname=template1");
        pqxx::work trans{conn};
        pqxx::result res = trans.exec(query);
        trans.commit();

        if (res.size())
        {
            std::cout << "User exists!\n";    
            return true;
        }
        else
        {
            std::cout << "User does not exist!\n";
            return false;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return false; 
}

bool UserDB::registerUser(const std::string &username, const std::string &password)
{
    std::string query = {
                        "insert into chatdb.usertb (usernm, passwd) values (\'"
                        + username +  "\', " 
                        + "\'" + password + "\' ); "
                        };
    std::cout << query << std::endl;

    try
    {
        pqxx::connection conn("user=postgres password=<Rv567%00> host=127.0.0.1 port=5432 dbname=template1");
        pqxx::work trans{conn};
        pqxx::result res = trans.exec(query);
        trans.commit();
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }                   
                        
    return false;
}

bool UserDB::deleteUser(const std::string &username)
{
    std::string query = {
                        "delete from chatdb.usertb where usernm = \'"
                        + username + 
                        "\'"};
    std::cout << query << std::endl;

     try
    {
        pqxx::connection conn("user=postgres password=<Rv567%00> host=127.0.0.1 port=5432 dbname=template1");
        pqxx::work trans{conn};
        pqxx::result res = trans.exec(query);
        trans.commit();
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }                   
                        
    return false;
}

bool UserDB::createMessage(const std::string &fromUser, const std::string &toUser, const std::string &message)
{
    std::string query = {
                        "insert into chatdb.messagetb (fromuser, touser, message) values (\'"
                        + fromUser +  "\', " 
                        + "\'" + toUser + "\', "
                        +  "\'" + message + "\'); "
                        };

    try
    {
        pqxx::connection conn("user=postgres password=<Rv567%00> host=127.0.0.1 port=5432 dbname=template1");
        pqxx::work trans{conn};
        pqxx::result res = trans.exec(query);
        trans.commit();
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    } 
    return false;
}

std::vector<std::string> UserDB::checkMessage(const std::string &username)
{
    std::vector<std::string> chat;
    std::string query = {
                        "select * from chatdb.messagetb where touser = \'"
                         + username + "\'"
                        };
    try
    {
        pqxx::connection conn("user=postgres password=<Rv567%00> host=127.0.0.1 port=5432 dbname=template1");
        pqxx::work trans{conn};
        pqxx::result res = trans.exec(query);
        for (auto row : res)
        {
            chat.push_back("[From:]" + row["fromuser"].as<std::string>() + '\n' + row["message"].as<std::string>() + '\n');
        }

        return chat;

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return chat;
    } 
    
}

void UserDB::UserParser(const char request[], std::string &_username, std::string &_password)
{
    std::string UID = request;
    UID.erase(0, 9);     
    _username = UID.substr(0, UID.find("#UIDE#"));
    
    UID.erase(0, UID.find("#PWDB#") + 6);        
    _password = UID.substr(0, UID.find("#PWDE#"));
}

void UserDB::MessageParser(const char request[], std::string &fromUser, std::string &toUser, std::string &message)
{
    std::string MSG = request;
    MSG.erase(0, 9);
    std::cout << MSG << std::endl;

    fromUser = MSG.substr(0, MSG.find("#TO#"));
    std::cout << "FROM: " << fromUser << std::endl;

    MSG.erase(0, MSG.find("#TO#") + 4);
    toUser = MSG.substr(0, MSG.find("#MSG#"));
    std::cout << "TO: " << toUser << std::endl;

    MSG.erase(0, MSG.find("#MSG#") + 5);
    message = MSG.substr(0, MSG.size());
    std::cout << "Message: " << message << std::endl;
}
