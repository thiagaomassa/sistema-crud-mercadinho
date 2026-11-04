#include <iostream>
#include <limits>
#include <string>
#include "Data.h"
#include "Produto.h"
#include "ProdutoAlimento.h"
#include "ProdutoLimpeza.h"
#include "Estoque.h"

using namespace std;

void limparBuffer() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int opcao = 0;
    Estoque estoque;

    do {
        system("clear");
        cout << "\n====================================\n";
        cout << "      SISTEMA DE ESTOQUE - MERCADINHO\n";
        cout << "====================================\n";
        cout << "1. Cadastrar Novo Produto\n";
        cout << "2. Listar Todos os Produtos\n";
        cout << "3. Exibir Detalhes de um Produto\n";
        cout << "4. Alterar Produto (Repor/Baixa/Preco)\n";
        cout << "5. Remover Produto\n";
        cout << "6. Exibir Relatorio Estatistico\n";
        cout << "7. Sair\n";
        cout << "Escolha uma opcao: ";

        if (!(cin >> opcao)) {
            cout << "Entrada invalida! Digite um numero.\n";
            limparBuffer();
            continue;
        }

        switch (opcao) {
            case 1: {
                int cod, qtd, d, m, a, tipo;
                string nome;
                double preco;

                while (true){               
                cout << "Codigo: ";
                if (!(cin >> cod)) {
                cout << "Entrada invalida! Digite um numero.\n";
                limparBuffer();
                continue;
                }

                if (estoque.codigoExiste(cod)) {
                    cout << "Erro: Ja existe um produto com o codigo " << cod << "! Tente outro.\n";
                    continue;
                }

                break; // Codigo valido e unico
                }

                cout << "Nome: ";
                cin.ignore();
                getline(cin, nome);
                cout << "Preco: ";
                cin >> preco;
                cout << "Quantidade: ";
                cin >> qtd;
                while (true) {
                    cout << "Validade (Dia Mes Ano): ";
                    if (!(cin >> d >> m >> a)) {
                        cout << "Entrada invalida! Digite dia, mes e ano com numeros.\n";
                        limparBuffer();
                        continue;
                    }
                    if (!Data::ehValida(d, m, a)) {
                        cout << "Data invalida! Digite uma data existente.\n";
                        continue;
                    }
                    break;
                }

                Data validade(d, m, a);

                cout << "Tipo do produto (1-Alimento, 2-Limpeza): ";
                cin >> tipo;

                if (tipo == 1) {
                    double temp;
                    cout << "Temperatura de conservacao: ";
                    cin >> temp;

                    ProdutoAlimento* pAlimento = new ProdutoAlimento(
                        cod, nome, preco, qtd, validade, temp);
                    estoque.Inserir(pAlimento);
                }
                else if (tipo == 2) {
                    string aroma;
                    cout << "Aroma: ";
                    cin.ignore();
                    getline(cin, aroma);

                    ProdutoLimpeza* pLimpeza = new ProdutoLimpeza(
                        cod, nome, preco, qtd, validade, aroma);
                    estoque.Inserir(pLimpeza);
                }
                break;
            }

            case 2: {
                int a = 0;
                while (a != 1) {
                    system("clear");
                    estoque.ListarTodos();
                    cout << "1 - Sair: ";
                    cin >> a;
                }
                break;
            }
            case 3: {
                int a = 0;
                while (a != 1) {
                    system("clear");
                    estoque.exibirUm();
                    cout << "1 - Sair" << endl
                         << "2 - Exibir outro Produto" << endl
                         << "Digite: ";
                    cin >> a;
                }
                break;
            }
            case 4: {
                int a = 0;
                while (a != 1) {
                    system("clear");
                    estoque.Alterar();
                    cout << "1 - Sair" << endl
                         << "2 - Alterar outro Produto" << endl
                         << "Digite: ";
                    cin >> a;
                }
                break;
            }
            case 5: {
                int a = 0;
                while (a != 1) {
                    system("clear");
                    estoque.Remover();
                    cout << "1 - Sair" << endl
                         << "2 - Remover outro Produto" << endl
                         << "Digite: ";
                    cin >> a;
                }
                break;
            }
            case 6: {
                int a = 0;
                while (a != 1) {
                    system("clear");
                    estoque.exibirRelatorio();
                    cout << "1 - Sair" << endl << "Digite: ";
                    cin >> a;
                }
                break;
            }
            case 7: {
                cout << "Salvando dados e encerrando o sistema...\n";
                break;
            }

            default:
                cout << "Opcao invalida!\n";
                break;
        }
    } while(opcao != 7);

    return 0;
}
