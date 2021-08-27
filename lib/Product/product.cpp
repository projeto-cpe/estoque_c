#include "product.h"


Product::Product(string _n, int _q)
{
    uid = generate_uid();
    name = _n;
    quantity = _q;
}


unsigned short int Product::generate_uid()
{
    auto uids = product_stock_files::getAllUIDs();

    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(1, 999);
    
    unsigned int uid = (unsigned short int) dist(mt);
    
    for (; uids.contains(uid); uid = (unsigned short int) dist(mt));

    return uid;
}


namespace product_stock_files {
    fs::path get_product_path(unsigned short int uid)
    {
        fs::path product_path{ "products/" };
        product_path /= to_string(uid);
        product_path /= "info.txt";
        return product_path;
    }


    void create(Product p)
    {
        auto product_path = get_product_path(p.uid);
        
        if(!file::fs_exists(product_path))
        {
            create_product(product_path, p);
            add_to_stock(p);
        }
    }

    
    string build_product_info(Product p)
    {
        return "NAME:" + p.name + "\n" \
             + "QUANTITY:" + to_string(p.quantity) + "\n";
    }


    void create_product(const fs::path& path, Product product)
    {
        fs::create_directories(path.parent_path());

        string product_content = build_product_info(product);

        file::write(path, product_content);
    }


    void add_to_stock(Product product)
    {
        fs::path stock_path{ "products/stock.txt" };
        string stock_content =  to_string(product.uid) + ":" + product.name + "\n";
        file::write(stock_path, stock_content, true);
    }


    Product get(unsigned short int uid) {
        auto product_path = get_product_path(uid);
        if (file::fs_exists(product_path)) {
            vector<string> tokens = str_utils::split(file::read(product_path), "\n");
            auto name_value = str_utils::split(tokens[0], "NAME:")[1];
            auto quantity_value = stoi(str_utils::split(tokens[1], "QUANTITY:")[1]);
            Product pr(name_value, quantity_value);
            return pr;
        }
    }
    
    
    bool there_is_something_to_update(int new_quantity, string new_name) {
        return new_quantity || new_name != "";
    }


    void update(unsigned short int uid, int new_quantity, string new_name)
    {
        if (there_is_something_to_update(new_quantity, new_name))
        {
            auto product = get(uid);
            product.quantity = new_quantity ? new_quantity : product.quantity;
    
            if (new_name != "") {
                update_stock_product_name(uid, product.name, new_name);
                product.name = new_name;
            }
    
            string product_content = build_product_info(product);

            auto path = get_product_path(uid);
            file::write(path, product_content);

        }
    }
    

    void update_stock_product_name(unsigned short int uid, string old_name, string new_name)
    {
        fs::path stock_path{ "products/stock.txt" };
        string stock_content = file::read("products/stock.txt");
        stock_content = str_utils::replace(stock_content, old_name, new_name);
        file::write(stock_path, stock_content);
    }

    
    void remove(){}


    set<unsigned short int> getAllUIDs()
    {
        set<unsigned short int> result;

        vector<string> tokens = str_utils::split(file::read("products/stock.txt"), "\n");
        
        for (auto &tok : tokens)
        {
            if (tok != "")
            {
                auto product_uid = str_utils::split(tok, ":");
                int _uid = stoi(product_uid[0]);
                result.insert((unsigned short int)_uid);
            }
        }

        return result;
    }
}