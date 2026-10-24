#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "Produto.h"

class ProdutoLimpeza : public Produto{
    private:
        std::string aroma;

    public:
        //c
        ProdutoLimpeza(int cod, const std::string& n, double p,int qtd, const Data& v, const std::string& ar):
        Produto(cod, n, p, qtd, v), aroma(ar){}

        std::string getAroma() const { return aroma; }
        void setAroma(const std::string& ar) { aroma = ar; }

        void exibirDetalhes() const override {
            std::cout << "[LIMPEZA]  Codigo: " << codigo
                    << " | Nome: " << nome
                    << " | Preco: R$ " << preco
                    << " | Estoque: " << qtdestoque
                    << " | Validade: " << validade.paraString()
                    << " | Aroma: " << aroma << "\n";
        }
        std::string getTipo() const override {
        
            return "LIMPEZA";
        
        }
        std::string serializar() const override {
            std::ostringstream oss;
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