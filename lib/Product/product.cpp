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
        fs::path product_path{ "products/" };
        product_path /= p.name;
        product_path /= "info.txt";
        
        if(!fs_exists(product_path)) {
            create_product(product_path, p);
            update_stock(p);
        }
    }

    void create_product(const fs::path& path, Product product) {
        fs::create_directories(path.parent_path());

        string product_content = "UID:" + to_string(product.uid) + "\n" \
                               + "QUANTITY:" + to_string(product.quantity) + "\n";

        write_to_file(path, product_content);
    }


    void update_stock(Product product) {
        fs::path stock_path{ "products/stock.txt" };
        string stock_content = product.name + ":" + to_string(product.uid) + "\n";
        write_to_file(stock_path, stock_content, true);
    }


    void write_to_file(const fs::path& p, string content, bool append) {
        auto write_mode = append ? ios_base::app : ios_base::out;
        ofstream ofs(p, write_mode);
        ofs << content; 
        ofs.close();
    }


    void get(){}
    
    
    void update(){}
    
    
    void remove(){}


    bool fs_exists(const fs::path& p, fs::file_status s)
    {
        if(fs::status_known(s) ? fs::exists(s) : fs::exists(p))
            return true;
        return false;
    }


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