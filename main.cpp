#include <iostream>
#include <string>
#include "json.hpp" // ruta relativa, se movio la libreria fuera de su carpeta para un mejor uso
#include <fstream> // leer y escribir en archivos
#include <vector> // para usar las variables tipo VECTOR
#include <conio.h>
#include <cmath> //por el momento para hallar la longitud del dni (log10()+1)
#include <windows.h> // funcion Sleep
#include <algorithm> //invertir string, upper case y lower case (convertir a mayuscula y minuscula); sort->ordenamiento

using json = nlohmann::json;
using namespace std;

// struct para crear un nuevos usuarios
struct userTemp {
    string codigo;
    vector <string> booksRead;
    int dni;
    string name = "prueba";
    int points = 0;
    vector <int> trophies;
    
    void reset(){
        codigo = ""; booksRead = {}; dni = 0;
        name = "prueba"; points =0; trophies = {};
    }
};

//struct para mostrar el ranking de usuarios
typedef struct user_data
{
    string codigo, name;
    int dni, booksRead, points,trophies;
}datatemp;

int showMenu();
void saveData(json *booksData, json *userData);
void option_menu(int val, json *booksData, json *userData, userTemp *newUserTemp);
void show_ranking(json *booksData, json *userData);
bool compare(datatemp a, datatemp b); // funcion para ordenar el ranking de usuarios
void show_users(json *userData);
void insert_user(json *booksData, json *userData, userTemp *newUserTemp);
vector <int> processTrophies(json *booksData, vector <string> name);
void update_user(json *booksData, json *userData, userTemp *newUserTemp);


// categoria de los libros -> 0           1          2             3        4
string catBooks[] = {"Ciencia Ficcion", "Drama", "Ramantica", "Cuento", "Novela"};

// lista de trofeos disponibles -> 0                1                   2                    3                  4
string trofeos[] = {"Lector de Ciencia Ficcion", "Lector de Dramas", "Lector de Romances", "Lector de Cuentos", "Lector de Novelas"};

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
        int val_menu = showMenu();
        option_menu(val_menu, &booksData, &userData, &newUserTemp);
    }
    
    //system("pause");
    return 0;
}

