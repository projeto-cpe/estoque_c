#include "product.h"


Product::Product(string _n, int _q) {
    uid = generate_uid();
    name = _n;
    quantity = _q;
}


unsigned short int Product::generate_uid() {
    auto uids = product_stock_files::getAllUIDs();

    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(1, 999);
    
    unsigned int uid = (unsigned short int) dist(mt);
    
    for (; uids.contains(uid); uid = (unsigned short int) dist(mt));

    return uid;
}


namespace product_stock_files {
    void create(Product p) {
        fs::path path{ "products/" };
        path /= p.name;
        path /= "info.txt";

        fs::create_directories(path.parent_path());

        string info_content = "UID:" + to_string(p.uid) + "\n" \
                            + "QUANTITY:" + to_string(p.quantity) + "\n";

        ofstream ofs(path);
        ofs << info_content; 
        ofs.close();
    }


    void get(){}
    
    
    void update(){}
    
    
    void remove(){}
    
    
    set<unsigned short int> getAllUIDs() {
        set<unsigned short int> result;

        vector<string> tokens = split::get_tokens(file::read("products/stock.txt"), "\n");
        
        for (auto &tok : tokens) {
            if (tok != "") {
                auto product_uid = split::get_tokens(tok, ":");
                int _uid = stoi(product_uid[1]);
                result.insert((unsigned short int)_uid);
            }
        }

        printf("%ld\n", result.size());

        return result;
    }
}