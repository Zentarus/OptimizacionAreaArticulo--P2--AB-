#ifndef BUSCA_HH
#define BUSCA_HH

#include <vector>
#include <iostream>
#include <string>
#include "./librerias/arbol.hh"
#include "./librerias/pagina.hh"
#include "./librerias/articulo.hh"

using namespace std;

void abrir_fichero_lectura(string nombre_fichero, ifstream& f_in);
void abrir_fichero_escritura(string nombre_fichero, ofstream& f_out);
void leer_pagina(ifstream& f_in, Pagina& pagina);
void escribir_resultados(ofstream& f_out, double tiempo_ejecucion);
void copiar_articulos(vector<Articulo> viejo, vector<Articulo> nuevo);
void calcular_partes(const vector<Articulo>& articulos_actuales, vector<vector<Articulo>>& partes);
bool hay_interseccion_entre_pareja_articulos(Articulo a, Articulo b);
bool intersecan_todos_articulos(const vector<Articulo>& articulos);
Articulo calcular_articulo_interseccion_pareja(Articulo a, Articulo b);
int calcular_area_interseccion_total(const vector<Articulo>& articulos);
int calcular_area(const vector<Articulo>& articulos);
bool hay_interseccion_con_sig_articulo(const vector<Articulo>& articulos_actuales, const Articulo& sig_articulo, int nivel);
int area_restante_maxima(const Pagina& pagina, const vector<Articulo>& articulos_actuales, int nivel);
bool aplicar_poda(const Pagina& pagina, const vector<Articulo>& articulos_actuales, const Articulo& sig_articulo, int nivel, int area_optima);
void construir_siguiente_nivel(Pagina& pagina, Node* raiz, vector<Articulo> articulos_actuales, vector<Articulo>& articulos_optimos, int& area_optima, int nivel, int& nodos_expandidos);
int obtener_composicion_optima(Pagina& pagina, vector<Articulo>& articulos_optimos, int& nodos_expandidos);
void imprimir_solucion(ofstream& f_out, int num_pag, int area_solucion, vector<Articulo> art_solucion, long double tiempo_ejecucion, int nodos_expandidos);
#endif