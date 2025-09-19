#include<iostream>
#include<cmath>
using namespace std;
int main(){
    std::cout << "Ingrese un numero: " << std::endl;
    int numero;
    std::cin >> numero;
    std::cout << "Ingresa otro numero: " << std::endl;
    int numero2;
    std::cin >> numero2;
    int cociente= numero/numero2;
    int residuo= numero%numero2;
    while (residuo!=0){
        numero=numero2;
        numero2=residuo;
        cociente=numero/numero2;
        residuo=numero%numero2;
    }
    cout << "El máximo común divisor es: " << numero2 << endl;
    return 0;
}