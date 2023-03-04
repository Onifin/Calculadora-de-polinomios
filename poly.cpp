#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include "poly.h"

using namespace std;

Poly::Poly():
    grau(-1), arr(nullptr)
{
}

Poly::Poly(int n):
    grau(n), arr(nullptr)
{
    arr = new double[grau + 1];
    if(grau == 0)
    {
        arr[0] = 0.0;
    }
    if(grau > 0)
    {


        for(int i = 0; i < grau; i++)
        {
            arr[i] = 0.0;
        }

        arr[grau] = 1.0;
    }
}

Poly::Poly(const Poly & P):
    grau(P.grau), arr(new double[P.grau + 1])
{
    for(int i = 0; i < P.grau + 1; i++)
    {
        arr[i] = P.arr[i];
    }
}

Poly::~Poly(){
    delete[] arr;
}
//Metodos get

int Poly::getGrau()const
{
    return(grau);
}

double Poly::getCoef(int COEF)const
{
    if(grau >= COEF && COEF >= 0)
    {
        return(arr[COEF]);
    }
    return(0.0);
}

double Poly::getValor(double x)
{
    if(empty())
    {
        return(0.0);
    }
    double soma = 0.0;

    for(int i = 0; i <= grau+1; i++)
    {
        soma = soma + getCoef(i)*pow(x, i);
    }
    return(soma);
}


//Recriar

void Poly::recriar(int novoGrau)
{
    delete[] arr;

    grau = novoGrau;

    if(novoGrau < 0)
    {
        arr = nullptr;
    }
    if(novoGrau == 0)
    {
        arr = new double[grau + 1];
        arr[0] = 0.0;
    }
    if(novoGrau > 0)
    {
        arr = new double[grau + 1];

        for(int i = 0; i < grau; i++)
        {
            arr[i] = 0.0;
        }

        arr[grau] = 1.0;
    }

}
// SOBRECARGA DO OPERADOR >>
istream& operator>>(istream& X, Poly& P)
{
    if(!P.empty())
    {
        if(P.grau != 0)
        {
            for(int i = P.grau; i >= 0; i--)
            {
                cout << "COEFICIENTE DE GRAU [" << i << "]: ";
                X >> P.arr[i];
            }
            while(P.arr[P.grau] == 0 && !P.isZero())
            {
                cout << "O VALOR DO MAIOR COEFICIENTE NAO PODE SER ZERO NESSE CASO, DIGITE NOVAMENTE O COEFICIENTE DE GRAU [" << P.grau << "]: ";
                X >> P.arr[P.grau];
            }
            return(X);
        }
        cout << "COEFICIENTE DE GRAU [" << 0 << "]: ";
        X >> P.arr[0];
        return(X);
    }
    cerr << "O POLINOMIO NAO PODE SER VAZIO";
    return(X);
}
// SOBRECARGA DO OPERADOR <<
ostream& operator<<(ostream& X, const Poly& P)
{
    if(P.grau >= 0)
    {
        for(int i = P.grau; i >= 0; i--)
        {
            if(P.arr[i] == 0.0)
            {
                if(i == 0 && P.grau == 0)
                {
                    X << P.arr[i];
                }
            }
            else
            {
                if(P.arr[i] < 0.0)
                {
                    X << "-";
                }
                else
                {
                    if(i != P.grau)
                    {
                        X << "+";
                    }
                }

                if(abs(P.arr[i]) != 1.0 || i == 0)
                {
                    X << abs(P.arr[i]);
                }

                if(i != 0)
                {
                    if(abs(P.arr[i]) != 1.0)
                    {
                        X << "*";
                    }
                    X << "x";

                    if(i > 1)
                    {
                        X << "^" << i;
                    }
                }
            }
        }
    }
    return(X);
}

//SOBRECARGA DO OPERADOR =

Poly& Poly::operator=(const Poly & P)
{
    if(this != &P)
    {
        delete[] arr;

        grau = P.grau;

        if(grau < 0){
            grau = -1;
            arr = nullptr;
        }else{
            arr = new double[P.grau + 1];

            for(int i = 0; i < P.grau + 1; i++)
            {
                arr[i] = P.arr[i];
            }
        }
    }

    return *this;
}

Poly& Poly::operator=(Poly && P){
    delete[] arr;
    grau = P.grau;
    arr = P.arr;
    P.grau = 0;
    P.arr = nullptr;

    return(*this);
}

// OPERADOR [] e ()

