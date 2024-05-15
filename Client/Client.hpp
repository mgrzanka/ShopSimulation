#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_
#include <iostream>
#include <memory>
#include <ostream>


#include "../Structures.hpp"
#include "../Employee/Employee.hpp"
#include "../Product/Product.hpp"


class Client
{
    private:
        // private attributes
        std::string name;
        std::string vorname;
        Money money;
        StoreTime time_spent;

        // private, helping methods
        void talk_to_employee(const std::unique_ptr<Employee>& employee_ptr) const;
        void update_money(const std::unique_ptr<Product>& product_ptr);
        virtual void display_buying_message(const std::unique_ptr<Employee>& employee_ptr, const std::unique_ptr<Product>& product_ptr) = 0;

    public:
        Client(std::string name, std::string vorname,
                Money money, StoreTime time_spent);
        virtual ~Client() = default;

        // getters and setters
        std::string get_name() const;
        Money get_money() const;
        StoreTime get_storetime() const;

        // methods including client's iterraction with the store
        virtual void start_message() const = 0;
        virtual void end_message() const = 0;
        // buy something gets employee pointer and product pointer, because they are defined in random event
        void buy_somethig(const std::unique_ptr<Employee>& employee_ptr, const std::unique_ptr<Product>& product_ptr);
};

std::ostream& operator<<(std::ostream& os, const Client& client);

#endif
