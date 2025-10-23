#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;
class Vehiculo {
protected:
    string marca;
    string modelo;
    string placa;
    bool disponible;
    static string pad(const string &s, size_t width) {
        if (s.length() >= width) return string();
        return string(width - s.length(), ' ');
    }
public:
    Vehiculo(string m, string mod, string p) 
        : marca(m), modelo(mod), placa(p), disponible(true) {}   
    virtual ~Vehiculo() {}
    virtual string mostrarInformacion() const {
        string info = "│ Marca:      " + marca + pad(marca, 24) + "│\n";
        info += "│ Modelo:     " + modelo + pad(modelo, 24) + "│\n";
        info += "│ Placa:      " + placa + pad(placa, 24) + "│\n";
        info += "│ Disponible: " + string(disponible ? "Sí" : "No") + pad(string(disponible ? "Sí" : "No"), 22) + "│\n";
        return info;
    }
    string getPlaca() const { return placa; }
    bool estaDisponible() const { return disponible; }
    string getMarca() const { return marca; }
    string getModelo() const { return modelo; }
    void setDisponible(bool d) { disponible = d; }
    virtual string getTipo() const { return "Vehículo"; }
};
class Auto : public Vehiculo {
private:
    int capacidadPasajeros;
public:
    Auto(string m, string mod, string p, int cap) 
        : Vehiculo(m, mod, p), capacidadPasajeros(cap) {}
    string mostrarInformacion() const override {
        string info = Vehiculo::mostrarInformacion();
        info += "│ Tipo:       Auto" + pad(string("Auto"), 20) + "│\n";
        string cap = to_string(capacidadPasajeros);
        info += "│ Pasajeros:  " + cap + pad(cap, 23) + "│\n";
        return info;
    }
    int getCapacidadPasajeros() const { return capacidadPasajeros; }
    string getTipo() const override { return "Auto"; }
};
class Bicicleta : public Vehiculo {
private:
    string tipo; 
public:
    Bicicleta(string m, string mod, string p, string t) 
        : Vehiculo(m, mod, p), tipo(t) {}
    string mostrarInformacion() const override {
        string info = Vehiculo::mostrarInformacion();
        info += "│ Tipo:       Bicicleta" + pad(string("Bicicleta"), 14) + "│\n";
        info += "│ Categoría:  " + tipo + pad(tipo, 24) + "│\n";
        return info;
    }   
    string getTipoBicicleta() const { return tipo; } 
    string getTipo() const override { return "Bicicleta"; }
};
class SistemaAlquiler {
private:
    vector<shared_ptr<Vehiculo>> vehiculos;
public:
    void registrarVehiculo(shared_ptr<Vehiculo> v) {
        for (const auto& vehiculo : vehiculos) {
            if (vehiculo->getPlaca() == v->getPlaca()) {
                cout << "Error: Ya existe un vehículo con la placa " << v->getPlaca() << endl;
                return;
            }
        }
        vehiculos.push_back(v);
        cout << "Vehículo registrado exitosamente!" << endl;
    }
    bool alquilarVehiculo(string placa) {
        for (auto& vehiculo : vehiculos) {
            if (vehiculo->getPlaca() == placa) {
                if (vehiculo->estaDisponible()) {
                    vehiculo->setDisponible(false);
                    cout << "Vehículo alquilado exitosamente!" << endl;
                    return true;
                } else {
                    cout << "El vehículo no está disponible." << endl;
                    return false;
                }
            }
        }
        cout << "No se encontró un vehículo con esa placa." << endl;
        return false;
    }
    bool devolverVehiculo(string placa) {
        for (auto& vehiculo : vehiculos) {
            if (vehiculo->getPlaca() == placa) {
                if (!vehiculo->estaDisponible()) {
                    vehiculo->setDisponible(true);
                    cout << "Vehículo devuelto exitosamente!" << endl;
                    return true;
                } else {
                    cout << "El vehículo ya está disponible." << endl;
                    return false;
                }
            }
        }
        cout << "No se encontró un vehículo con esa placa." << endl;
        return false;
    }
    void mostrarVehiculosDisponibles() const {
        cout << "VEHÍCULOS DISPONIBLES PARA ALQUILER" << endl;
        bool hayDisponibles = false;
        for (const auto& vehiculo : vehiculos) {
            if (vehiculo->estaDisponible()) {
                cout << vehiculo->mostrarInformacion() << endl;
                hayDisponibles = true;
            }
        }    
        if (!hayDisponibles) {
            cout << "No hay vehículos disponibles en este momento.\n" << endl;
        }
    }
    void mostrarTodosLosVehiculos() const {
        cout << "VEHÍCULOS REGISTRADOS" << endl;
        if (vehiculos.empty()) {
            cout << "No hay vehículos registrados en el sistema.\n" << endl;
            return;
        }       
        for (const auto& vehiculo : vehiculos) {
            cout << vehiculo->mostrarInformacion() << endl;
        }
    }    
    int getTotalVehiculos() const { return vehiculos.size(); }
};
int main() {
    SistemaAlquiler sistema;
    int opcion;
    cout << "SISTEMA DE VEHÍCULOS" << endl;
    sistema.registrarVehiculo(make_shared<Auto>("Toyota", "Corolla", "ABC123", 5));
    sistema.registrarVehiculo(make_shared<Auto>("Honda", "Civic", "XYZ789", 5));
    sistema.registrarVehiculo(make_shared<Bicicleta>("Trek", "Mountain X", "BIC001", "Montaña"));
    sistema.registrarVehiculo(make_shared<Bicicleta>("Giant", "Road Pro", "BIC002", "Ruta"));
    do {
        cout << "MENÚ PRINCIPAL" << endl;
        cout << "1. Registrar nuevo vehículo" << endl;
        cout << "2. Alquilar vehículo" << endl;
        cout << "3. Devolver vehículo" << endl;
        cout << "4. Mostrar vehículos disponibles" << endl;
        cout << "5. Mostrar todos los vehículos" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        switch(opcion) {
            case 1: {
                int tipoVehiculo;
                cout << "\n¿Qué tipo de vehículo desea registrar?" << endl;
                cout << "1. Auto" << endl;
                cout << "2. Bicicleta" << endl;
                cout << "Opción: ";
                cin >> tipoVehiculo;
                string marca, modelo, placa;
                cout << "Ingrese marca: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, marca);
                cout << "Ingrese modelo: ";
                getline(cin, modelo);
                cout << "Ingrese placa: ";
                getline(cin, placa);
                if (tipoVehiculo == 1) {
                    int capacidad;
                    cout << "Ingrese capacidad de pasajeros: ";
                    cin >> capacidad;
                    sistema.registrarVehiculo(make_shared<Auto>(marca, modelo, placa, capacidad));
                } else if (tipoVehiculo == 2) {
                    string tipo;
                    cout << "Ingrese tipo (Montaña/Ruta/Urbana): ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, tipo);
                    sistema.registrarVehiculo(make_shared<Bicicleta>(marca, modelo, placa, tipo));
                } else {
                    cout << "Opción inválida." << endl;
                }
                break;
            }
            case 2: {
                string placa;
                cout << "Ingrese la placa del vehículo a alquilar: ";
                cin >> placa;
                sistema.alquilarVehiculo(placa);
                break;
            }
            case 3: {
                string placa;
                cout << "Ingrese la placa del vehículo a devolver: ";
                cin >> placa;
                sistema.devolverVehiculo(placa);
                break;
            }
            case 4:
                sistema.mostrarVehiculosDisponibles();
                break;
            case 5:
                sistema.mostrarTodosLosVehiculos();
                break;
            case 0:
                cout << "\n¡Gracias por usar el sistema! 👋\n" << endl;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
        }
    } while(opcion != 0);   
    return 0;
}