// mostrar menu
int showMenu()
{
    system("cls");
    int i = 0;
    cout << "\n =======================================" << endl;
    cout << "\tM	E	N	U" << endl;
    cout << " =======================================" << endl;
    cout << "  [1] Ingresar nuevo Usuario " << endl;
    cout << "  [2] Visualizar lectores registrados " << endl;
    cout << "  [3] Modificar datos del lector " << endl;
    cout << "  [4] Imprimir el ranking de lectores " << endl;
    cout << "  [5] Salir " << endl;
    cout << "  Selecciones una opcion(numero): ";
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

// procesar las opciones del menu
void option_menu(int val, json *booksData, json *userData, userTemp *newUserTemp)
{   
    switch (val)
    {
        case 1:
            insert_user(booksData, userData, newUserTemp);
            cout << "\nPRESIONE UNA TECLA PARA VOLVER AL MENU\n";
            _getch();
            break;
        case 2:
            show_users(userData);
            break;
        case 3:
            system("cls");
            update_user(booksData, userData, newUserTemp);
            cout << "\nPRESIONE UNA TECLA PARA VOLVER AL MENU\n";
            _getch();
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

    int cantData = userData->size();
    datatemp arrayUser[cantData];

    int ii = 0;
    for (auto x = userData->begin(); x != userData->end(); ++x)
    {
        arrayUser[ii].codigo = x.key();
        arrayUser[ii].dni = x.value().at("dni");
        arrayUser[ii].name = x.value().at("name");
        arrayUser[ii].points = x.value().at("points");
        arrayUser[ii].trophies = x.value().at("trophies").size();
        arrayUser[ii].booksRead = x.value().at("booksRead").size();
        ii++;
    }

    sort(arrayUser, arrayUser+cantData, compare);

    cout << "\n\t\t\t\tRANKING DE LECTORES\n";
    cout << "+-------------------------------------------------------------------------------+" << endl;
    cout << "    Codigo    |    DNI   |\tNombres \t| Puntos |  Trofeo  | Nro Libros " << endl;
    cout << "+-------------------------------------------------------------------------------+" << endl;
    for( int i = 0 ; i < cantData ; i++)
    {
        cout << "  " << arrayUser[i].codigo << "  | " << arrayUser[i].dni << " |  " << arrayUser[i].name << "   \t";
        cout << "|   " << arrayUser[i].points << "  |  " << arrayUser[i].trophies << "    ";
        cout << " |   " << arrayUser[i].booksRead << endl;

        if (i == 9) // mostrar solo el top 10
            break;
    }
    cout << "+-------------------------------------------------------------------------------+" << endl;
    cout << "\nPRESIONE UNA TECLA PARA VOLVER AL MENU\n";
    _getch();
}

bool compare(datatemp a, datatemp b) // funcion para ordenar el ranking de usuarios
{
	if(a.points > b.points)
		return 1;
	else 
		return 0;
}

// mostrar todos los usuarios
void show_users(json *userData)
{
    system("cls");
    cout << "\nActualmente existen " << userData->size() << " usuarios en el sistema\n" << endl;
    cout << "+--------------------------------------------------------+" << endl;
    cout << "    Codigo    |     DNI    |\tNombre y Apellido \t " << endl;
    cout << "+--------------------------------------------------------+" << endl;
    for (auto& x : userData->items())
    {
        cout << "  " << x.key() << "  |  " << x.value().at("dni") << "  |  ";
        cout << x.value().at("name") << endl;
    }
    cout << "+--------------------------------------------------------+" << endl;
    cout << "\nPRESIONE UNA TECLA PARA VOLVER AL MENU\n";
    _getch();
}

void insert_user(json *booksData, json *userData, userTemp *newUserTemp)
{
    bool comprobar = false;
   
    do {
        comprobar = false;
        
        system("cls");
        cout << "+---------------------------------------------------------+" << endl;
        cout << "\tCreando un Nuevo Usuario" << endl;
        cout << "+---------------------------------------------------------+" << endl;
        
        cout << "\nIngrese el DNI del nuevo usuario: " << endl;
        cin >> newUserTemp->dni;
        
        if ( int( log10(newUserTemp->dni) + 1 ) == 8 ){  //comprobar que sea DNI valido
			for (auto it = userData->begin(); it != userData->end(); ++it) // o   for (auto& it : userData->items())
        	{
            	if(it.value().at("dni") == newUserTemp->dni)
           		{
            		cout << "No permitido!! el DNI ingresado ya se encuentra registrado" << endl;
            		Sleep(3000); //esperar 3 segundos
            		comprobar = true;
            	}
        	}
		}
		else{
			cout << "DNI no valido" << endl;
			Sleep(2000); //esperar 2 segundos
			comprobar = true;
		}
    }
    while (comprobar);
    
    cout << "Ingrese el nombre del nuevo usuario: \n";
    cin.sync(); // sincronizar entrada de consola 
    getline(cin, newUserTemp->name); //ingresar nombre completo a variable

    cout << "El Usuario a leido libros registrados? (0 =  no, 1 = si) \n";
    cin >> comprobar;

    while(comprobar) 
    {
        string cod;
        cout << "Ingrese el codigo de un libro: " << endl; // solo funciona con códigos registrados
        cin >> cod;
        newUserTemp->booksRead.push_back(cod);
        cout << "Ingresar nuevo libro = 1 , salir = 0: ";
        cin >> comprobar;
    }

    //crear codigo del nuevo usuario usuario
    string codUser = newUserTemp->name.substr(newUserTemp->name.find(" ")+1, 2);    
    string tmp_s_reversed(to_string(newUserTemp->dni));
    reverse(tmp_s_reversed.begin(), tmp_s_reversed.end());
    codUser = codUser + tmp_s_reversed;

    //convertir el codigo del usuario a minusculas
    std::for_each(codUser.begin(), codUser.end(), [](char & c) {
        c = ::tolower(c);
    });

    // calcular cantidad de puntos
    for (auto i = 0; i < newUserTemp->booksRead.size(); i++) 
    {
        for (auto x = booksData->begin(); x != booksData->end(); ++x)
        {
            if(x.key() == newUserTemp->booksRead[i]) // buscar si el libro existe
            {
                newUserTemp->points += 1; // si existe se le suma 1 punto
                int num_temp = x.value().at("points"); // se obtiene la cantidad de puntos de ese libro
                newUserTemp->points += num_temp; // se suma los puntos anteriores con los nuevos
            }
        }        
    }

    json j_books(newUserTemp->booksRead); // convertir vector de libros a json_array

    // calcular cantidad de trofeos
    newUserTemp->trophies = processTrophies(booksData, newUserTemp->booksRead);
    json j_trophies(newUserTemp->trophies); // convertir vector de trofeos a json_array

    // agregar nuevo usuario a una variable JSON
    json prueba =
    {
        codUser, {
                {"booksRead", j_books},
                {"dni", newUserTemp->dni},
                {"name", newUserTemp->name},
                {"points", newUserTemp->points},
                {"trophies", j_trophies}
            }
    };
    
    // agregar la variable JSON del usuario a la variable JSON principal
    userData->push_back(json::object_t::value_type(prueba));    
    // guardar cambios en los archivos de texto
    saveData(booksData, userData);
    
    // imprimir para observar el resultado
    system("cls");
    cout << "+---------------------------------------------------------+" <<
        "\nEl codigo del nuevo usuario es " << codUser << "\ny sus datos son:" <<
        "\n+---------------------------------------------------------+\n" <<
        "\n\tNombre: " << newUserTemp->name <<
        "\n\tDNI:" << newUserTemp->dni <<
        "\n\tCantidad de libros leidos: " << newUserTemp->booksRead.size() <<
        "\n\tTotal de puntos: " << newUserTemp->points << 
        "\n+---------------------------------------------------------+" << endl;
    
    newUserTemp->reset(); // reiniciar datos del struct temporal
}

vector <int> processTrophies(json *booksData, vector <string> booksread)
{
    vector <int> Trophies; // para almacenar los id de los trofeos obtenidos cada vez
    int number[] = {0,0,0,0,0}; // almacenar la cantidad de libros leidos por categoria

    for (auto i = 0; i < booksread.size(); i++) // recorrer libros
    {        
        for (auto x = booksData->begin(); x != booksData->end(); ++x) // buscar si el libro existe
        {
            if(x.key() == booksread[i]) // comprar ID del libro con los libros almacenados
            {
                for (int j = 0; j < 5; j++) // recorrer el array contador "number"
                {
                    if (j == x.value().at("Genero")) // comparar el id del genero
                        number[j] += 1; // incrementar el valor por cada libro leido del mismo genero
                }                
            }
        }
    }

    // verificar si un usuaria a leido 5 o mas libros de una categoria
    for (int j = 0; j < 5; j++) 
    {
        if (number[j] >= 5) // si leyo mas de 5 libros del mismo genero agregar su ID
            Trophies.push_back(j);// mandar el id del trofeo para mostrar
    } 
    return Trophies; // regresar los trofeos obtenidos
}
void update_user(json *booksData, json *userData, userTemp *newUserTemp)
{
    bool comprobar = false;
   
    do {
        comprobar = false;
        system("cls");
        cout << "+---------------------------------------------------------+" << endl;
        cout << "\tActualizando Usuario" << endl;
        cout << "+---------------------------------------------------------+" << endl;
        
        cout << "\nIngrese el DNI del usuario: " << endl;
        cin >> newUserTemp->dni;

        for (auto it = userData->begin(); it != userData->end(); ++it) // o   for (auto& it : userData->items())
        {
            if(it.value().at("dni") == newUserTemp->dni)
            {
                cout << "Usuario encontrado!!" << endl;
                newUserTemp->codigo = it.key();
                newUserTemp->dni = it.value().at("dni");
                newUserTemp->name = it.value().at("name");
                
                for (auto& x : it.value().at("booksRead").items())
                {
                    newUserTemp->booksRead.push_back(x.value());
                }

                comprobar = false;
                break;
            }
            else{
			cout << "DNI no valido, intentelo nuevamente" << endl;
			Sleep(2000); //esperar 2 segundos
			comprobar = true;
		    }
        }
    }
    while (comprobar);

    cout << "El Usuario a leido nuevos libros? (0 =  no, 1 = si) \n";
    cin >> comprobar;

    if (comprobar)
    {
        while(comprobar) 
        {
            string cod;
            cout << "Ingrese el codigo de un libro: " << endl; // solo funciona con códigos registrados
            cin >> cod;
            newUserTemp->booksRead.push_back(cod);
            cout << "Ingresar nuevo libro = 1 , salir = 0: ";
            cin >> comprobar;
        }

        // calcular cantidad de puntos
        for (auto i = 0; i < newUserTemp->booksRead.size(); i++) 
        {
            for (auto x = booksData->begin(); x != booksData->end(); ++x)
            {
                if(x.key() == newUserTemp->booksRead[i]) // buscar si el libro existe
                {
                    newUserTemp->points += 1; // si existe se le suma 1 punto
                    int num_temp = x.value().at("points"); // se obtiene la cantidad de puntos de ese libro
                    newUserTemp->points += num_temp; // se suma los puntos anteriores con los nuevos
                }
            }        
        }
        json j_books(newUserTemp->booksRead); // convertir vector de libros a json_array

        // calcular cantidad de trofeos
        newUserTemp->trophies = processTrophies(booksData, newUserTemp->booksRead);
        json j_trophies(newUserTemp->trophies); // convertir vector de trofeos a json_array

        // agregar nuevo usuario a una variable JSON
        json prueba =
        {
            newUserTemp->codigo, {
                    {"booksRead", j_books},
                    {"dni", newUserTemp->dni},
                    {"name", newUserTemp->name},
                    {"points", newUserTemp->points},
                    {"trophies", j_trophies}
                }
        };
        
        // eliminar usuario para reemplazar sus datos
        userData->erase(newUserTemp->codigo);
        // agregar la variable JSON del usuario editado a la variable JSON principal
        userData->push_back(json::object_t::value_type(prueba));    
        // guardar cambios en los archivos de texto
        saveData(booksData, userData);
    }
    newUserTemp->reset(); // reiniciar datos del struct temporal
}