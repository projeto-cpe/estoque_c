#include "product.h"


Product::Product(unsigned short int _u, string _n, int _q) {
    uid = _u;
    name = _n;
    quantity = _q;
}

namespace product_stock_files {
    void create(Product p) {
        fs::path path{ "products/" };
        path /= p.name;
        path /= "info.txt";

        fs::create_directories(path.parent_path());

        string info_content = "UID: " + to_string(p.uid) + "\n" \
                            + "QUANTITY: " + to_string(p.quantity) + "\n";

        ofstream ofs(path);
        ofs << info_content; 
        ofs.close();
    }
    void get(){}
    void update(){}
    void remove(){}
}