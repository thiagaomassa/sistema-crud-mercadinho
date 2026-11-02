#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>
#include "Data.h"

using namespace std;

class Produto {
protected:
    int codigo;
    string nome;
    double preco;
    int qtdestoque;
    Data validade;

public:
    Produto(int cod, const string& n, double p, int qtd, const Data& v)
        : codigo(cod), nome(n), preco(p), qtdestoque(qtd), validade(v) {}

    virtual ~Produto() {}

    int getCodigo() const {
        return codigo;
    }

    string getNome() const {
        return nome;
    }

    double getPreco() const {
        return preco;
    }

    int getQtdEstoque() const {
        return qtdestoque;
    }

    Data getValidade() const {
        return validade;
    }

    void setNome(const string& n) {
        nome = n;
    }

    void setPreco(double p) {
        preco = p;
    }

    void setQtdEstoque(int qtd) {
        qtdestoque = qtd;
    }

    void setValidade(const Data& v) {
        validade = v;
    }

    void reporEstoque(int qtd) {
        qtdestoque += qtd;
    }

    bool darBaixaEstoque(int qtd) {
        if (qtd <= qtdestoque) {
            qtdestoque -= qtd;
            return true;
        } else {
            return false;
        }
    }

    virtual void exibirDetalhes() const = 0;
    virtual string getTipo() const = 0;
    virtual string serializar() const = 0;
};

#endif
