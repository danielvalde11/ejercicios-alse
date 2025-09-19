#include <iostream>
using namespace std;
int main(){
    cout<<"Cuantos numeros va a ingresar?"<<endl;
    int n;
    cin>>n;
    int arreglo[n];
    for(int i=0;i<n;i++){
        cout<<"Ingrese un numero: "<<endl;
        cin>>arreglo[i];
    }
    int suma=0;
    for(int i=0;i<n;i++){
        suma+=arreglo[i];
    }
    cout<<"La suma de los numeros es: "<<suma<<endl;
    return 0;
}
