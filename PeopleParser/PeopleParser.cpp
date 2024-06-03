#include "PeopleParser.hpp"
#include "../FileHandler/FileHandler.hpp"
#include "../Employee/cashier.hpp"
#include "../Employee/manager.hpp"
#include "../Employee/cleaner.hpp"
#include "../Employee/storekeeper.hpp"
#include "../Client/RegularClient.hpp"
#include "../Client/Tourist.hpp"
#include"../Client/MenagersFriend.hpp"
#include <random>
#include <tuple>

PeopleParser::PeopleParser(std::string path):
path(path)
{}

std::string PeopleParser::get_random_name()
{
    FileHandler full_names_handle = FileHandler(path);
    std::vector<std::tuple<std::string, std::string>> full_names =full_names_handle.load_names();
    std::vector<std::string> names;

    for (std::tuple<std::string, std::string> full_name : full_names) {
        names.push_back(std::get<0>(full_name));
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_name(0, names.size() - 1);
    int random_index = dist_name(gen);

    std::string name = names[random_index];

    return name;

}

std::string PeopleParser::get_random_surname()
{
    FileHandler full_names_handle = FileHandler(path);
    std::vector<std::tuple<std::string, std::string>> full_names =full_names_handle.load_names();
    std::vector<std::string> surnames;

    for (std::tuple<std::string, std::string> full_name : full_names) {
        surnames.push_back(std::get<1>(full_name));
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_name(0, surnames.size() - 1);
    int random_index = dist_name(gen);

    std::string surname = surnames[random_index];

    return surname;
}

std::string PeopleParser::get_full_name()
{
    return get_random_name() + " " + get_random_surname();
}

std::vector<std::unique_ptr<Employee>> PeopleParser::generate_employees()
{
    std::vector<std::unique_ptr<Employee>> employees;
    Money base_wage = Money(3000);
    std::tuple<unsigned int, unsigned int> morning_shift = std::make_tuple(8, 14);
    std::tuple<unsigned int, unsigned int> afternoon_shift = std::make_tuple(14, 20);

    std::map<std::string, std::tuple<unsigned int, unsigned int>> morning_schedule = {
    {"mon",morning_shift},
    {"tue", morning_shift},
    {"wed", morning_shift},
    {"thu", morning_shift},
    {"fri", morning_shift},
    {"sat", morning_shift},
    {"sun", morning_shift},
    };

    std::map<std::string, std::tuple<unsigned int, unsigned int>> afternoon_schedule = {
    {"mon",afternoon_shift},
    {"tue", afternoon_shift},
    {"wed", afternoon_shift},
    {"thu", afternoon_shift},
    {"fri", afternoon_shift},
    {"sat", afternoon_shift},
    {"sun", afternoon_shift},
    };

    Money base_bonus = Money(5);

    std::unique_ptr<Employee> cashier1 = std::make_unique<Cashier>(get_full_name(), morning_schedule, base_wage, base_bonus);
    employees.push_back(std::move(cashier1));

    std::unique_ptr<Employee> cashier2 = std::make_unique<Cashier>(get_full_name(), afternoon_schedule, base_wage, base_bonus);
    employees.push_back(std::move(cashier2));

    std::unique_ptr<Employee> cleaner1 = std::make_unique<Cleaner>(get_full_name(), morning_schedule, base_wage, base_bonus);
    employees.push_back(std::move(cleaner1));

    std::unique_ptr<Employee> cleaner2 = std::make_unique<Cleaner>(get_full_name(), afternoon_schedule, base_wage, base_bonus);
    employees.push_back(std::move(cleaner2));

     std::unique_ptr<Employee> manager1 = std::make_unique<Manager>(get_full_name(), morning_schedule, base_wage, base_bonus);
    employees.push_back(std::move(manager1));

    std::unique_ptr<Employee> manager2 = std::make_unique<Manager>(get_full_name(), afternoon_schedule, base_wage, base_bonus);
    employees.push_back(std::move(manager2));

     std::unique_ptr<Employee> storekeeper1 = std::make_unique<Storekeeper>(get_full_name(), morning_schedule, base_wage, base_bonus);
    employees.push_back(std::move(storekeeper1));

    std::unique_ptr<Employee> storekeeper2 = std::make_unique<Storekeeper>(get_full_name(), afternoon_schedule, base_wage, base_bonus);
    employees.push_back(std::move(storekeeper2));

    return employees;
}
    std::vector<std::unique_ptr<Client>> PeopleParser::generate_clients()
    {
        std::vector<std::unique_ptr<Client>> clients;
        std::unique_ptr<Client> client;

        for (int i = 0; i < 20; ++i)
        {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist_name(1, 3);
        int random_int = dist_name(gen);

        switch(random_int)
        {
            case 1:
                client = std::make_unique<RegularClient>(get_random_name(), get_random_surname(), Money(100000), StoreTime(10));
                clients.push_back(std::move(client));
                break;
            case 2:
                client = std::make_unique<Tourist>(get_random_name(), get_random_surname(), Money(1000000), StoreTime(30));
                clients.push_back(std::move(client));
                break;
            case 3:
                client = std::make_unique<MenagersFriend>(get_random_name(), get_random_surname(), Money(10000), StoreTime(5));
                clients.push_back(std::move(client));
                break;
        }
        }
        return clients;

        
    }