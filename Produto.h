#ifndef PRODUTO_H
#define PRODUTO_H

#include <iostream>
#include <string>
#include "Data.h"

class Produto {
protected:
    int codigo;
    std::string nome;
    double preco;
    int qtdestoque; 
    Data validade;

public:
    // C
    Produto(int cod, const std::string& n, double p, int qtd, const Data& v)
        : codigo(cod), nome(n), preco(p), qtdestoque(qtd), validade(v) {}
    // Dv
    virtual ~Produto() {}

    // Gets
    int getCodigo() const { return codigo; }
    std::string getNome() const { return nome; }
    double getPreco() const { return preco; }
    int getQtdEstoque() const { return qtdestoque; }
    Data getValidade() const { return validade; }

    // Sets
    void setNome(const std::string& n) { nome = n; }
    void setPreco(double p) { preco = p; }
    void setQtdEstoque(int qtd) { qtdestoque = qtd; }
    void setValidade(const Data& v) { validade = v; }

    void reporEstoque(int qtd) { 
        qtdestoque += qtd; 
    }

    bool darBaixaEstoque(int qtd) {
        if (qtd <= qtdestoque) {
            qtdestoque -= qtd;
            return true;
        }
        return false;
    }

    // polimorfismo
    virtual void exibirDetalhes() const = 0;
    virtual std::string getTipo() const = 0;
    virtual std::string serializar() const = 0;
};

#endif