#include "calculator.h"
#include <iostream>
#include <string>

using namespace std;

int Calculator::nrCalc = 0;

//FUNCTII VERIFICARE ECUATIE INTRODUSA DE LA TASTATURA

string sterge_spatii(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

bool verificare_paranteze(string str)
{
    int k_ptr_desc = 0;
    int k_ptr_inch = 0;
    int k_rot_desc = 0;
    int k_rot_inch = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '[')
            k_ptr_desc++;
        if (str[i] == ']')
            k_ptr_inch++;
        if (str[i] == '(')
            k_rot_desc++;
        if (str[i] == ')')
            k_rot_inch++;
    }
    if (k_ptr_desc != k_ptr_inch || k_rot_desc != k_rot_inch)
        return 0;
    else
        return 1;
}

bool valid_chars(string str)
{
    for (int i = 0; i < str.length(); i++)
        if (!strchr("0123456789.+-*/#^[]()", str[i]))
            return 0;
    return 1;
}

bool impartire_invalida(string str)
{
    if (strstr(str.c_str(), "/0") != nullptr)
        return true;
    else
        return false;
}

int main()
{
    string buffer;
    Calculator c("", "CASIO");
    Expresie e;
    cout.precision(15);
    cout << "Introduceti expresiile de calculat sau tastati exit pentru a iesi." << endl;
    cout << "Numerele negative se pot introduce cu paranteze (-5) sau fara paranteze -5" << endl;
    getline(cin, buffer);
    while (buffer != "exit")
    {
        buffer = sterge_spatii(buffer);
        while ((!valid_chars(buffer) || !verificare_paranteze(buffer) || impartire_invalida(buffer)) && buffer != "exit")
        {
            c.setMesaj("Expresie invalida! Introduceti o noua expresie:");
            cout << c.getMesaj() << endl;
            getline(cin, buffer);
            buffer = sterge_spatii(buffer);
        }
        if (buffer == "exit")
            break;
        e.setExpresie(buffer);
        c.setExp(e);
        c.calc();
        cout << c.getRez() << endl;
        Calculator::addNrCalc();
        getline(cin, buffer);
    }

    cout << "Numarul de expresii evaluate: " << Calculator::getNrCalc() << " expresii." << endl;
    return 0;
}