#ifndef PRODUCT_H
#define PRODUCT_H

#include <filesystem>
#include <string>
#include <fstream>
#include "../utils.h"
#include <random>

using namespace std;
namespace fs = filesystem;

class Product {
  private:
    unsigned short int generate_uid();

  public:
    unsigned short int uid;
    string name;
    int quantity;
    Product(string _n, int _q);
};

namespace product_stock_files {
    void create(Product p);
    void create_product(const fs::path& path, Product product);
    void update_stock(Product product);
    string build_product_info(Product p);
    Product get(unsigned short int uid);
    void update(unsigned short int uid, int new_quantity=0, string new_name="");
    void remove();
    void write_to_file(const fs::path& p, string content, bool append = false);
    set<unsigned short int> getAllUIDs();
}

#endif