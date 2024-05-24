#ifndef _STORE_HPP_
#define _STORE_HPP_

#include "../Product/Product.hpp"
#include "../Client/Client.hpp"
#include "../Employee/employee.hpp"
#include "../Structures.hpp"
#include "../RandomEvent/RandomEvent.hpp"
#include <memory>
#include <vector>
#include <string>
#include <iostream>


class Store
{
    protected:
        std::vector<std::unique_ptr<Product>> products;
        std::vector<std::unique_ptr<Client>> clients;
        std::vector<std::unique_ptr<Employee>> employees;
        Money money;
    public:
        std::vector<std::unique_ptr<Product>>& get_products() const;
        std::vector<std::unique_ptr<Client>>& get_clients() const;
        std::vector<std::unique_ptr<Employee>>& get_employees() const;
        Money get_money() const;

        std::vector<std::unique<Product>> get_new_products();

        void add_money(unsigned int added_money);
        //void take_money_out(int taken_money);   //czy potrzebujemy metody zabierania pieniędzy ze sklepu? skąd wypłata dla pracowników?

        void add_products(std::vector<std::unique_ptr<Product>> new_products);
        void add_clients(std::vector<std::unique_ptr<Client>> new_clients);
        void add_employees(std::vector<std::unique_ptr<Employee>> new_employees);

        std::vector<std::unique_ptr<RandomEvent>> get_possible_events();
        std::unique_ptr<RandomEvent> draw_random_event();
};

#endif