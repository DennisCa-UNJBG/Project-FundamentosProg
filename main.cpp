#include <iostream>
#include "json.hpp" // ruta relativa, se movio la libreria fuera de su carpeta para un mejor uso
//#include "json-develop\single_include\nlohmann\json.hpp" // ruta relativa dentro de la carpeta del proyecto de la libreria
#include <fstream>

using json = nlohmann::json;
using namespace std;

// categoria de los libros
                        // 0              1          2             3        4
string catBooks[] = {"Ciencia Ficcion", "Drama", "Ramantica", "Cuento", "Novela"};

// lista de trofeos disponibles
                        //0                             1
string trofeos[] = {"Lector de Ciencia Ficcion", "Lector de Drama", 
                        // 2                    3               4
                "Lector de Ramantica", "Lector de Cuento", "Lector de Novela"};


int main(){
    // leer datos de los libros disponibles
    ifstream fileBooks("./data/booksData.json");

    // leer datos de los usuarios existentes
    ifstream fileUser("./data/userData.json");

    // pasar los datos a objetos(variables) para trabajar
    json booksData = json::parse(fileBooks);
    json userData = json::parse(fileUser);

    // mostrar los datos obtenidos de los liros y usuarios
    cout << booksData.dump(1, '\t') << "\n\n";
    cout << userData.dump(1, '\t') << "\n\n"<< endl;

    /* mostrar datos precisos de un usuario */
    
    // mostrar todos los datos del usuario it54816518
    cout << userData.at("it54816518") << "\n" <<
            // mostrar solo el DNI del usuario
            userData.at("it54816518").at("dni") << "\n" <<
            // mostrar solo los libros leidos por el usuario
            userData.at("it54816518").at("booksRead") << endl;
    
    /* mostrar datos precisos de un usuario */
    // mostrar todos los datos del libro li0001
    cout << booksData.at("li0001") << "\n" <<
            // mostrar solo el genero del libro
            booksData.at("li0001").at("Genero") << "\n" <<
            // mostrar solo el nombre del libro
            booksData.at("li0001").at("Nombre") << endl;

    // imprimir una categoria de libros
    cout << catBooks[0];

    // guardar nuevamente los datos JSON
    ofstream save_books("./data/booksData.json");
    save_books << booksData.dump(1, '\t');
    ofstream save_user("./data/userData.json");
    save_user << userData.dump(1, '\t');

    //system("pause");
    return 0;
}