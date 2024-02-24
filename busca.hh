#include <vector>
#include <iostream>
using namespace std;

class Articulo {
public:
    int x;
    int y;
    int ancho;
    int alto;
    int area;

    Articulo(int _x, int _y, int _ancho, int _alto) :
        x(_x), y(_y), ancho(_ancho), alto(_alto) {
            area = _ancho * _alto;
        }

    Articulo() :
        x(0), y(0), ancho(0), alto(0), area(0) {}

    void mostrar_articulo(int index = 0){
        cout << "Articulo " + to_string(index) << ":" << endl;
        cout << "-----------------" << endl;
        cout << "ancho -> " << ancho << endl;
        cout << "alto -> " << alto << endl;
        cout << "x -> " << x << endl;
        cout << "y -> " << y << endl;
    }
};

class Pagina {
public:
    int num_articulos;
    int ancho;
    int alto;
    int area;
    vector<Articulo> articulos; 

    Pagina(int _num_articulos, int _ancho, int _alto, const vector<Articulo>& _articulos) :
        num_articulos(_num_articulos), ancho(_ancho), alto(_alto), articulos(_articulos) {
            area = _ancho * _alto;
    }

    Pagina() :
        Pagina(0, 0, 0, vector<Articulo>()) {}

    void actualizar_area(){
        area = ancho * alto;
    }

    void mostrar_pagina(bool mostrar_articulos){
        cout << endl;
        cout << "Pagina: " << endl;
        cout << "----------------------------------" << endl;
        cout << "num_articulos -> " << num_articulos << endl;
        cout << "alto -> " << alto << endl;
        cout << "ancho -> " << ancho << endl;
        cout << "area -> " << area << endl << endl;
        if(mostrar_articulos){
            for(int i = 0; i < num_articulos; i++){
                articulos[i].mostrar_articulo(i);
                cout << endl;
            }
        }
    }
};
