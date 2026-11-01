#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <limits> 
#include "Produto.h"
#include <fstream>
#include <sstream>

using namespace std;

class Estoque {
    private:
        vector<Produto*> listaProdutos;
        string nomeArquivo = "dados_mercadinho.txt";

        void carregarArquivo(){
            ifstream arquivo(nomeArquivo);
            if(! arquivo.is_open()){
                cout<<"Não foi possivel carregar os dados";
                return;
            }else{
                string linha;
                while(getline(arquivo,linha)){
                    if(linha.empty()) continue; 
                    string tipo, cod, nome, custo, qtd, d, m, a;
                    stringstream fluxo(linha);

                    getline(fluxo,tipo,';');
                    getline(fluxo,cod,';');
                    getline(fluxo,nome,';');
                    getline(fluxo,custo,';');
                    getline(fluxo,qtd,';');
                    getline(fluxo,d,';');
                    getline(fluxo,m,';');
                    getline(fluxo,a,';');

                    int codigo = stoi(cod);
                    double preco = stod(custo);
                    int qtdestoque = stoi(qtd);
                    int dia = stoi(d);
                    int mes = stoi(m);
                    int ano = stoi(a);

                    if(tipo == "ALIMENTO"){
                        string temp;
                        getline(fluxo,temp,';');
                        double tempConst = stod(temp);
                        Data validade(dia, mes, ano);
                        ProdutoAlimento *ptdAlimento = new ProdutoAlimento(codigo,nome,preco,qtdestoque,validade,tempConst);
                        listaProdutos.push_back(ptdAlimento);

                    }else if(tipo == "LIMPEZA"){
                        string aroma;
                        getline(fluxo,aroma,';');
                        Data validade(dia, mes, ano);
                        ProdutoLimpeza *ptdLimpeza = new ProdutoLimpeza(codigo,nome,preco,qtdestoque,validade,aroma);
                        listaProdutos.push_back(ptdLimpeza);
                    }
                    

            }
        }
            arquivo.close();
    }

        void salvarArquivo(){
            ofstream arquivo(nomeArquivo);
            if(!arquivo.is_open()){
                cout<<"Não foi possivel salvar os dados";
                return;
            }else{
                for(int i = 0; i < listaProdutos.size();i++){
                   arquivo << listaProdutos[i]->serializar() <<endl;

                }
            }
            arquivo.close();
    }
        
