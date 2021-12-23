#pragma once

#include <iostream>
#include <string>

using namespace std;

class Operatie {
private:
    double op1;
    double op2;
    string semn;
public:
    //CONSTRUCTORI
    Operatie() {
        op1 = 0;
        op2 = 0;
        semn = "";
    }

    Operatie(double a, double b, string s) {
        op1 = a;
        op2 = b;
        semn = s;
    }
    //SUPRAINCARCARE OPERATORI
    Operatie operator+(const Operatie& o)
    {
        Operatie c = *this;
        c.op1 += o.op1;
        c.op2 += o.op2;
        return c;
    }

    Operatie operator-(const Operatie& o)
    {
        Operatie c = *this;
        c.op1 -= o.op1;
        c.op2 -= o.op2;
        return c;
    }

    Operatie operator*(const Operatie& o)
    {
        Operatie c = *this;
        c.op1 *= o.op1;
        c.op2 *= o.op2;
        return c;
    }

    Operatie operator/(const Operatie& o)
    {
        Operatie c = *this;
        c.op1 /= o.op1;
        c.op2 /= o.op2;
        return c;
    }

    //GETTERS SI SETTERS

    double getOp1()
    {
        return op1;
    }

    double getOp2()
    {
        return op2;
    }

    string getSemn()
    {
        return semn;
    }

    void setOp1(double x)
    {
        op1 = x;
    }

    void setOp2(double x)
    {
        op2 = x;
    }

    void setSemn(char s)
    {
        if (strchr("+-*/#^", s))
            semn = string(1, s);
    }

    //FUNCTII
    double putere() {
        return pow(op1, op2);
    }

    double radical() {
        return pow(op1, 1.0 / op2);
    }

    double impartire() {
        if (op2 != 0)
            return op1 / op2;
        else throw exception("impartire la 0");

    }

    double result() {
        if (semn == "#")
            return radical();
        else if (semn == "^")
            return putere();
        else if (semn == "*")
            return op1 * op2;
        else if (semn == "/")
            return impartire();
        else if (semn == "+")
            return op1 + op2;
        else if (semn == "-")
            return op1 - op2;
    }

    friend istream& operator>>(istream& in, Operatie& c);
    friend ostream& operator<<(ostream& out, Operatie c);
};

class Expresie {
private:
    string expresie;
public:
    //CONSTRUCTORI
    Expresie() {
        expresie = "";
    }

    Expresie(string s)
    {
        expresie = s;
    }

    //GETTERS SI SETTERS
    string getExpresie() {
        return expresie;
    }

    void setExpresie(string s)
    {
        expresie = s;
    }

    //SUPRAINCARCARE OPERATORI
    bool operator<(Expresie e)
    {
        if (this->expresie.length() < e.expresie.length())
            return true;
        else
            return false;
    }

    bool operator>=(Expresie e)
    {
        if (this->expresie.length() >= e.expresie.length())
            return true;
        else
            return false;
    }
    bool operator>(Expresie e)
    {
        if (this->expresie.length() > e.expresie.length())
            return true;
        else
            return false;
    }

    bool operator<=(Expresie e)
    {
        if (this->expresie.length() <= e.expresie.length())
            return true;
        else
            return false;
    }

    bool operator==(Expresie e)
    {
        if (this->expresie.length() == e.expresie.length())
            return true;
        else
            return false;
    }

    //FUNCTII
    //daca dir este > 0 cauta in dreapta, iar daca este < 0, atunci cauta in stanga
    int nr_cifre(int index, int dir)
    {
        int k = 0;
        int i;
        if (dir < 0)
        {
            for (i = index - 1; i >= 0 && strchr("0123456789.", expresie[i]); i--)
                k++;
        }
        else
        {
            for (i = index + 1; i < expresie.length() && strchr("0123456789.", expresie[i]); i++)
                k++;
        }
        return k;
    }
    //verifica daca exista paranteze [] sau ()
    bool has_brackets(string type)
    {
        if(expresie.find(type) != -1)
            return true;
        else
            return false;
    }

    //preia expresia din paranteze
    string get_brackets(string type_open)
    {
        string type_close;
        if (type_open == "[")
            type_close = "]";
        else
            type_close = ")";
        int op = expresie.find(type_open);
        int cl = expresie.find(type_close);

        return expresie.substr(op + 1, cl-op-1);
    }

    //transforma operatia elementara in obiect Operatie pentru prelucrare
    void prelucrare_op(char semn, int poz)
    {
        Operatie* o = new Operatie();
        string strrez;
            if (o != nullptr)
                delete o;
            int nrcifa = nr_cifre(poz, -1);
            int nrcifb = nr_cifre(poz, 1);
            string suba = expresie.substr(poz - nrcifa, nrcifa);
            string subb = expresie.substr(poz + 1, nrcifb);
            string subsemn = expresie.substr(poz, 1);
            double a = stod(suba);
            double b = stod(subb);
            o = new Operatie(a, b, subsemn);
            try
            {
                strrez = to_string(o->result());
                expresie.replace(poz - nrcifa, nrcifa + nrcifb + 1, strrez);
            }
            catch (exception e)
            {
                cout << "Impartire la 0!";
            }
  
    }
    
