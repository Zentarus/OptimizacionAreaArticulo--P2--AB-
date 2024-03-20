#include "busca.hh"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <stdlib.h>
#include "./librerias/arbol.hh"


using namespace std;

void abrir_fichero_lectura(string nombre_fichero, ifstream& f_in){
    f_in.open(nombre_fichero);
    if (!f_in.is_open()){
        cout << "Error al abrir el fichero \"" << nombre_fichero << "\" para su lectura" << endl;
        exit(1);
    }
}

void abrir_fichero_escritura(string nombre_fichero, ofstream& f_out){
    f_out.open(nombre_fichero);
    if (!f_out.is_open()){
        cout << "Error al abrir el fichero \"" << nombre_fichero << "\" para su escritura" << endl;
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

void escribir_resultados(ofstream& f_out, double tiempo_ejecucion){
    f_out << "Aqui resultado area | " << setprecision(3) << tiempo_ejecucion << " ms" << endl;
}

void copiar_articulos(vector<Articulo> viejo, vector<Articulo> nuevo){
    for (auto& articulo : viejo){
        nuevo.push_back(articulo);
    }
}

void calcular_partes(const vector<Articulo>& articulos_actuales, vector<vector<Articulo>>& partes){

    for (int i = 0; i < articulos_actuales.size(); i++)
    {
        vector<vector<Articulo>> subset_temp = partes;  //making a copy of given 2-d vector.

        for (int j = 0; j < subset_temp.size(); j++)
            subset_temp[j].push_back( articulos_actuales[i] );   // adding set[i] element to each subset of subsetTemp. like adding {2}(in 2nd iteration  to {{},{1}} which gives {{2},{1,2}}.

        for (int j = 0; j < subset_temp.size(); j++)
            partes.push_back( subset_temp[j] );  //now adding modified subsetTemp to original subset (before{{},{1}} , after{{},{1},{2},{1,2}}) 
    }
}

// Calcula el área actual ocupada por los articulos pasados por parámetro
int calcular_area(const vector<Articulo>& articulos_actuales) {
    int area_total = 0;

    vector<vector<Articulo>> partes;
    calcular_partes(articulos_actuales, partes);

    for(vector<Articulo> conjunto : partes){
        int area_interseccion = calcular_area_interseccion(conjunto);

        if(conjunto.size() % 2 == 0){
            area_total -= area_interseccion;
        } else {
            area_total += area_interseccion;
        }
    }

    return area_total;
}

// Función para verificar si un artículo cabe completamente dentro de la página
/* Creo que no es necesaria pues todos los artículos caben, pero por si acaso
bool cabe_en_pagina(const Pagina& pagina, const Articulo& articulo) {
    cout << "Entro cabe_en_pagina()" << endl;
    return  (articulo.x + articulo.ancho <= pagina.ancho) &&
            (articulo.y + articulo.alto <= pagina.alto);
}
*/

// Comprueba si hay intersección entre el artículo actual y los articulos colocados anteriormente
bool hay_interseccion(const vector<Articulo>& articulos_actuales, const Articulo& sig_articulo, int nivel) {
    cout << "Entro hay_interseccion()" << endl;
    const Articulo& articulo_actual = sig_articulo;

    for (int i = 0; i < articulos_actuales.size(); ++i) {
        const Articulo& articulo_anterior = articulos_actuales[i];
        cout << "Se va a comparar: " << articulo_actual.x << ", " << articulo_actual.y << ", " << articulo_actual.ancho << ", " << articulo_actual.alto << " con "
                                        << articulo_anterior.x << ", " << articulo_anterior.y << ", " << articulo_anterior.ancho << ", " << articulo_anterior.alto << endl;

        // Comprueba si hay intersección entre los artículos
        if (articulo_actual.x < articulo_anterior.x + articulo_anterior.ancho &&
            articulo_actual.x + articulo_actual.ancho > articulo_anterior.x &&
            articulo_actual.y < articulo_anterior.y + articulo_anterior.alto &&
            articulo_actual.y + articulo_actual.alto > articulo_anterior.y) {
            cout << "Hay interseccion" << endl;
            return true;
        }
    }
    cout << "NO hay interseccion" << endl;
    return false;
}

int area_restante_maxima(const Pagina& pagina, const vector<Articulo>& articulos_actuales, int nivel){
    vector articulos_restantes = articulos_actuales;
    for (int i = nivel; i < pagina.num_articulos; i++){
        articulos_restantes.push_back(pagina.articulos[i]);
    }

    return calcular_area(articulos_restantes);
}

bool aplicar_poda(const Pagina& pagina, const vector<Articulo>& articulos_actuales, const Articulo& sig_articulo, int nivel, int area_optima) {

    /*
    // Si el artículo actual no cabe en la página
    if (!cabe_en_pagina(pagina, articulos_actuales[nivel])) {
        cout << "PODA: El articulo no cabe en pagina" << endl;
        return true;
    }
    */

    // Si hay intersección de artículos
    // --------------------------------------------------------------
    if (hay_interseccion(articulos_actuales, sig_articulo, nivel)) {
        cout << "PODA: Hay interseccion entre articulos" << endl;
        return true;
    }

    /*
    // Si el area que se va a añadir es menor que una óptima alcanzada
    // ---------------------------------------------------------------
    vector<Articulo> vector_con_sig_articulo = articulos_actuales; // Declaramos un vector auxiliar con el siguiente articulo que se puede añadir
    vector_con_sig_articulo.push_back(pagina.articulos[nivel]);
    int area_con_sig_articulo = calcular_area(vector_con_sig_articulo); // Calculamos el área que se alcanza con dicho vector auxiliar

    if (area_con_sig_articulo <= area_optima) {
        cout << "PODA: Area a alcanzar es menor o igual que optima" << endl;
        return true;
    }
    */

    if(area_optima < area_restante_maxima(pagina, articulos_actuales, nivel)){
        cout << "PODA: (Area actual + Area que queda por añadir) es menor que la optima actual";
        return true;
    }
    
    return false;
}

void construir_siguiente_nivel(Pagina& pagina, Node* raiz, vector<Articulo> articulos_actuales, vector<Articulo>& articulos_optimos, int& area_optima, int nivel){
    
    int area_actual = calcular_area(articulos_actuales);

    if(area_actual > area_optima) {
        area_optima = area_actual;
        articulos_optimos = articulos_actuales;

    }

    if (nivel < pagina.articulos.size()){ // Para que en la siguiente instruccion no se acceda a una componente fuera de rango
                                          // Tambien es la condición de poda para no pasarnos del número de articulos
        Articulo sig_articulo = pagina.articulos[nivel];
        
        cout << "Explorando articulo: " << sig_articulo.id << " en nivel " << nivel << endl;
        cout << sig_articulo.x << ", " << sig_articulo.y << ", " << sig_articulo.ancho << ", " << sig_articulo.alto << endl;

        if (!aplicar_poda(pagina, articulos_actuales, sig_articulo, nivel, area_optima))
        {
            cout << "No se aplica poda, continuando exploracion..." << endl;

            // añade el articulo al vector
            articulos_actuales.push_back(pagina.articulos[nivel]);

            // RECORRE IZQUIERDA (añade el nuevo articulo)
            // (recorre primero izquierda porque añadir un articulo nuevo siempre sera mejor que no añadirlo)
            cout << "Explorando rama izquierda..." << endl;
            raiz->left = new Node(articulos_actuales, raiz->id + to_string(sig_articulo.id));
            //area_optima = max(calcular_area(pagina, articulos_actuales), area_optima);
            construir_siguiente_nivel(pagina, raiz->left, articulos_actuales, articulos_optimos, area_optima, nivel + 1);

            // extrae el articulo del vector
            articulos_actuales.pop_back();

            // RECORRE DERECHA (no añade el nuevo articulo)
            cout << "Explorando rama derecha..." << endl;
            raiz->right = new Node(raiz->articulos, raiz->id);
            construir_siguiente_nivel(pagina, raiz->right, articulos_actuales, articulos_optimos, area_optima, nivel + 1);
        }
        else
        {
            cout << "Se aplica la poda en este nivel, terminando exploracion." << endl;
        }
    } else {
        cout << "Finaliza exploracion por fin de articulos" << endl;
    }
}


// faltará que esta función devuelva por referencia el area_optima que habrá calculado construir_siguiente_nivel(...)
void obtener_composicion_optima(Pagina& pagina, double& duracion_ms){
    int area_optima = 0;
    vector<Articulo> articulos_insertados, articulos_optimos;
    Node* raiz = new Node(articulos_insertados, "");

    auto start_time = chrono::high_resolution_clock::now();
    construir_siguiente_nivel(pagina, raiz, articulos_insertados, articulos_optimos, area_optima, 0);
    auto end_time = chrono::high_resolution_clock::now();

    duracion_ms = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1000000.0;
    Node::print_tree(raiz, 0);

    cout << endl << "--------------------------------------------------------" << endl;
    cout << "Area optima: " << endl << "\t" << area_optima << endl << endl;
    cout << "Articulos utilizados: " << endl;
    for (Articulo art : articulos_optimos){
        cout << "\t" << art.x << ", " << art.y << ", " << art.ancho << ", " << art.alto << endl;
    }

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
    double tiempo_ejecucion = 0.0;
    ifstream f_in;
    ofstream f_out;

    if (argc < 3){
        cout << "ERROR: Numero de parametros invalido" << endl;
        exit(1);
    }

    abrir_fichero_lectura(argv[1], f_in);
    abrir_fichero_escritura(argv[2], f_out);
    /*Pagina pagina;
    leer_pagina(f_in, pagina);
    pagina.mostrar_pagina(true);
    */

    while(!f_in.eof()){
        Pagina pagina;
        leer_pagina(f_in, pagina);
        obtener_composicion_optima(pagina, tiempo_ejecucion);
        //pagina.mostrar_pagina(true, num_paginas);
        escribir_resultados(f_out, tiempo_ejecucion);
    }
    
    f_in.close();
    f_out.close();
    return 0;
}