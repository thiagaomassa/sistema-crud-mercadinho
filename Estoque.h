#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Produto.h"
using namespace std;

class Estoque{
    private:
        vector<Produto*> listaProdutos;
        void limparBuffer() {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    public:
        Estoque(){}
        ~Estoque(){

        }

        void Inserir(Produto* novoProduto){      
            listaProdutos.push_back(novoProduto);
            cout<<"Produto adicionado\n";
        }
        void ListarTodos(){
            cout<<" === LISTA DE TODOS OS PRODUTOS ==="<<endl;
            for(int i = 0; i < listaProdutos.size(); i++){
                cout <<i<<". "<<listaProdutos[i]->exibirDetalhes();
            }
        }
        int Pesquisar(string nome){
            vector<int> indicesEncontrados;
            for(int i = 0; i < listaProdutos.size(); i++){

                if(listaProdutos[i]->getNome() == nome){
                    indicesEncontrados.push_back(i);
                }
                if(indicesEncontrados.size() == 0){
                    return -1;

                }else if(indicesEncontrados.size() == 1){
                    return indicesEncontrados[0];

                }else{
                    int escolhaUsuario = 0;
                    for(int i = 0; i < indicesEncontrados.size(); i++){
                        cout<<indicesEncontrados[i]<<"."<<" "<<listaProdutos[indicesEncontrados[i]]->getNome()<<endl;
                    }
                    cout<<"Digite o numero do produto desejado";
                    cin>>escolhaUsuario;
                    if(escolhaUsuario > 0 && escolhaUsuario <= listaProdutos.size()){
                        return escolhaUsuario;
                    }else{
                        cout<<"Opcao Invalida! ";
                        return -1;
                    }
                }
                
            }
        }
       
        void exibirUm(){

            string nomeProduto;
            int indiceDoProduto;
            cout<<"Digite o nome do produto: ";
            getline(cin,nomeProduto);
            indiceDoProduto = Pesquisar(nomeProduto);
            cout<<listaProdutos[indiceDoProduto]->exibirDetalhes();

        }
        void Alterar(){
            if(listaProdutos.empty()){
                cout<<"Estoque Vazio";
                return;

            }
            string nome;
            cout<<"Digite o nome do produto que deseja alterar: ";
            limparBuffer();
            getline(cin,nome);
            int indice = Pesquisar(nome);
            if(indice == -1){
                cout<<"Produto nao encontrado";
                return;
            }
            int opcao;
            cout << "Produto selecionado: " << listaProdutos[indice]->getNome() << " (Estoque: " << listaProdutos[indice]->getQtdEstoque() << ")\n";
            cout << "1. Repor Estoque "<<endl;
            cout << "2. Dar Baixa no Estoque"<<endl;
            cout << "3. Alterar Preco "<<endl;
            cout << "Escolha uma opcao: ";
            cin>>opcao;
            if(opcao == 1){
                int qtd;
                cout<<"Quantidade a adicionar: ";
                cin>>qtd;
                listaProdutos[indice]->reporEstoque(qtd);
                cout<<"Estoque adicionado com sucesso";
            }else if (opcao == 2){
                int qtd;
                cout<<"Quantidade a retirar: ";
                cin>>qtd;
                if(listaProdutos[indice]->darBaixaEstoque(qtd)){
                    cout<<"Estoque retirado com sucesso";
                }else{
                    cout<<"Estoque insuficiente";
                }
            }else if(opcao == 3){
                float preco;
                cout<<"Novo preco do produto: ";
                cin>>preco;
                listaProdutos[indice]->setPreco(preco);
                cout<<"Preco atualizado com sucesso";
            }else{
                cout<<"Opcao invalida";
                return;
            }
            
        }
        void Remover(){
            if(listaProdutos.empty()){
                cout<<"Estoque Vazio";
                return;
            }
            string nome;
            int indiceDoProduto;
            cout<<"Digite o nome do produto a ser retirado: ";
            limparBuffer();
            getline(cin,nome);
            indiceDoProduto = Pesquisar(nome);
            if(indiceDoProduto == -1){
                cout<<"Produto nao encontrado"<<endl;
                return;
            }
            delete listaProdutos[indiceDoProduto];
            listaProdutos.erase(listaProdutos.begin() + indiceDoProduto);
            cout<<"Produto retirado com sucesso";

        }
        void Relatorio(){
            
        }



};
