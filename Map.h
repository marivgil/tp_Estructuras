#include <iostream>
#include <stdlib.h>
#include "Cliente.h"
#include "ArrayList.h"

using namespace std;

struct AVLNode {
    int height;
    AVLNode* left;
    AVLNode* right;
    Cliente kv;
};

typedef AVLNode* AVL;

typedef AVL Map;

// Prop.: crea un Map vacio
Map emptyM();

// Prop.: asocia un cuit con un cliente
void addM(Map& m, Cliente c);

// Prop.: devuelve un cliente dado un cuit
Cliente lookupM(Map& m, string cuit);

// Prop.: indica si la respuesta del lookup es v�lida
bool isNothing(Cliente c);

// Prop.: elimina un cliente dado un cuit
void removeM(Map& m, string cuit);

// Prop.: devuelve la lista de claves de un Map
ArrayList domM(Map& m);

// Prop.: imprime un Map
void printMap(Map m);

// Prop.: libera la memoria de un Map
void destroyM(Map& m);

//prop: elimina del arbol los clientes recibidos
void eliminarClientesDelPlanM(ArrayList clientes, Map& m);
