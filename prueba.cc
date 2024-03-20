#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

void calcular_partes(const vector<int>& articulos_actuales, vector<vector<int>>& partes){

    for (int i = 0; i < articulos_actuales.size(); i++)
    {
        cout << "creando subset_temp" << endl;
        vector<vector<int>> subset_temp = partes;  //making a copy of given 2-d vector.
        
        cout << "primer bucle " << i << endl;
        for (int j = 0; j < subset_temp.size(); j++)
            subset_temp[j].push_back( articulos_actuales[i] );   // adding set[i] element to each subset of subsetTemp. like adding {2}(in 2nd iteration  to {{},{1}} which gives {{2},{1,2}}.
        
        cout << "segundo bucle " << i << endl;
        for (int j = 0; j < subset_temp.size(); j++)
            partes.push_back( subset_temp[j] );  //now adding modified subsetTemp to original subset (before{{},{1}} , after{{},{1},{2},{1,2}}) 
    }
}

int main(int argc, char *argv[]){
    vector<vector<int>> resultado;
    vector<int> numeros;

    for(int i = 1; i < 5; i++){
        numeros.push_back(i);
    }

    cout << "comienzo calculo" << endl;
    calcular_partes(numeros, resultado);
    cout << "termino calculo" << endl;
    
    for (auto parte : resultado){
        cout << "hola";
        for(auto num : parte){
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}
