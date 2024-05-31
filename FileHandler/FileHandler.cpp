#include "FileHandler.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

FileHandler::FileHandler(std::string path):
path(path)
{}

std::vector<std::tuple<std::string, std::string>> FileHandler::load_names()
{
     file.open(path);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
    }
    std::vector<std::tuple<std::string, std::string>> names;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string name;
        std::string surname;

        if (std::getline(lineStream, name, ',') && std::getline(lineStream, surname)) {
            names.emplace_back(name, surname);
        }
    }

    file.close();
    return names;
}


std::vector<std::unique_ptr<Product>> FileHandler::load_products()
{
    file.open(path);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
    }

    std::vector<std::unique_ptr<Product>> products;
    std::string line;
      while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string type, name;
        int amount;

        std::getline(ss, type, ',');
        std::getline(ss, name, ',');
        ss >> amount;

        if (type == "vegetable") {
            products.push_back(std::make_unique<Vegetable>(name, amount));
        } else if (type == "dairy") {
            products.push_back(std::make_unique<Dairy>(name, amount));
        } else if (type == "fruit") {
            products.push_back(std::make_unique<Fruit>(name, amount));
        }
    }

}