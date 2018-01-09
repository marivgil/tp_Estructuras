#include <iostream>
#include "ArrayList.h"

using namespace std;

struct PlanSt {
    string nombre;
    ArrayList cuitsClientes;
};

typedef PlanSt* Plan;

/// UN CONJUNTO DE PLANES ES UN ARRAY DE TIPO PLAN
typedef Plan* SetPlanes;

/***
    INTERFAZ DE CONJUNTO DE PLANES
***/

// Prop.: crea el conjunto actual de planes
// O(n)
SetPlanes crearPlanes();

// Prop.: agrega un cliente a un plan
// O(1)
void agregarAPlan(SetPlanes& ps, string plan, string cuit);

// Prop.: agrega un cliente al plan inicial
// O(1)
void agregarAPrimerPlan(SetPlanes& ps, string cuit);

// Prop.: borra un cliente de un plan
// O(n)
void borrarDePlan(SetPlanes& ps, string plan, string cuit);

// Prop.: devuelve la cantidad de clientes de un plan
// O(1)
int cantidadDeClientes(SetPlanes ps, string plan);

// Prop.: pasa un cliente al siguiente plan si corresponde
// y devuelve el plan en el que debería estar
// O(n)
string chequearPlan(SetPlanes& ps, string plan, string cuit, int cantidadDePrendas);

// Prop.: pasa un cliente al siguiente plan si corresopnde
// O(n)
void destroyPlanes(SetPlanes& ps);

// Prop: Elimina los clientes del plan recibido, retorna los clientes eliminados
// O():
ArrayList eliminarClientesDelPlanS(string plan, SetPlanes& ps);

// Prop.: imprime un set de planes de clientes
// O(n)
void printSet(SetPlanes ps);

/***
    ITERADOR DE PLANES
***/

/// UN ITERADOR SOBRE PLANES ES
/// SIMPLEMENTE UN INDICE SOBRE UN PLAN
struct PlanesIteratorSt {
    int indiceActual;
    SetPlanes planes;
};

typedef PlanesIteratorSt* PlanIterator;

PlanIterator startIt(SetPlanes ps);
string currentIt(PlanIterator it);
void nextIt(PlanIterator& it);
bool finishedIt(PlanIterator it);
void destroyIt(PlanIterator& it);
