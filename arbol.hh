#pragma once
#include <iostream>
#include <functional>
#include "articulo.hh"

using namespace std;

//A structure to create node
struct Node {
    string id;
    vector<Articulo> articulos;
    int area_ocupada;

    struct Node* left;
    struct Node* right;

    // A constructor to the struct node
    // that inserts value in the data variable.

    Node(vector<Articulo> _articulos, string _id)
    {   
        id = _id;
        articulos = _articulos;
        left = NULL;//Left child is initialized to NULL
        right = NULL;//Right child is initialized to NULL

        int total = 0;
        for (auto& articulo : articulos){
            total += articulo.area;
        }
        area_ocupada = total;
    }
};

//string vector_articulos_a_string(vector<Articulo> articulos);

//A function to print the tree
void Printtree(struct Node *root, int tab);

