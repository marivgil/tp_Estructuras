#include <iostream>
#include "Map.h"
#include "SetPlanes.h"

using namespace std;

struct LavaderoSt {
    Map clientes;
    SetPlanes planes;
};

typedef LavaderoSt* Lavadero;

// Prop.: crea un lavadero vacio
// O(n)
Lavadero crearLavadero();

// Prop.:
// O(log n)
Cliente obtenerCliente(Lavadero& lavadero, string cuit);

// Prop.: incorpora un cliente nuevo con plan inicial
// O(log n)
void agregarCliente(Lavadero& lavadero, string cuit, string nombre);

// Prop.: elimina un cliente del lavadero
// O(n)
void borrarCliente(Lavadero& lavadero, string cuit);

// Prop.: le otorga una cantidad de prendas a un cliente
// O(log n)
void darPrendas(Lavadero& lavadero, string cuit, int cantidad);

// Prop.: recibe una cantidad de prendas devueltas por un cliente
// O(log n)
void recibirPrendas(Lavadero& lavadero, string cuit, int cantidad);

// Prop.: devuelve la cantidad total de clientes del lavadero
// O(n)
int cantidadTotalDeClientes(Lavadero lavadero);

// Prop.: devuelve el plan con mas clientes
// Prec.: existe por lo menos un plan en el lavadero
// O(n)
string planConMasClientes(Lavadero lavadero);

// Prop.: destruye la memoria utilizada por el lavadero
// O(n . log n)
void destroyLavadero(Lavadero& lavadero);

// Prop: elimina el plan indicado por parametro del lavadero
// O()
void borrarClientesDePlan(string unPlan, Lavadero& unLavadero);

void printLavadero(Lavadero lavadero);
