#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <limits> // Necessário para o numeric_limits do limparBuffer
#include "Produto.h"
using namespace std;

class Estoque {
    private:
        vector<Produto*> listaProdutos;
        
        void limparBuffer() {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
    public:
        Estoque() {}
        ~Estoque() {
            for (Produto* p : listaProdutos) {
                delete p;
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
            
        }
};
