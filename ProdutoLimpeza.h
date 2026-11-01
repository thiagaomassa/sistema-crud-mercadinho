#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "Produto.h"

class ProdutoLimpeza : public Produto{
    private:
        string aroma;

    public:
        //c
        ProdutoLimpeza(int cod, const string& n, double p,int qtd, const Data& v, const string& ar):
        Produto(cod, n, p, qtd, v), aroma(ar){}

        string getAroma() const { return aroma; }
        void setAroma(const string& ar) { aroma = ar; }

        void exibirDetalhes() const override {
            cout << "[LIMPEZA]  Codigo: " << codigo
                    << " | Nome: " << nome
                    << " | Preco: R$ " << preco
                    << " | Estoque: " << qtdestoque
                    << " | Validade: " << validade.paraString()
                    << " | Aroma: " << aroma << "\n";
        }
        string getTipo() const override {
        
            return "LIMPEZA";
        
        }
        string serializar() const override {
            ostringstream oss;
            oss << getTipo() << ";"
                << codigo << ";"
                << nome << ";"
                << preco << ";"
                << qtdestoque << ";"
                << validade.getDia() << ";"
                << validade.getMes() << ";"
                << validade.getAno() << ";"
                << aroma;
            return oss.str();
        }
};
