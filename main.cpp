#include <iostream>
#include "json.hpp" // ruta relativa, se movio la libreria fuera de su carpeta para un mejor uso
//#include "json-develop\single_include\nlohmann\json.hpp" // ruta relativa dentro de la carpeta del proyecto de la libreria
#include <fstream>

using json = nlohmann::json;
using namespace std;

int main(){
    ifstream archivo("prueba.json"); //lectura del archivo JSON
    json cargarData = json::parse(archivo); // almanenar los datos en una nueva variable declarada en la liberia "json.hpp"

    cout<<cargarData; // mostrar todos los datos del archivo JSON
    
    cout<< "\n";
    cout << cargarData.at("Anna") << endl; // mostrar solo los datos del objeto "Anna"
    cout << cargarData.at("Anna").at("age") << endl; // mostrar solo la edad del objeto "Anna"

    //system("pause");
    return 0;
}