#include "lib/utils.h"
#include "lib/Product/product.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
    Product pr("Amendoim", 5);
    product_stock_files::create(pr);
    // product_stock_files::update(895, 50);
    // string xd = "Abacate";
    // product_stock_files::update(895, 0, xd);
    // auto x = product_stock_files::get(895);
    // vector<string> result = str_utils::split(file::read("test.txt"), "$%");
    // print_vector(result);
    // cout << x.name << endl;
 
    return 0;
}
