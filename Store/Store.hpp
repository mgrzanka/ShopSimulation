#ifndef _STORE_HPP_
#define _STORE_HPP_

#include "../Product/Product.hpp"
#include "../Client/Client.hpp"
#include "../Employee/employee.hpp"
#include "../Structures.hpp"
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
        Store(std::vector<std::unique_ptr<Product>>& products,
                std::vector<std::unique_ptr<Client>>& clients,
                std::vector<std::unique_ptr<Employee>>& employees,
                Money money);

        const std::vector<std::unique_ptr<Product>>& get_products() const;
        const std::vector<std::unique_ptr<Client>>& get_clients() const;
        const std::vector<std::unique_ptr<Employee>>& get_employees() const;
        Money get_money() const;

        void add_money(Money added_money);
        void take_money_out(Money taken_money);

        void add_products(std::vector<std::unique_ptr<Product>>& new_products);
        void add_clients(std::vector<std::unique_ptr<Client>>& new_clients);
        void add_employees(std::vector<std::unique_ptr<Employee>>& new_employees);

        friend class EventGenerator;
};
#endif