    //calculeaza o expresie elementara (fara paranteze) respectand ordinea operatiilor
    double calc() {
        for (int i = 0; i < expresie.length(); i++)
            if (expresie[i] == '#' || expresie[i] == '^')
                prelucrare_op(expresie[i], i);
        for (int i = 0; i < expresie.length(); i++)
            if (expresie[i] == '*' || expresie[i] == '/')
                prelucrare_op(expresie[i], i);
        for (int i = 0; i < expresie.length(); i++)
            if (expresie[i] == '+' || expresie[i] == '-')
                prelucrare_op(expresie[i], i);
        return stod(expresie);
    }

    friend istream& operator>>(istream& in, Expresie& c);
    friend ostream& operator<<(ostream& out, Expresie c);
};

class Calculator {
private:
    Expresie exp; //folosit pentru a memoria expresia initiala
    double rez; // folosit pentru a memora rezultatul
    double* sol; //vector alocat dinamic care memoreaza istoricul solutiilor
    int nrSol; //nr solutiilor din vectorul sol
    char* mesaj; //Mesaj de informare pentru calculator

    const string numeModel; //Denumire model calculator
    static int nrCalc; //Numarul de expresii calculate de toate calculatoarele in timpul programului
public:
    Calculator(): numeModel("N/A")
    {
        rez = -1;
        sol = nullptr;
        nrSol = 0;
        mesaj = nullptr;
    }

    Calculator(string expresie) : numeModel("N/A")
    {
        this->exp.setExpresie(expresie);
        rez = -1;
        sol = nullptr;
        nrSol = 0;
        mesaj = nullptr;
    }

    Calculator(string expresie, string denumire) : numeModel(denumire)
    {
        rez = -1;
        sol = nullptr;
        nrSol = 0;
        mesaj = nullptr;
        this->exp.setExpresie(expresie);
    }

    Calculator(const Calculator& c) : numeModel(c.numeModel)
    {
        rez = c.rez;
        exp = c.exp;
        nrSol = c.nrSol;
        if (c.sol != nullptr)
        {
            sol = new double[nrSol];
            for (int i = 0; i < nrSol; i++)
                sol[i] = c.sol[i];
        }
        else
            sol = nullptr;
        if (c.mesaj != nullptr)
        {
            mesaj = new char[strlen(c.mesaj) + 1];
            strcpy_s(mesaj, strlen(c.mesaj) + 1, c.mesaj);
        }
        else
            mesaj =  nullptr;
    }

    //GETTERS SI SETTERS
    double getRez()
    {
        return rez;
    }

    void setExp(Expresie e)
    {
        exp = e;
    }

    Expresie getExp()
    {
        return exp;
    }

    int getNrSol()
    {
        return nrSol;
    }

    void setNrSol(int n)
    {
        if (n >= 0)
        {
            nrSol = n;
        }
    }

    double* getSol()
    {
        if (sol != nullptr)
        {
            double* c;
            c = new double[nrSol];
            for (int i = 0; i < nrSol; i++)
                c[i] = sol[i];
            return c;
        }

        else
            return nullptr;
    }

    void setSol(double* c, int n)
    {
        if (sol != nullptr)
        {
            delete[] sol;
        }
        nrSol = n;
        sol = new double[nrSol];
        for (int i = 0; i < nrSol; i++)
            sol[i] = c[i];
    }

    char* getMesaj()
    {
        if (mesaj != nullptr)
        {
            char* c = new char[strlen(mesaj) + 1];
            strcpy_s(c, strlen(mesaj) + 1, mesaj);
            return c;
        }
        else
            return nullptr;
    }

    void setMesaj(const char* s)
    {
        if (s != nullptr)
        {
            if (mesaj != nullptr)
                delete[] mesaj;
            mesaj = new char[strlen(s) + 1];
            strcpy_s(mesaj, strlen(s) + 1, s);
        }
    }

    //FUNCTII

    //adauga o solutie noua in vectorul de solutii
    void addsol(double n)
    {
        double* c;
        if (sol != nullptr)
        {
            c = new double[nrSol];
            for (int i = 0; i < nrSol; i++)
                c[i] = sol[i];
            delete[] sol;
        }
        nrSol++;
        sol = new double[nrSol];
        for (int i = 1; i < nrSol - 1; i++)
            sol[i] = c[i];
        sol[nrSol - 1] = n;
    }

