#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

class Data {
private:
    int dia;
    int mes;
    int ano;

public:
    Data() : dia(1), mes(1), ano(2026) {}

    Data(int d, int m, int a) : dia(d), mes(m), ano(a) {}

    int getDia() const {
        return dia;
    }

    int getMes() const {
        return mes;
    }

    int getAno() const {
        return ano;
    }

    static bool ehValida(int d, int m, int a) {
        if (a < 1000 || a > 9999 || m < 1 || m > 12 || d < 1) {
            return false;
        }

        const int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return d <= diasPorMes[m - 1];
    }

    void setDia(int d) {
        if (d >= 1 && d <= 31) {
            dia = d;
        }
        else {
            cout << "Dia invalido" << endl;
        }
    }

    void setMes(int m) {
        if (m >= 1 && m <= 12) {
            mes = m;
        }
        else {
            cout << "Mes invalido" << endl;
        }
    }

    void setAno(int a) {
        if (a >= 1000 && a <= 9999) {
            ano = a;
        }
        else {
            cout << "Ano invalido" << endl;
        }
    }

    std::string paraString() const {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << dia << "/"
            << std::setw(2) << std::setfill('0') << mes << "/"
            << ano;
        return oss.str();
    }

    void printData() const {
        std::cout << paraString() << std::endl;
    }
};
