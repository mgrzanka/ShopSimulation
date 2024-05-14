#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_
#include <iostream>


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
        Product pick_product();
        Employee pick_employee();
        void get_served_by_employee(Employee& picked_employee);
        void update_money(Product& picked_product);

    public:
        // getters and setters
        std::string get_name();
        Money get_money();
        StoreTime get_storetime();

        // methods including client's iterraction with the store
        void start_message();
        void end_message();
        void buy_somethig();
};


#endif
