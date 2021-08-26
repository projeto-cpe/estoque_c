#ifndef PRODUCT_H
#define PRODUCT_H

#include <filesystem>
#include <string>
#include <fstream>

using namespace std;
namespace fs = filesystem;

class Product {
  public:
    unsigned short int uid;
    string name;
    int quantity;
    Product(unsigned short int _u, string _n, int _q);
};

namespace product_stock_files {
    void create(Product p);
    void get();
    void update();
    void remove();
}

#endif