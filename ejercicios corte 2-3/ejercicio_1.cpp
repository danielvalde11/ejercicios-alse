#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class Libro {
private:
    string titulo;
    string autor;
    string isbn;
    bool disponible;
public:
    Libro(string t, string a, string i);
    string getTitulo() const;
    string getAutor() const;
    string getISBN() const;
    bool isDisponible() const;
    void setDisponible(bool d);
    void mostrarInfo() const;
};
class Biblioteca {
private:
    vector<Libro> libros;
public:
    Biblioteca();
    void agregarLibro(const Libro& libro);
    bool eliminarLibro(const string& isbn);
    void mostrarLibrosDisponibles() const;
    void mostrarTodosLosLibros() const;
    vector<Libro*> buscarPorTitulo(const string& titulo);
    vector<Libro*> buscarPorAutor(const string& autor);
    Libro* buscarPorISBN(const string& isbn);
};
Libro::Libro(string t, string a, string i) 
    : titulo(t), autor(a), isbn(i), disponible(true) {}
string Libro::getTitulo() const { return titulo; }
string Libro::getAutor() const { return autor; }
string Libro::getISBN() const { return isbn; }
bool Libro::isDisponible() const { return disponible; }
void Libro::setDisponible(bool d) { disponible = d; }
void Libro::mostrarInfo() const {
    cout << "Título: " << titulo << "\n";
    cout << "Autor: " << autor << "\n";
    cout << "ISBN: " << isbn << "\n";
    cout << "Estado: " << (disponible ? "Disponible" : "Prestado") << "\n";
}
Biblioteca::Biblioteca() {}
void Biblioteca::agregarLibro(const Libro& libro) {
    libros.push_back(libro);
    cout << "Libro agregado exitosamente!\n";
}
bool Biblioteca::eliminarLibro(const string& isbn) {
    for (auto it = libros.begin(); it != libros.end(); ++it) {
        if (it->getISBN() == isbn) {
            libros.erase(it);
            cout << "Libro eliminado exitosamente!\n";
            return true;
        }
    }
    cout << "Libro no encontrado.\n";
    return false;
}
void Biblioteca::mostrarLibrosDisponibles() const {
    cout << "LIBROS DISPONIBLES EN LA BIBLIOTECA\n";
    bool hayDisponibles = false;
    for (const auto& libro : libros) {
        if (libro.isDisponible()) {
            libro.mostrarInfo();
            hayDisponibles = true;
        }
    }   
    if (!hayDisponibles) {
        cout << "No hay libros disponibles.\n";
    }
}
void Biblioteca::mostrarTodosLosLibros() const {
    cout << "TODOS LOS LIBROS EN LA BIBLIOTECA\n";
    if (libros.empty()) {
        cout << "La biblioteca está vacía.\n";
        return;
    } 
    for (const auto& libro : libros) {
        libro.mostrarInfo();
    }
}
vector<Libro*> Biblioteca::buscarPorTitulo(const string& titulo) {
    vector<Libro*> resultados;
    for (auto& libro : libros) {
        if (libro.getTitulo().find(titulo) != string::npos) {
            resultados.push_back(&libro);
        }
    }
    return resultados;
}
vector<Libro*> Biblioteca::buscarPorAutor(const string& autor) {
    vector<Libro*> resultados;
    for (auto& libro : libros) {
        if (libro.getAutor().find(autor) != string::npos) {
            resultados.push_back(&libro);
        }
    }
    return resultados;
}
Libro* Biblioteca::buscarPorISBN(const string& isbn) {
    for (auto& libro : libros) {
        if (libro.getISBN() == isbn) {
            return &libro;
        }
    }
    return nullptr;
}
void mostrarMenu() {
    cout << "SISTEMA DE GESTIÓN DE BIBLIOTECA \n";
    cout << "1. Agregar libro\n";
    cout << "2. Eliminar libro\n";
    cout << "3. Buscar por título\n";
    cout << "4. Buscar por autor\n";
    cout << "5. Mostrar libros disponibles\n";
    cout << "6. Mostrar todos los libros\n";
    cout << "7. Cambiar disponibilidad\n";
    cout << "0. Salir\n";
    cout << "Opción: ";
}
int main() {
    Biblioteca biblioteca;
    int opcion;
    string titulo, autor, isbn, busqueda;
    biblioteca.agregarLibro(Libro("Cien años de soledad", "Gabriel García Márquez", "978-0307474728"));
    biblioteca.agregarLibro(Libro("Don Quijote de la Mancha", "Miguel de Cervantes", "978-8491050643"));
    biblioteca.agregarLibro(Libro("El Hobbit", "J.R.R. Tolkien", "978-0547928227"));
    do {
        mostrarMenu();
        if (!(cin >> opcion)) {
            cin.clear();
            string dummy;
            getline(cin, dummy);
            cout << "\n Entrada inválida. Ingresa un número.\n";
            continue;
        }
        cin.ignore();
        switch(opcion) {
            case 1: {
                cout << "\nTítulo: ";
                getline(cin, titulo);
                cout << "Autor: ";
                getline(cin, autor);
                cout << "ISBN: ";
                getline(cin, isbn);   
                biblioteca.agregarLibro(Libro(titulo, autor, isbn));
                break;
            }
            case 2: {
                cout << "\nISBN del libro a eliminar: ";
                getline(cin, isbn);
                biblioteca.eliminarLibro(isbn);
                break;
            }
            case 3: {
                cout << "\nTítulo a buscar: ";
                getline(cin, busqueda);
                auto resultados = biblioteca.buscarPorTitulo(busqueda);   
                if (resultados.empty()) {
                    cout << "No se encontraron libros.\n";
                } else {
                    cout << "\n Se encontraron " << resultados.size() << " libro(s):\n";
                    for (auto libro : resultados) {
                        libro->mostrarInfo();
                    }
                }
                break;
            }
            case 4: {
                cout << "\nAutor a buscar: ";
                getline(cin, busqueda);
                auto resultados = biblioteca.buscarPorAutor(busqueda);   
                if (resultados.empty()) {
                    cout << "No se encontraron libros.\n";
                } else {
                    cout << "\nSe encontraron " << resultados.size() << " libro(s):\n";
                    for (auto libro : resultados) {
                        libro->mostrarInfo();
                    }
                }
                break;
            }
            case 5:
                biblioteca.mostrarLibrosDisponibles();
                break;
            case 6:
                biblioteca.mostrarTodosLosLibros();
                break;
            case 7: {
                cout << "\nISBN del libro: ";
                getline(cin, isbn);
                Libro* libro = biblioteca.buscarPorISBN(isbn);   
                if (libro) {
                    libro->setDisponible(!libro->isDisponible());
                    cout << " Disponibilidad cambiada a: " 
                         << (libro->isDisponible() ? "Disponible" : "Prestado") << "\n";
                } else {
                    cout << " Libro no encontrado.\n";
                }
                break;
            }           
            case 0:
                cout << "\n¡Hasta pronto!\n";
                break;   
            default:
                cout << "\nOpción inválida.\n";
        }
    } while(opcion != 0);    
    return 0;
}