#include "lib/utils.h"
#include "lib/Product/product.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
    Product pr("Amendoim", 5);
    product_stock_files::create(pr);
    // vector<string> result = split::get_tokens(file::read("test.txt"), "$%");
    // print_vector(result);
    cout << endl;
 
    return 0;
}
