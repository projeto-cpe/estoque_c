#include "input.h"
#include <filesystem>

void enter(int choice){         // Função para perguntar se quer continuar depois de cada ação.
	cout << "Operação realizada! Deseja voltar ao menu inicial? (1 - Sim; 2 - Não)\n";
	cin >> choice;
        if (choice == 1){
            user_interactions();}
        
        if (choice== 2){
            cout << "Volte sempre!\n";}
}

void user_interactions(){
    // cout << "teste\n";
    // Product pr("Abacate", 5);
    // product_stock_files::create(pr);
    // product_stock_files::remove(986);
    // product_stock_files::update(895, 50);
    // string xd = "Abacate";
    // product_stock_files::update(895, 0);
    // auto x = product_stock_files::get(895);
    // cout pr.name; (acessar parametros pr)

    #ifdef cplusplus
    #include <cstdlib>
    #else
    #include <stdlib.h>
    #endif
    if (system("CLS")) system("clear");

    int entry;
    int choice;
    unsigned short int uid;
    string name;
    int quantity;
    

    cout << "Seja bem-vindo ao controle de inventário!\n\n";
    relatorio();
    cout << "\n\n O que você deseja fazer?\n 1 - Vender produto\n 2 - Inserir novo produto no estoque\n 3 - Alterar produto\n 4 - Remover produto\n 5 - Sair\n";
    
    cin >> entry;

    if (entry == 1){
        cout << "Qual é o código do produto vendido?\n";
        cin >> entry;
        int cod = entry;
        cout << "Qual foi a quantidade vendida?\n";
        cin >> entry;
        int quant = entry;
        //acessa a quantidade anterior
        auto x = product_stock_files::get(cod);
        //tira a quantidade vendida da quantidade anterior
        int atual = x.quantity - quant;
        //sobrescreve a nova quantidade na anterior 
        product_stock_files::update(cod, atual);
        enter(choice);

        
    }

    if (entry == 2){
    	cout << "Qual é o nome do produto que se deseja adicionar?\n";
    	cin.ignore();
    	getline(cin,name);
    	product_stock_files::product_exists_in_stock(name);
		if (product_stock_files::product_exists_in_stock(name)==false){
    	cout << "Quantos produtos estão entrando no estoque?\n";
    	cin>>quantity;
    	Product pr(name, quantity);
		product_stock_files::create(pr); 
        enter(choice);}
        else if (product_stock_files::product_exists_in_stock(name)==true){
			cout<<"O produto já existe no estoque.\n"<<"Tente novamente.\n";
			cout << "Deseja voltar ao menu inicial? (1 - Sim; 2 - Não)\n";
			cin >> choice;
			if (choice == 1){
			user_interactions();}
			if (choice== 2){
            cout << "Volte sempre!\n";
            }
           }
        
    }
    if (entry == 3){
        cout << "Qual o código do produto que se deseja alterar?\n";
        cin >> uid;
        cout << "O que você deseja alterar? (1 - Nome; 2 - Quantidade)\n";
        cin >> entry;
        if (entry == 1){
	    auto pr = product_stock_files::get(uid);
	    cout<< "O nome atual do produto é "<<pr.name<<endl; 
            cout << "Insira o novo nome: ";
            string new_name;
            cin.ignore();
            getline(cin,new_name);
            product_stock_files::update(uid, 0, new_name);
            
            
            
        }
        else if (entry == 2){
	    auto pr = product_stock_files::get(uid);
	    cout<<"A quantidade atual do produto é "<<pr.quantity<<endl; 
            cout << "Insira a nova quantidade: ";
            int new_quantity;
            cin>>new_quantity;
            product_stock_files::update(uid,new_quantity );
        }
        enter(choice);
    }

    if (entry == 4){
    	cout << "Qual o codigo do produto que se deseja remover?\n";
        cin >> uid;
	auto pr = product_stock_files::get(uid);
        cout<<"O produto "<<pr.name<<" foi removido do estoque"<<endl; 
        Product get(unsigned short int uid);
        product_stock_files::remove(uid);
        enter(choice);
    }
        
    
    if (entry == 5){
        cout << "Volte sempre!" << endl;
        return;
    }

}


void relatorio(){ 
    ifstream ifs("products/stock.txt");
    string line;

    cout << "Produtos atualmente estocados: \n\n";
    cout << "Código" << setw(18) << "Produto" << setw(18) << "Quantidade" << endl;
    while(std::getline(ifs, line)){
        auto uid = str_utils::split(line, ":");
        auto x = product_stock_files::get(stoi(uid[0]));

        cout << uid[0] << setw(20) << x.name << setw(15) << x.quantity << endl;
    }
}

