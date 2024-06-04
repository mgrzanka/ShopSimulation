#include "catch_amalgamated.hpp"
#include "../FileHandler/FileHandler.hpp"
#include <tuple>
#include <vector>

TEST_CASE("Filehandler class") {
    FileHandler product_handle = FileHandler("../products.txt");
    FileHandler names_handle = FileHandler("../names.txt");

    std::vector<std::unique_ptr<Product>> products = product_handle.load_products();
    REQUIRE(products.size() == 178);
    REQUIRE(products[0]->get_name() == "orange");

    std::vector<std::tuple<std::string, std::string>> names = names_handle.load_names();
    REQUIRE(names.size() == 125);
    REQUIRE(names[0] == std::make_tuple("William" , "Smith") );
}