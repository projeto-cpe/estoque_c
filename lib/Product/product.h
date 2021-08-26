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
    void get();
    void update();
    void remove();
    set<unsigned short int> getAllUIDs();
}

#endif