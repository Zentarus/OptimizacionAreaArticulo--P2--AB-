#ifndef BUSCA_HH
#define BUSCA_HH

#include <vector>
#include <iostream>
#include <string>
#include "./librerias/pagina.hh"
#include "./librerias/articulo.hh"

using namespace std;

void abrir_fichero(string nombre_fichero, ifstream& f_in);

void leer_pagina(ifstream& f_in, Pagina& pagina);

void copiar_articulos(vector<Articulo> viejo, vector<Articulo> nuevo);

int area_actual(const Pagina& pagina, const vector<Articulo>& articulos_actuales);

bool hay_interseccion(const vector<Articulo>& articulos_actuales, const Articulo& sig_articulo, int nivel);

bool aplicar_poda(const Pagina& pagina, const vector<Articulo>& articulos_actuales, const Articulo& sig_articulo, int nivel, int area_optima);

void obtener_composicion_optima(Pagina& pagina);

#endif