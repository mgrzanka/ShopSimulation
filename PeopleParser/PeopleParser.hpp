#include <memory>
#include <string>
#include <vector>
#include "../Employee/employee.hpp"
#include "../Client/Client.hpp"

class PeopleParser {

private:
    std::string path;
    std::string get_random_name();
    std::string get_random_surname();
    std::string get_full_name();

public:
    PeopleParser(std::string path);
    std::vector<std::unique_ptr<Employee>> generate_employees();
    std::vector<std::unique_ptr<Client>> generate_clients();

};
