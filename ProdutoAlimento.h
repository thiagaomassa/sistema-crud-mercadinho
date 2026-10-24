#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "Produto.h"

class ProdutoAlimento : public Produto{
    private:
        double tempCons; //temperatura de conservação do produto alimenticio

    public:
        ProdutoAlimento(int cod, const std::string& n, double p, int qtd, const Data& v, double temp)
        : Produto(cod, n, p, qtd, v), tempCons(temp) {}

    double getTemp() const {
        return tempCons; 
    }
    void setTemp(double temp) {
        tempCons = temp;
    }

    void exibirDetalhes() const override {
        std::cout << "[ALIMENTO] Codigo: " << codigo
                  << " | Nome: " << nome
                  << " | Preco: R$ " << preco
                  << " | Estoque: " << qtdestoque
                  << " | Validade: " << validade.paraString()
                  << " | Temp. Maxima: " << tempCons << "°C\n";
    }

    std::string getTipo() const override {
        return "ALIMENTO";
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
            << tempCons;
        return oss.str();
    }
    
};