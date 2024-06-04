#include "catch_amalgamated.hpp"
#include "../PeopleParser/PeopleParser.hpp"

TEST_CASE("PeopleParser class") {
    PeopleParser parser = PeopleParser("../names.txt");
    std::vector<std::unique_ptr<Employee>> employees = parser.generate_employees();
    REQUIRE(employees.size() == 8);

    std::vector<std::unique_ptr<Client>> clients = parser.generate_clients();
    REQUIRE(clients.size() == 20);
}