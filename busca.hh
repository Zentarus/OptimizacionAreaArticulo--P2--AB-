#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "./librerias/pagina.hh"
#include "./librerias/articulo.hh"

using namespace std;

void abrir_fichero(string nombre_fichero, ifstream& f_in);

void leer_pagina(ifstream& f_in, Pagina& pagina);

void obtener_composicion_optima(Pagina& pagina);

int main(int argc, char *argv[]);