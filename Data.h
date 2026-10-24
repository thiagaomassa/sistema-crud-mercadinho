#pragma once


#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

class Data {
private:
    int dia;
    int mes;
    int ano;

public:
    
    Data() : dia(1), mes(1), ano(2026) {}

    
    Data(int d, int m, int a) : dia(d), mes(m), ano(a) {}

    // Gets
    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getAno() const { return ano; }

    // Sets
    void setDia(int d) { dia = d; }
    void setMes(int m) { mes = m; }
    void setAno(int a) { ano = a; }

    //"DD/MM/AAAA"
    std::string paraString() const {
        std::ostringstream oss;                                             //uso de IA para evitar o buffer overvlow com o OSS
        oss << std::setw(2) << std::setfill('0') << dia << "/"
            << std::setw(2) << std::setfill('0') << mes << "/"
            << ano;
        return oss.str();
    }

    void printData() const {
        std::cout << paraString() << std::endl;
    }
};

