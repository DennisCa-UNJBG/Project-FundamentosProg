#include <iostream>
#include <string>
#include "json.hpp" // ruta relativa, se movio la libreria fuera de su carpeta para un mejor uso
#include <fstream> // leer y escribir en archivos
#include <vector> // para usar las variables tipo VECTOR

using json = nlohmann::json;
using namespace std;

// struct para crear un nuevos usuarios
struct userTemp {
    string codigo;
    vector <string> booksRead;
    int dni;
    string name = "prueba";
    int points;
    vector <string> trophies;
};

int showMenu();
void saveData(json *booksData, json *userData);
void show_data(json *data);
void option_menu(int val, json *booksData, json *userData, userTemp *newUserTemp);
void show_ranking(json *booksData, json *userData);
void show_users(json *userData);
void insert_user(json *booksData, json *userData, userTemp *newUserTemp);


// categoria de los libros -> 0           1          2             3        4
string catBooks[] = {"Ciencia Ficcion", "Drama", "Ramantica", "Cuento", "Novela"};

// lista de trofeos disponibles -> 0                1                   2                    3                  4
string trofeos[] = {"Lector de Ciencia Ficcion", "Lector de Drama", "Lector de Ramantica", "Lector de Cuento", "Lector de Novela"};

//variable para finalizar el bucle del programa
bool start = true;

int main(){   

    userTemp newUserTemp;

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
        option_menu(val_menu, &booksData, &userData, &newUserTemp);  
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
    for (auto it = data->begin(); it != data->end(); ++it)
    {
        std::cout << it.key() << " | " << it.value() << "\n";
    }
    cout << data->dump(1, '\t') << "\n\n"<< endl;
}

// procesar las opciones del menu
void option_menu(int val, json *booksData, json *userData, userTemp *newUserTemp)
{   
    switch (val)
    {
        case 1:
            insert_user(booksData, userData, newUserTemp);
            cout << "hola" ;
            break;
        case 2:
            show_users(userData);
            break;
        case 3:
            show_data(userData);
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
            cout << "\nOpcion no valida, intentelo nuevamente...\n\n" << endl;
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

void insert_user(json *booksData, json *userData, userTemp *newUserTemp)
{
    bool comprobar = false;
    
    system("cls");
    cout << "---------------------------------------------------------+" << endl;
    cout << "\tCreando un Nuevo Usuario" << endl;
    cout << "---------------------------------------------------------+" << endl;

    do {
        comprobar = false;
        
        cout << "Ingrese el DNI del nuevo usuario: " << endl;
        cin >> newUserTemp->dni;

        for (auto it = userData->begin(); it != userData->end(); ++it) // o   for (auto& it : userData->items())
        {
            if(it.value().at("dni") == newUserTemp->dni)
            {
                cout << "No permitido!! el DNI ingresado ya se encuentra registrado" << endl;
                comprobar = true;
            }
        }
    }
    while (comprobar);
    
    cout << "Ingrese el nombre del nuevo usuario: \n";
    getline(cin, newUserTemp->name);
    getline(cin, newUserTemp->name); //deben sere 2 getline(luego se repara)

    cout << "El Usuario a leido libros registrados? (0 =  no, 1 = si) \n";
    cin >> comprobar;

    while(comprobar) 
    {
        string cod;
        cout << "Ingrese el código de un libro: " << endl;
        cin >> cod;
        newUserTemp->booksRead.push_back(cod);
        cout << "Ingresar nuevo libro = 1 , salie = 0: ";
        cin >> comprobar;
    }

    cout << "\n" << newUserTemp->booksRead.size() << "\n" << newUserTemp->dni << "\n"  << newUserTemp->name
        << "\n" << newUserTemp->points << "\n"  << newUserTemp->trophies.size() << "\n" << endl;
        
}
