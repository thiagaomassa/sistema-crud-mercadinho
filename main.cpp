#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "Data.h"
#include "Produto.h"
#include "ProdutoAlimento.h"

// Função auxiliar para limpar o buffer do teclado com segurança
void limparBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::vector<Produto*> listaProdutos;
    int opcao = 0;

    do {
        std::cout << "\n====================================\n";
        std::cout << "      PAINEL DE TESTE INTERATIVO     \n";
        std::cout << "====================================\n";
        std::cout << "1. Cadastrar Novo Alimento\n";
        std::cout << "2. Listar Todos os Produtos (Polimorfismo)\n";
        std::cout << "3. Repor Estoque de um Produto\n";
        std::cout << "4. Dar Baixa no Estoque (Venda)\n";
        std::cout << "5. Testar Serializacao (Linha para Arquivo)\n";
        std::cout << "6. Sair\n";
        std::cout << "Escolha uma opcao: ";
        
        if (!(std::cin >> opcao)) {
            std::cout << "Entrada invalida! Digite um numero.\n";
            limparBuffer();
            continue;
        }

        switch (opcao) {
            case 1: {
                int cod, qtd, d, m, a;
                std::string nome;
                double preco, temp;

                std::cout << "\n--- CADASTRAR ALIMENTO ---\n";
                std::cout << "Codigo: ";
                std::cin >> cod;
                limparBuffer();

                std::cout << "Nome do Produto: ";
                std::getline(std::cin, nome);

                std::cout << "Preco (R$): ";
                std::cin >> preco;

                std::cout << "Quantidade inicial em estoque: ";
                std::cin >> qtd;

                std::cout << "Validade (Dia Mes Ano separados por espaco): ";
                std::cin >> d >> m >> a;

                std::cout << "Temperatura de Conservacao (C): ";
                std::cin >> temp;

                // Instancia dinamicamente e guarda no vetor como Produto*
                listaProdutos.push_back(new ProdutoAlimento(cod, nome, preco, qtd, Data(d, m, a), temp));
                std::cout << "Produto cadastrado com sucesso!\n";
                break;
            }

            case 2: {
                std::cout << "\n--- LISTA DE PRODUTOS CADASTRADOS ---\n";
                if (listaProdutos.empty()) {
                    std::cout << "Nenhum produto cadastrado ate o momento.\n";
                } else {
                    for (size_t i = 0; i < listaProdutos.size(); ++i) {
                        std::cout << "[" << i << "] ";
                        // Chama o metodo polimorfico sobrescrito
                        listaProdutos[i]->exibirDetalhes();
                    }
                }
                break;
            }

            case 3: {
                std::cout << "\n--- REPOR ESTOQUE ---\n";
                if (listaProdutos.empty()) {
                    std::cout << "Nenhum produto cadastrado.\n";
                    break;
                }

                int codBusca, qtdAdicionar;
                std::cout << "Digite o codigo do produto: ";
                std::cin >> codBusca;

                bool achou = false;
                for (Produto* p : listaProdutos) {
                    if (p->getCodigo() == codBusca) {
                        std::cout << "Produto encontrado: " << p->getNome() 
                                  << " | Estoque atual: " << p->getQtdEstoque() << "\n";
                        std::cout << "Quantidade a adicionar: ";
                        std::cin >> qtdAdicionar;

                        p->reporEstoque(qtdAdicionar);
                        std::cout << "Estoque atualizado para: " << p->getQtdEstoque() << "\n";
                        achou = true;
                        break;
                    }
                }
                if (!achou) std::cout << "Produto com codigo " << codBusca << " nao encontrado.\n";
                break;
            }

            case 4: {
                std::cout << "\n--- DAR BAIXA NO ESTOQUE (VENDA) ---\n";
                if (listaProdutos.empty()) {
                    std::cout << "Nenhum produto cadastrado.\n";
                    break;
                }

                int codBusca, qtdRetirar;
                std::cout << "Digite o codigo do produto: ";
                std::cin >> codBusca;

                bool achou = false;
                for (Produto* p : listaProdutos) {
                    if (p->getCodigo() == codBusca) {
                        std::cout << "Produto: " << p->getNome() 
                                  << " | Estoque atual: " << p->getQtdEstoque() << "\n";
                        std::cout << "Quantidade a retirar: ";
                        std::cin >> qtdRetirar;

                        if (p->darBaixaEstoque(qtdRetirar)) {
                            std::cout << "Baixa efetuada! Novo saldo: " << p->getQtdEstoque() << "\n";
                        } else {
                            std::cout << "ERRO: Saldo insuficiente em estoque!\n";
                        }
                        achou = true;
                        break;
                    }
                }
                if (!achou) std::cout << "Produto nao encontrado.\n";
                break;
            }

            case 5: {
                std::cout << "\n--- VISUALIZAR SERIALIZACAO PARA ARQUIVO ---\n";
                if (listaProdutos.empty()) {
                    std::cout << "Nenhum produto cadastrado.\n";
                } else {
                    for (Produto* p : listaProdutos) {
                        std::cout << p->serializar() << "\n";
                    }
                }
                break;
            }

            case 6:
                std::cout << "\nLimpando memoria e encerrando...\n";
                break;

            default:
                std::cout << "Opcao invalida!\n";
                break;
        }

    } while (opcao != 6);

    // Liberacao de memoria dinamica (chama o virtual ~Produto())
    for (Produto* p : listaProdutos) {
        delete p;
    }
    listaProdutos.clear();

    return 0;
}