        void limparBuffer() {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
    public:
        Estoque() {
            carregarArquivo();
        }
        ~Estoque() {
            salvarArquivo();
            for (int i = 0; i < listaProdutos.size(); i++) {
                 delete listaProdutos[i];
            }
            listaProdutos.clear();
        }

        void Inserir(Produto* novoProduto) {       
            listaProdutos.push_back(novoProduto);
            cout << "Produto adicionado\n";
        }
        
        void ListarTodos() {
            if (listaProdutos.empty()) {
                cout << "Estoque Vazio\n";
                return;
            }
            cout << " === LISTA DE TODOS OS PRODUTOS ===\n";
            for (int i = 0; i < listaProdutos.size(); i++) {
                cout << i << ". ";
                listaProdutos[i]->exibirDetalhes();
            }
        }
        
        int Pesquisar(string nome) {
            vector<int> indicesEncontrados;
            
            
            for (int i = 0; i < listaProdutos.size(); i++) {
                if (listaProdutos[i]->getNome() == nome) {
                    indicesEncontrados.push_back(i);
                }
            }
            
            if (indicesEncontrados.empty()) {
                return -1;
            } else if (indicesEncontrados.size() == 1) {
                return indicesEncontrados[0];
            } else {
                int escolhaUsuario = 0;
                cout << "Produtos encontrados com esse nome:\n";
                for (int i = 0; i < indicesEncontrados.size(); i++) {
                    cout << indicesEncontrados[i] << ". " << listaProdutos[indicesEncontrados[i]]->getNome() << "\n";
                }
                cout << "Digite o numero do produto desejado: ";
                cin >> escolhaUsuario;
                
                
                for (int i = 0; i < indicesEncontrados.size(); i++) {
                    if (indicesEncontrados[i] == escolhaUsuario) {
                        return escolhaUsuario;
                    }
                }
                cout << "Opcao Invalida! \n";
                return -1;
            }
        }
       
        void exibirUm() {
            if (listaProdutos.empty()) {
                cout << "Estoque Vazio\n";
                return;
            }
            string nomeProduto;
            cout << "Digite o nome do produto: ";
        
            limparBuffer(); 
            getline(cin, nomeProduto);
            
            int indiceDoProduto = Pesquisar(nomeProduto);
            
    
            if (indiceDoProduto != -1) {
                listaProdutos[indiceDoProduto]->exibirDetalhes();
            } else {
                cout << "Produto nao encontrado\n";
            }
        }
        
        void Alterar() {
            if (listaProdutos.empty()) {
                cout << "Estoque Vazio\n";
                return;
            }
            string nome;
            cout << "Digite o nome do produto que deseja alterar: ";
            limparBuffer();
            getline(cin, nome);
            
            int indice = Pesquisar(nome);
            if (indice == -1) {
                cout << "Produto nao encontrado\n";
                return;
            }
            
            int opcao;
            cout << "Produto selecionado: " << listaProdutos[indice]->getNome() << " (Estoque: " << listaProdutos[indice]->getQtdEstoque() << ")\n";
            cout << "1. Repor Estoque \n";
            cout << "2. Dar Baixa no Estoque\n";
            cout << "3. Alterar Preco \n";
            cout << "Escolha uma opcao: ";
            cin >> opcao;
            
            if (opcao == 1) {
                int qtd;
                cout << "Quantidade a adicionar: ";
                cin >> qtd;
                listaProdutos[indice]->reporEstoque(qtd);
                cout << "Estoque adicionado com sucesso\n";
            } else if (opcao == 2) {
                int qtd;
                cout << "Quantidade a retirar: ";
                cin >> qtd;
                if (listaProdutos[indice]->darBaixaEstoque(qtd)) {
                    cout << "Estoque retirado com sucesso\n";
                } else {
                    cout << "Estoque insuficiente\n";
                }
            } else if (opcao == 3) {
                float preco;
                cout << "Novo preco do produto: ";
                cin >> preco;
                listaProdutos[indice]->setPreco(preco);
                cout << "Preco atualizado com sucesso\n";
            } else {
                cout << "Opcao invalida\n";
            }
        }
        
        void Remover() {
            if (listaProdutos.empty()) {
                cout << "Estoque Vazio\n";
                return;
            }
            string nome;
            cout << "Digite o nome do produto a ser retirado: ";
            limparBuffer();
            getline(cin, nome);
            
            int indiceDoProduto = Pesquisar(nome);
            
            if (indiceDoProduto == -1) {
                cout << "Produto nao encontrado\n";
                return;
            }
            delete listaProdutos[indiceDoProduto];
            listaProdutos.erase(listaProdutos.begin() + indiceDoProduto);
            cout << "Produto retirado com sucesso\n";
        }
        void exibirRelatorio(){
            if(listaProdutos.empty()){
                cout<<"Nao ha produtos cadastrados"<<endl;
                return;
            }
            int totalUnidadesEstoque = 0;
            double valorTotalPatrimonio = 0;

            for(int i = 0; i < listaProdutos.size(); i++){
                totalUnidadesEstoque += listaProdutos[i]->getQtdEstoque();
                valorTotalPatrimonio += listaProdutos[i]->getQtdEstoque() * listaProdutos[i]->getPreco();
            }
            cout<<"----------RELATORIO ESTATISTICO----------"<<endl;
            cout<<"Total de produtos = "<<listaProdutos.size()<<endl;
            cout<<"Total de unidades em estoque = "<<totalUnidadesEstoque<<endl;
            cout<<"Valor total do patrimonio = "<<valorTotalPatrimonio<<endl;

        }
};
