#include <iostream>
#include <string>
using namespace std;
int pasar(const string &columnTitle) {
    int result = 0;
    for (char c : columnTitle) {
        int valorLetra = (c - 'A' + 1);
        result = result * 26 + valorLetra;
    }
    return result;
}
int main() {
    string s;
    cout << "Ingrese el título de columna (como Excel, ej: \"A\", \"ZY\", etc.): ";
    cin >> s;
    int numero = pasar(s);
    cout << "Número de columna correspondiente: " << numero << endl;
    return 0;
}