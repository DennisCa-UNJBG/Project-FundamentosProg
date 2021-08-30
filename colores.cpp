#include <iostream>
#include <windows.h>
using namespace std;
int main()
{
    // mostrar las opciones de colores en consola
    HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE); //just once
    for (int i = 0 ; i < 255 ; i++) 
    {
        SetConsoleTextAttribute(color, i);
        cout<<" combination" << i;
    }
    return 0;
}