double Poly::operator[](int COEF)const
{
    return(getCoef(COEF));
}

double Poly::operator()(double x)
{
    return(getValor(x));
}
//Testes booleanos

bool Poly::empty() const
{
    return(grau < 0);
}

bool Poly::isZero() const
{
    return(grau == 0 && arr[0] == 0.0);
}
//SOBRECARGA DO OPERADOR +
Poly Poly::operator+(const Poly & P) const
{
    if(P.empty()) return *this;
    if(empty()) return P;
    if(P.isZero()) return *this;
    if(isZero()) return P;

    Poly aux(max(grau, P.grau));

    for(int i = 0; i <= aux.getGrau(); i++)
    {
        aux.arr[i] = getCoef(i) + P.getCoef(i);
    }

    aux.diminuirGrau();

    return aux;
}

//SOBRECARGA DO OPERADOR - BINARIO
Poly Poly::operator-(const Poly & P) const
{
    if(P.empty()) return *this;
    if(empty()) return -P;
    if(P.isZero()) return *this;
    if(isZero()) return -P;

    Poly aux(max(grau, P.grau));

    for(int i = 0; i <= aux.getGrau(); i++)
    {
        aux.arr[i] = getCoef(i) - P.getCoef(i);
    }

    aux.diminuirGrau();

    return aux;
}
//SOBRECARGA DO OPERADOR - UNARIO
Poly Poly::operator-() const
{
    if(empty()) return(*this);
    if(isZero()) return(*this);

    Poly aux(grau);

    for(int i = 0; i <= grau; i++){
        aux.arr[i] = (-1)*arr[i];
    }

    return(aux);
}
//SOBRECARGA DO OPERADOR *
Poly Poly::operator*(const Poly & P) const
{
    if(empty()) return *this;
    if(P.empty()) return P;
    if(isZero()) return *this;
    if(P.isZero()) return P;

    Poly aux(grau + P.grau);

    aux.arr[aux.grau] = 0.0;

    cout << aux;

    for(int i = 0; i <= grau; i++){
        for(int j = 0; j <= P.grau; j++){
            aux.arr[i+j] = aux.arr[i+j] + arr[i] * P.arr[j];
        }
    }
    return(aux);

}
//SET COEF

void Poly::setCoef(int i, double novoValor)
{
    if(grau >= i && !empty())
    {
        if(novoValor != 0.0 || i != grau || grau == 1)
        {
            arr[i] = novoValor;
        }
        else
        {
            cerr << "COEFICIENTE INVALIDO!" << endl;
        }
    }
    else
    {
        cerr << "COEFICIENTE INVALIDO!" << endl;
    }
}

//SALVAR EM ARQUIVO

bool Poly::salvar(std::string nomeArq)
{
    ofstream arquivo;

    arquivo.open(nomeArq);

    if(!arquivo.is_open())
    {
        arquivo.close();
        return(false);
    }

    arquivo << "POLY " << grau << endl;

    for(int i = 0; i <= grau; i++)
    {
        arquivo << arr[i] << " ";
    }

    arquivo.close();
    return(true);
}

bool Poly::ler(std::string nomeArq)
{
    string cabecalho;
    int GRAU;

    ifstream arquivo;
    arquivo.open(nomeArq);

    if(!arquivo.is_open())
    {
        arquivo.close();
        return(false);
    }

    arquivo >> cabecalho;

    if(cabecalho != "POLY" || !arquivo.good())
    {
        arquivo.close();
        return(false);
    }

    arquivo >> GRAU;

    if(!arquivo.good())
    {
        arquivo.close();
        return(false);
    }

    if(GRAU < 0)
    {
        arquivo.close();
        grau = GRAU;
        arr = nullptr;
        return(true);
    }

    Poly aux(GRAU);

    for(int i = 0; i <= GRAU; i++)
    {
        arquivo >> aux.arr[i];

        if(!arquivo.good()){
            arquivo.close();
            return(false);
        }
    }

    if(aux.arr[aux.grau] == 0.0 && aux.grau > 0){
        arquivo.close();
        return(false);
    }

    arquivo.close();
    *this = aux;
    return(true);

}

void Poly::diminuirGrau()
{
    int novoGrau = grau;

    while(novoGrau > 0 && arr[novoGrau] == 0.0){
        novoGrau--;
    }

    if(novoGrau == grau) return;

    Poly aux(novoGrau);

    for(int i = 0; i <= novoGrau; i++){
        aux.arr[i] = arr[i];
    }

    *this = aux;
}
