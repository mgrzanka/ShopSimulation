#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include "Client/Client.hpp"
#include "Employee/employee.hpp"
#include "FileHandler/FileHandler.hpp"
#include "Simulation/Simulation.hpp"
#include "PeopleParser/PeopleParser.hpp"
#include "Structures.hpp"



int main(int argc, char* argv[]) {
    // // Parser
    // if (argc < 1) {
    //     std::cerr << "Usage: " << argv[0] << " <days> <starting budget> <names file path> <products file path>"<< std::endl;
    //     return 1;
    // }
    // unsigned int days;
    // unsigned int starting_budget;
    // try
    // {
    //     days = std::stoi(argv[1]);
    //     starting_budget = std::stoi(argv[2]);
    // }catch(std::invalid_argument& e){std::cout<<"Number in arguments is not a correct number!"; exit(0);}
    // std::string names_path = argv[3];
    // if(names_path.empty()) names_path = "names.txt";
    // std::string products_path = argv[4];
    // if(products_path.empty()) products_path = "products.txt";

    // Creating auxiliary objects for simulation
    PeopleParser people_parser("/home/gosia/PROI/proi_24l_101_projekt/names.txt");
    std::vector<std::unique_ptr<Client>> clients = people_parser.generate_clients();
    std::vector<std::unique_ptr<Employee>> employees = people_parser.generate_employees();
    FileHandler file_handler("/home/gosia/PROI/proi_24l_101_projekt/products.txt");
    Store store(clients, employees, Money(1000000));
    std::vector<float> probabilities = {0.1, 0.2, 0.1, 0.6};

    // Simulation
    Simulation simulation(2, 8, 20, store, probabilities, file_handler);
    simulation.run();

    std::cout<<"Thanks for staying here in this fascinating simulation\n";

    return 0;
}
