#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cout << "Ingrese el número de días: ";
    cin >> n;
    vector<int> precios(n);
    cout << "Ingrese los precios de cada día: ";
    for (int i = 0; i < n; i++) {
        cin >> precios[i];
    }
    int minPrecio = precios[0];
    int maxGanancia = 0;
    int diaCompraTemp = 0; 
    int diaCompra = 0;     
    int diaVenta = 0;     
    for (int i = 1; i < n; i++) {
        if (precios[i] - minPrecio > maxGanancia) {
            maxGanancia = precios[i] - minPrecio;
            diaCompra = diaCompraTemp;
            diaVenta = i;
        }
        if (precios[i] < minPrecio) {
            minPrecio = precios[i];
            diaCompraTemp = i;
        }
    }
    if (maxGanancia > 0) {
        cout << "Mejor día para comprar: Día " << diaCompra + 1 << endl;
        cout << "Mejor día para vender: Día " << diaVenta + 1 << endl;
        cout << "Ganancia máxima: " << maxGanancia << endl;
    } else {
        cout << "No hay ganancia posible." << endl;
    }
    return 0;
}