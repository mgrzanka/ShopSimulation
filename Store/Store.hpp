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
        Money money;
        std::vector<std::unique_ptr<Product>> products;

        std::vector<std::unique_ptr<Client>> taken_clients;
        std::vector<std::unique_ptr<Client>> available_clients;

        std::vector<std::unique_ptr<Employee>> on_shift_employees;
        std::vector<std::unique_ptr<Employee>> on_shift_occupied_employees;
        std::vector<std::unique_ptr<Employee>> on_break_employees;
    public:
        Store(std::vector<std::unique_ptr<Product>>& products,
                std::vector<std::unique_ptr<Client>>& clients,
                std::vector<std::unique_ptr<Employee>>& employees,
                Money money);
        Store() = default;

        const std::vector<std::unique_ptr<Product>>& get_products() const;
        const std::vector<std::unique_ptr<Client>>& get_taken_clients() const;
        const std::vector<std::unique_ptr<Client>>& get_available_clients() const;
        const std::vector<std::unique_ptr<Employee>>& get_on_shift_employees() const;
        const std::vector<std::unique_ptr<Employee>>& get_on_shift_occupied_employees() const;
        const std::vector<std::unique_ptr<Employee>>& get_on_break_employees() const;
        Money get_money() const;

        void add_money(Money added_money);
        void take_money_out(Money taken_money);

        void add_products(std::vector<std::unique_ptr<Product>>& new_products);
        void add_clients(std::vector<std::unique_ptr<Client>>& new_clients);
        void add_employees(std::vector<std::unique_ptr<Employee>>& new_employees);

        std::tuple<std::vector<int>, std::vector<int>> check_employee_shift(unsigned int day, unsigned int iterations, unsigned int starting_hour, unsigned int closing_hour);
        void update_employees_shift(std::tuple<std::vector<int>,std::vector<int>> employees);

        friend class EventGenerator;
        friend class CleanerCleans;
        friend class ClientBuysEvent;
        friend class MenagerGivesRise;
        friend class SupplierAddsProducts;
};
#endif
