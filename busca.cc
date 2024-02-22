#include "busca.hh"
#include <fstream>
#include <istream>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

void obtener_articulos(ifstream& f_in){
    string fichero;
}

void abrir_fichero(string nombre_fichero){
    ifstream f_in;
    f_in.open(nombre_fichero);
    if (!f_in.is_open()){
        cout << "Error al abrir el fichero \"" << nombre_fichero << "\" para su lectura" << endl;
        exit(1);
    }
}

void leer_pagina(ifstream& f_in, Articulo[]){
    string num_articulos, ancho_pag, alto_pag;
    getline(f_in, num_articulos, ' ');
    getline(f_in, ancho_pag, ' ');
    getline(f_in, alto_pag);

    //Pagina pag = 
    
}

int main(int argc, char *argv[]){

    ifstream fichero;
    abrir_fichero(argv[1], fichero);
    while()
        // leer una página

    return 0;
}
*/

/*
int main() {
    // Pruebas para la clase Articulo
    Articulo art1(10, 20, 5, 5);
    std::cout << "Area del articulo 1: " << art1.area << std::endl;

    Articulo art2;
    std::cout << "Area del articulo 2: " << art2.area << std::endl;

    // Pruebas para la clase Pagina
    Pagina pagina1(3, 10, 20);
    std::cout << "Area de la pagina 1: " << pagina1.area << std::endl;

    return 0;
}*/