    //Incrementeaza nrCalc cu o unitate
    static void addNrCalc()
    {
        nrCalc++;
    }

    static int getNrCalc()
    {
        return nrCalc;
    }

    //rezolva parantezele
    void resolve_brackets(string type_open)
    {
        Expresie exp2;
        string type_close;
        if (type_open == "[")
            type_close = "]";
        else
            type_close = ")";

        while (exp.has_brackets(type_open))
        {
            exp2.setExpresie(exp.get_brackets(type_open));
            exp2.calc();
            string cexpresie = exp.getExpresie();
            int op = cexpresie.find(type_open);
            int cl = cexpresie.find(type_close);
            cexpresie.replace(op, cl - op + 1, exp2.getExpresie());
            exp.setExpresie(cexpresie);
        }
    }

    //functia principala de calcul a expresiei primite ca input
    void calc() {
        resolve_brackets("(");
        resolve_brackets("[");
        rez = exp.calc();
    }

    //SUPRAINCARCARE OPERATORI
    Calculator& operator=(const Calculator& c)
    {
        if (mesaj != nullptr)
            delete[] mesaj;
        if (sol != nullptr)
            delete[] mesaj;

        rez = c.rez;
        exp = c.exp;
        nrSol = c.nrSol;
        if (c.sol != nullptr)
        {
            sol = new double[nrSol];
            for (int i = 0; i < nrSol; i++)
                sol[i] = c.sol[i];
        }
        else
            sol = nullptr;
        if (c.mesaj != nullptr)
        {
            mesaj = new char[strlen(c.mesaj) + 1];
            strcpy_s(mesaj, strlen(c.mesaj) + 1, c.mesaj);
        }
        else
            mesaj = nullptr;

        return *this;
    }

    double operator[](int i)
    {
        if (i >= 0 && i < nrSol)
            return sol[i];
    }

    operator Expresie()
    {
        return exp;
    }

    ~Calculator() {
        if (mesaj != nullptr)
            delete[] mesaj;
        if (sol != nullptr)
            delete[] mesaj;
    }

    friend istream& operator>>(istream& in, Calculator& c);
    friend ostream& operator<<(ostream& out, Calculator c);
};


//SUPRAINCARCARE OPERATORI >> SI <<
inline istream& operator>>(istream& in, Calculator& c)
{
    in >> c.exp;
    cout << "Introduceti numarul de elemente din vectorul de solutii generate de calculator: " << endl;
    in >> c.nrSol;
    if (c.nrSol > 0)
    {
        if (c.sol != nullptr)
            delete[] c.sol;

        c.sol = new double[c.nrSol];
        for (int i = 0; i < c.nrSol; i++)
        {
            cout << "Sol[" << i << "]= ";
            in >> c.sol[i];
        }
        c.rez = c.sol[c.nrSol - 1]; //adaugam in rezultat ultimul rezultat al calculatorului
    }
    else
    {
        c.sol = nullptr;
        c.rez = -1; //adaugam -1 pentru ca nu au mai existat rezultate
    }
    //nu are sens citirea c.mesaj de la tastatura deoarece se actualizeaza in main in functie de expresie
    return in;
}

inline ostream& operator<<(ostream& out, Calculator c)
{
    out << "Expresia curenta este: " << c.exp.getExpresie() << endl;
    out << "Ultimul rezultat a fost: " << c.rez << endl;
    if (c.sol != nullptr)
    {
        out << "Numarul solutiilor din istoric este: " << c.nrSol << endl;
        for (int i = 0; i < c.nrSol; i++)
            out << "Sol[" << i << "]= " << c.sol[i] << endl;
    }
    else
        out << "Calculatorul nu are solutii in istoric" << endl;
    if(c.mesaj != nullptr)
        out << "Ultimul mesaj afisat de calculator este: \"" << c.mesaj << "\"" << endl;
    out << "Modelul calculatorului este: " << c.numeModel << endl;
    return out;
}

inline istream& operator>>(istream& in, Expresie& e)
{
    char c;
    cout << "Introduceti expresia: ";
    c = getchar();
    getline(in, e.expresie);
    if (c != '\n')
        e.expresie.insert(0, 1, c);

    c = '\n';
    return in;
}

inline ostream& operator<<(ostream& out, Expresie e)
{
    out << "Expresia este: " << e.expresie << endl;
    return out;
}

inline istream& operator>>(istream& in, Operatie& o)
{
    cout << "Operandul 1: ";
    in >> o.op1;
    cout << "Operandul 2: ";
    in >> o.op2;
    cout << "Operator: ";
    in >> o.semn;
    return in;
}

inline ostream& operator<<(ostream& out, Operatie o)
{
    cout << "Operandul 1: ";
    out << o.op1;
    out << "Operandul 2: ";
    out << o.op2;
    out << "Operator: ";
    out << o.semn;
    return out;
}