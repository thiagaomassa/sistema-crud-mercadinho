#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "Data.h"
#include "Produto.h"
#include "ProdutoAlimento.h"
#include "ProdutoLimpeza.h"
#include "Estoque.h"

using namespace std;

//limpar o buffer do teclado
void limparBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int opcao = 0;
    Estoque estoque;

    do {
    cout << "\n====================================\n";
    cout << "      SISTEMA DE ESTOQUE - MERCADINHO     \n";
    cout << "====================================\n";
    cout << "1. Cadastrar Novo Produto\n";
    cout << "2. Listar Todos os Produtos\n";
    cout << "3. Exibir Detalhes de um Produto\n";
    cout << "4. Alterar Produto (Repor/Baixa/Preco)\n";
    cout << "5. Remover Produto\n";
    cout << "6. Exibir Relatorio Estatistico\n";
    cout << "7. Sair\n";
    cout << "Escolha uma opcao: ";
        
        if (!(std::cin >> opcao)) {
            std::cout << "Entrada invalida! Digite um numero.\n";
            limparBuffer();
            continue;
        }

        switch (opcao) {
            case 1: {
                int cod, qtd, d, m, a, tipo;
                string nome;
                double preco;

                cout << "Codigo: "; 
                cin >> cod;
                cout << "Nome: "; 
                cin.ignore();
                getline(std::cin, nome);
                cout << "Preco: ";
                cin >> preco;
                cout << "Quantidade: ";
                cin >> qtd;
                cout << "Validade (Dia Mes Ano): ";
                cin >> d >> m >> a;

                Data validade(d, m, a); 

                cout << "Tipo do produto (1-Alimento, 2-Limpeza): ";
                cin >> tipo;

                if (tipo == 1) {
                    double temp;
                    cout << "Temperatura de conservacao: "; std::cin >> temp;
                    
                
                    ProdutoAlimento* pAlimento = new ProdutoAlimento(cod, nome, preco, qtd, validade, temp);
                    estoque.Inserir(pAlimento); 

                } else if (tipo == 2) {
                    string aroma;
                    cout << "Aroma: ";
                    cin.ignore(); 
                    getline(std::cin, aroma);
                    
                
                    ProdutoLimpeza* pLimpeza = new ProdutoLimpeza(cod, nome, preco, qtd, validade, aroma);

                    estoque.Inserir(pLimpeza);
                }
                break;
            
            }

            case 2: {
                estoque.ListarTodos();
                break;
            }
            case 3: {
                estoque.exibirUm();
                break;
            }
            case 4: {
                estoque.Alterar();
                break; 
            }
            case 5: {
            estoque.Remover();
            break;  
            }
            case 6: {
                estoque.exibirRelatorio();
                break; 
            }
            case 7: {
                cout << "Salvando dados e encerrando o sistema...\n";
                break; 
            }
            default:
                std::cout << "Opcao invalida!\n";
                break;
        }
    } while (opcao != 7);
    return 0;
 }
