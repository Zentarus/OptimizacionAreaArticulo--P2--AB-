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

void abrir_fichero(string nombre_fichero, ifstream& f_in){
    f_in.open(nombre_fichero);
    if (!f_in.is_open()){
        cout << "Error al abrir el fichero \"" << nombre_fichero << "\" para su lectura" << endl;
        exit(1);
    }
}

void leer_pagina(ifstream& f_in, Pagina& pagina){
    string s_num_articulos, s_ancho_pag, s_alto_pag;
    string x_articulo, y_articulo, ancho_articulo, alto_articulo;

    getline(f_in, s_num_articulos, ' ');
    getline(f_in, s_ancho_pag, ' ');
    getline(f_in, s_alto_pag);

    int num_articulos = stoi(s_num_articulos);
    int ancho_pag = stoi(s_ancho_pag);
    int alto_pag = stoi(s_alto_pag);

    Articulo v_articulos[num_articulos];

    for (int i = 0; i < num_articulos; i++){
        
        getline(f_in, x_articulo, ' ');
        getline(f_in, y_articulo, ' ');
        getline(f_in, ancho_articulo, ' ');
        getline(f_in, alto_articulo);

        v_articulos[i] = Articulo(stoi(x_articulo), stoi(y_articulo), stoi(ancho_articulo), stoi(alto_articulo));
    }
    pagina.num_articulos = num_articulos;
    pagina.ancho = ancho_pag;
    pagina.alto = alto_pag;
    pagina.num_articulos = v_articulos;
}

int main(int argc, char *argv[]){

    ifstream f_in;
    abrir_fichero(argv[1], f_in);
    cout << "antes de leer" << endl;
    Pagina pagina;
    
    leer_pagina(f_in, pagina);
    cout << "despues de leer pagina" << endl;
    cout << "alto: " << pagina.alto << endl;
    cout << "ancho: " << pagina.ancho << endl;
    cout << "area: " << pagina.area << endl;
    cout << "num_articulos: " << pagina.num_articulos << endl;
    
    for(int i = 0; i < pagina.num_articulos; i++){
        cout << "articulo: " << i << endl;
        cout << "--------------------------" << endl;
        cout << "x_articulo: " << pagina.articulos[i]->x << endl;
        cout << "y_articulo: " << pagina.articulos[i]->y << endl;
        cout << "ancho_articulo: " << pagina.articulos[i]->ancho << endl;
        cout << "alto_articulo: " << pagina.articulos[i]->alto << endl;
        cout << endl;
    }
    
    /*
    while(!f_in.eof()){
        
    }
        // leer una página
    */
    return 0;
}