#include "../Product/Product.hpp"
#include "../Employee/Employee.hpp"
#include "../Client/Client.hpp"
#include <memory>
#include <vector>



class FileHandler
{
    std::string path;
    public:
        FileHandler(std::string path);
        std::vector<std::unique_ptr<Client>> load_clients();
        std::vector<std::unique_ptr<Employee>> load_employees();
        std::vector<std::unique_ptr<Client>> load_products();
};
