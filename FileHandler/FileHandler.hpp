#include "../Product/Product.hpp"
#include <memory>
#include <vector>
#include <fstream>


class FileHandler
{
    std::string path;
    std::ifstream file;
    public:
        FileHandler(std::string path);
        std::vector<std::tuple<std::string, std::string>> load_names();
        std::vector<std::unique_ptr<Product>> load_products();
};
