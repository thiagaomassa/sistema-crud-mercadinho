#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Produto.h"
#pragma once
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
            cout << "Produto selecionado: " << p->getNome() << " (Estoque: " << p->getQtdEstoque() << ")\n";
            cout << "1. Repor Estoque "<<endl;
            cout << "2. Dar Baixa no Estoque"<<endl;
            cout << "3. Alterar Preco "<<endl;
            cout << "Escolha uma opcao: ";
            cin>>opcao;
            
        }



};
