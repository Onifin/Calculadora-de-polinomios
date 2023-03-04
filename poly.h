#ifndef POLY_H_
#define POLY_H_
#include <string>

class Poly
{
    private:
        int grau;
        double *arr;
    public:
        Poly();
        Poly(int n);
        Poly(const Poly & P);
        ~Poly();

        void imprimir() const;
        void recriar(int novoGrau);
        bool empty()const;
        bool isZero()const;

        int getGrau()const;
        double getCoef(int COEF)const;
        double getValor(double x);

        void setCoef(int i, double novoValor);

        friend std::ostream& operator<<(std::ostream& X, const Poly& P);
        friend std::istream& operator>>(std::istream& X, Poly& P);

        Poly &operator=(const Poly & P);
        Poly &operator=(Poly && P);
        Poly operator+(const Poly & P) const;
        Poly operator-(const Poly & P) const;
        Poly operator-() const;
        Poly operator*(const Poly & P) const;
        double operator[](int i)const;
        double operator()(double x);

        void diminuirGrau();

        bool salvar(std::string nomeArq);
        bool ler(std::string nomeArq);

};

#endif
