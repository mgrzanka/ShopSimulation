#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_
#include <memory>
#include <vector>
#include <vector>


#include "../Structures.hpp"
#include "../UserInterface/UserInterface.hpp"


class Client
{
    protected:
        // private attributes
        std::string name;
        std::string vorname;
        Money money;
        UserInterface client_interface;

        // protected, helping methods
        virtual void interaction_while_paying(std::string employee_name) const; // it has default method, but can be overrided
        void display_buying_message(std::string employee_name, std::vector<std::string> product_names, const Money& product_price) const;
        // void display_buying_message(std::string employee_name, std::vector<std::string> product_names, const Money& product_price) const;

    public:
        Client(std::string name, std::string vorname, Money money);
        virtual ~Client() = default;

        // getters and setters
        std::string get_name() const;
        Money get_money() const;

        void add_money(unsigned int amount);
        void take_money(unsigned int amount);

        // methods including client's iterraction with the store
        virtual void start_message() const = 0;
        virtual void end_message() const = 0;

        void buy_somethig(std::string employee_name, std::vector<std::string> product_name, const Money& product_price);
};

std::ostream& operator<<(std::ostream& os, const Client& client);

#endif
