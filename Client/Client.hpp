#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_
#include <memory>


#include "../Structures.hpp"
#include "../UserInterface/ClientInterface.hpp"


class Client
{
    protected:
        // private attributes
        std::string name;
        std::string vorname;
        Money money;
        StoreTime time_spent;
        std::unique_ptr<UserInterface> client_interface;

        // protected, helping methods
        virtual void interaction_while_paying(std::string employee_name) const; // it has default method, but can be overrided
        void update_money(Money product_price);
        void display_buying_message(std::string employee_name, std::string product_name, Money product_price) const;

    public:
        Client(std::string name, std::string vorname, Money money, StoreTime time_spent);
        virtual ~Client() = default;

        // getters and setters
        std::string get_name() const;
        Money get_money() const;
        StoreTime get_storetime() const;

        // methods including client's iterraction with the store
        virtual void start_message() const = 0;
        virtual void end_message() const = 0;
        // buy something gets employee pointer and product pointer, because they are defined in random event
        void buy_somethig(std::string employee_name, std::string product_name, Money product_price);
};

std::ostream& operator<<(std::ostream& os, const Client& client);

#endif
