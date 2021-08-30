#include <iostream>
#include "json.hpp" // ruta relativa, se movio la libreria fuera de su carpeta para un mejor uso
#include <fstream> // leer y escribir en archivos

using json = nlohmann::json;
using namespace std;

int showMenu();
void saveData(json *booksData, json *userData);
void show_data(json *data);
void option_menu(int val, json *booksData, json *userData);
void show_ranking(json *booksData, json *userData);
void show_users(json *userData);


// categoria de los libros -> 0           1          2             3        4
string catBooks[] = {"Ciencia Ficcion", "Drama", "Ramantica", "Cuento", "Novela"};

// lista de trofeos disponibles -> 0                1                   2                    3                  4
string trofeos[] = {"Lector de Ciencia Ficcion", "Lector de Drama", "Lector de Ramantica", "Lector de Cuento", "Lector de Novela"};

//variable para finalizar el bucle del programa
bool start = true;

int main(){
    // leer datos de los libros disponibles
    ifstream fileBooks("./data/booksData.json");

    // leer datos de los usuarios existentes
    ifstream fileUser("./data/userData.json");

    // pasar los datos a objetos(variables) para trabajar
    json booksData = json::parse(fileBooks);
    json userData = json::parse(fileUser);
    
    while(start)
    {
        //show_data(&userData);
        int val_menu = showMenu();
        option_menu(val_menu, &booksData, &userData);  
    }
    
    //system("pause");
    return 0;
}

// mostrar menu
int showMenu()
{
    int i = 0;
    cout << "********************************" << endl;
    cout << "\tMENU" << endl;
    cout << "********************************" << endl;
    cout << "[1] Ingresar nuevo Usuario " << endl;
    cout << "[2] Visualizar lectores registrados " << endl;
    cout << "[3] Modificar datos del lector " << endl;
    cout << "[4] Imprimir el ranking de lectores " << endl;
    cout << "[5] Salir " << endl;
    cout << "Selecciones una opcion(numero): ";
    cin >> i;

    return i;
}

// guardar nuevamente los datos en los archivos JSON
void saveData(json *booksData, json *userData)
{
    ofstream save_books("./data/booksData.json");
    save_books << booksData->dump(1, '\t');
    ofstream save_user("./data/userData.json");
    save_user << userData->dump(1, '\t');
}

// mostrar datos sin procesar
void show_data(json *data)
{
    cout << data->dump(1, '\t') << "\n\n"<< endl;
}

// procesar las opciones del menu
void option_menu(int val, json *booksData, json *userData)
{   
    switch (val)
    {
        case 1:
            system("cls");
            cout << "\n\nEn proceso de desarrollo...\n\n" << endl;
            break;
        case 2:
            show_users(userData);
            break;
        case 3:
            system("cls");
            cout << "\n\nEn proceso de desarrollo...\n\n" << endl;
            break;
        case 4:
            show_ranking(booksData, userData);
            break;
        case 5:
            cout << "\nSaliendo del programa...\n" << endl;
            start = false;
            break;
        default:
            system("cls");
            cout << "Opcion no valida, intentelo nuevamente...\n\n" << endl;
            break;
    }
}

// mostrar top 10 de lectores(solo muestra)
void show_ranking(json *booksData,json *userData)
{
    system("cls");
    cout << "----------------------------------------------------------------------------+" << endl;
    cout << "|   Codigo   |\tDNI\t|\tNombres \t |   Puntos   |  Trofeo \t |  Nro Libros |" << endl;
    cout << "----------------------------------------------------------------------------+" << endl;
    for (auto& x : userData->items())
    {
        cout << " " << x.key() << "\t" << x.value().at("dni") << "   " << x.value().at("name");
        cout << "\t " << x.value().at("points") << " \t" << x.value().at("trophies").size();
        cout << "\t" << x.value().at("booksRead").size() << endl;
    }
    cout << "----------------------------------------------------------------------------+" << endl;
    cout << "\nFin de la lista...\n";
}

// mostrar todos los usuarios
void show_users(json *userData)
{
    system("cls");
    cout << "\nActualmente existen " << userData->size() << " usuarios en el sistema\n" << endl;
    cout << "---------------------------------------------------------+" << endl;
    cout << "|   Codigo    |    DNI\t |\tNombre y Apellido \t| " << endl;
    cout << "---------------------------------------------------------+" << endl;
    for (auto& x : userData->items())
    {
        cout << "  " << x.key() << " \t " << x.value().at("dni") << " \t ";
        cout << x.value().at("name") << endl;
    }
    cout << "---------------------------------------------------------+" << endl;
    cout << "\nFin de la lista...\n";
}
