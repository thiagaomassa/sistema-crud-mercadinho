#pragma once

#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "Produto.h"
#include "ProdutoAlimento.h"
#include "ProdutoLimpeza.h"

using namespace std;

class Estoque {
private:
    vector<Produto*> listaProdutos;
    string nomeArquivo = "dados_mercadinho.txt";

    void carregarArquivo() {
        ifstream arquivo(nomeArquivo);

        if (!arquivo.is_open()) {
            cout << "Não foi possivel carregar os dados";
            return;
        }

        string linha;
        while (getline(arquivo, linha)) {
            if (linha.empty()) {
                continue;
            }

            string tipo, cod, nome, custo, qtd, d, m, a;
            stringstream fluxo(linha);

            getline(fluxo, tipo, ';');
            getline(fluxo, cod, ';');
            getline(fluxo, nome, ';');
            getline(fluxo, custo, ';');
            getline(fluxo, qtd, ';');
            getline(fluxo, d, ';');
            getline(fluxo, m, ';');
            getline(fluxo, a, ';');

            int codigo = stoi(cod);
            double preco = stod(custo);
            int quantidade = stoi(qtd);
            int dia = stoi(d);
            int mes = stoi(m);
            int ano = stoi(a);
            Data validade(dia, mes, ano);

            if (tipo == "ALIMENTO") {
                string temperatura;
                getline(fluxo, temperatura, ';');

                double temp = stod(temperatura);
                ProdutoAlimento* produto = new ProdutoAlimento(
                    codigo, nome, preco, quantidade, validade, temp);
                listaProdutos.push_back(produto);
            }
            else if (tipo == "LIMPEZA") {
                string aroma;
                getline(fluxo, aroma, ';');

                ProdutoLimpeza* produto = new ProdutoLimpeza(
                    codigo, nome, preco, quantidade, validade, aroma);
                listaProdutos.push_back(produto);
            }
        }

        arquivo.close();
    }

    void salvarArquivo() {
        ofstream arquivo(nomeArquivo);

        if (!arquivo.is_open()) {
            cout << "Não foi possivel salvar os dados";
            return;
        }

        for (size_t i = 0; i < listaProdutos.size(); i++) {
            arquivo << listaProdutos[i]->serializar() << endl;
        }

        arquivo.close();
    }

    void limparBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    Estoque() {
        carregarArquivo();
    }

    ~Estoque() {
        salvarArquivo();

        for (size_t i = 0; i < listaProdutos.size(); i++) {
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
        for (size_t i = 0; i < listaProdutos.size(); i++) {
            cout << i << ". ";
            listaProdutos[i]->exibirDetalhes();
        }
    }

    int Pesquisar(string nome) {
        vector<int> indicesEncontrados;

        for (size_t i = 0; i < listaProdutos.size(); i++) {
            if (listaProdutos[i]->getNome() == nome) {
                indicesEncontrados.push_back(i);
            }
        }

        if (indicesEncontrados.empty()) {
            return -1;
        }

        if (indicesEncontrados.size() == 1) {
            return indicesEncontrados[0];
        }

        int escolhaUsuario = 0;
        cout << "Produtos encontrados com esse nome:\n";

        for (size_t i = 0; i < indicesEncontrados.size(); i++) {
            int indice = indicesEncontrados[i];
            cout << indice << ". "
                 << listaProdutos[indice]->getNome() << "\n";
        }

        cout << "Digite o numero do produto desejado: ";
        cin >> escolhaUsuario;

        for (size_t i = 0; i < indicesEncontrados.size(); i++) {
            if (indicesEncontrados[i] == escolhaUsuario) {
                return escolhaUsuario;
            }
        }

        cout << "Opcao Invalida! \n";
        return -1;
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

        int indice = Pesquisar(nomeProduto);
        if (indice != -1) {
            listaProdutos[indice]->exibirDetalhes();
        }
        else {
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
        cout << "Produto selecionado: "
             << listaProdutos[indice]->getNome()
             << " (Estoque: "
             << listaProdutos[indice]->getQtdEstoque() << ")\n";
        cout << "1. Repor Estoque \n";
        cout << "2. Dar Baixa no Estoque\n";
        cout << "3. Alterar Preco \n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (opcao == 1) {
            int quantidade;
            cout << "Quantidade a adicionar: ";
            cin >> quantidade;
            listaProdutos[indice]->reporEstoque(quantidade);
            cout << "Estoque adicionado com sucesso\n";
        }
        else if (opcao == 2) {
            int quantidade;
            cout << "Quantidade a retirar: ";
            cin >> quantidade;

            if (listaProdutos[indice]->darBaixaEstoque(quantidade)) {
                cout << "Estoque retirado com sucesso\n";
            }
            else {
                cout << "Estoque insuficiente\n";
            }
        }
        else if (opcao == 3) {
            float preco;
            cout << "Novo preco do produto: ";
            cin >> preco;
            listaProdutos[indice]->setPreco(preco);
            cout << "Preco atualizado com sucesso\n";
        }
        else {
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

        int indice = Pesquisar(nome);
        if (indice == -1) {
            cout << "Produto nao encontrado\n";
            return;
        }

        delete listaProdutos[indice];
        listaProdutos.erase(listaProdutos.begin() + indice);
        cout << "Produto retirado com sucesso\n";
    }

    void exibirRelatorio() {
        if (listaProdutos.empty()) {
            cout << "Nao ha produtos cadastrados" << endl;
            return;
        }

        int totalUnidadesEstoque = 0;
        double valorTotalPatrimonio = 0;

        for (size_t i = 0; i < listaProdutos.size(); i++) {
            totalUnidadesEstoque += listaProdutos[i]->getQtdEstoque();
            valorTotalPatrimonio += listaProdutos[i]->getQtdEstoque()
                                  * listaProdutos[i]->getPreco();
        }

        cout << "----------RELATORIO ESTATISTICO----------" << endl;
        cout << "Total de produtos = " << listaProdutos.size() << endl;
        cout << "Total de unidades em estoque = "
             << totalUnidadesEstoque << endl;
        cout << "Valor total do patrimonio = "
             << valorTotalPatrimonio << endl;
    }
};
