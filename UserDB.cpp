#include "UserDB.hpp"


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
