#include "busca.hh"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "arbol.hh"


using namespace std;

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

    vector<Articulo> v_articulos; 

    for (int i = 0; i < num_articulos; i++){
        
        getline(f_in, ancho_articulo, ' ');
        getline(f_in, alto_articulo, ' ');
        getline(f_in, x_articulo, ' ');
        getline(f_in, y_articulo);

        v_articulos.push_back(Articulo(i, stoi(x_articulo), stoi(y_articulo), stoi(ancho_articulo), stoi(alto_articulo)));
    }

    pagina.num_articulos = num_articulos;
    pagina.ancho = ancho_pag;
    pagina.alto = alto_pag;
    pagina.actualizar_area();
    pagina.articulos = v_articulos;
}

void copiar_articulos(vector<Articulo> viejo, vector<Articulo> nuevo){
    for (auto& articulo : viejo){
        nuevo.push_back(articulo);
    }
}

void construir_siguiente_nivel(Pagina& pagina, Node* raiz, vector<Articulo> articulos_actuales, int& area_optima, int nivel){
    Articulo sig_articulo = pagina.articulos[nivel];
    if(nivel < pagina.articulos.size()){ // | ... | ... condiciones de poda

        // añade el articulo al vector
        articulos_actuales.push_back(pagina.articulos[nivel]);
        
        // RECORRE IZQUIERDA (añade el nuevo articulo)
        // (recorre primero izquierda porque añadir un articulo nuevo siempre sera mejor que no añadirlo)
        raiz->left = new Node(articulos_actuales, raiz->id + to_string(sig_articulo.id));
        construir_siguiente_nivel(pagina, raiz->left, articulos_actuales, area_optima, nivel+1);
        
        // extrae el articulo del vector
        articulos_actuales.pop_back();

        // RECORRE DERECHA (no añade el nuevo articulo)
        raiz->right = new Node(raiz->articulos, raiz->id);
        construir_siguiente_nivel(pagina, raiz->right, articulos_actuales, area_optima, nivel+1);
        

        
        
    };
}


void obtener_composicion_optima(Pagina& pagina){
    int area_optima = 0;
    vector<Articulo> articulos_insertados;
    Node* raiz = new Node(articulos_insertados, "");
    
    construir_siguiente_nivel(pagina, raiz, articulos_insertados, area_optima, 0);

    Node::print_tree(raiz, 0);

    // PRUEBA
    /*
    Articulo art0 = pagina.articulos[0];
    Articulo art1 = pagina.articulos[1];
    Articulo art2 = pagina.articulos[2];
    vector<Articulo> arts;
    arts.push_back(art0);
    arts.push_back(art1);
    arts.push_back(art2);
    Node* raiz = new Node(arts, to_string(art0.id) + to_string(art1.id) + to_string(art2.id));
    cout << raiz->id << endl;
    cout << raiz->area_ocupada << endl;
    */
}


int main(int argc, char *argv[]){
    ifstream f_in;

    if (argc < 2){
        cout << "ERROR: Numero de parametros invalido" << endl;
        exit(1);
    }

    abrir_fichero(argv[1], f_in);
    /*Pagina pagina;
    
    leer_pagina(f_in, pagina);
    pagina.mostrar_pagina(true);
    */
    int num_paginas = 0;
    while(!f_in.eof()){
        Pagina pagina;
    
        leer_pagina(f_in, pagina);
        obtener_composicion_optima(pagina);
        //pagina.mostrar_pagina(true, num_paginas);
        num_paginas++;
    }
        // leer una página

    return 0;
}